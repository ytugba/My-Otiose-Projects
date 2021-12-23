print("Loading Libraries...")
import os
import tkinter
from tkinter import filedialog
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import datetime
import json
import datetime
from skimage.transform import resize
from keras.models import Model
from keras.layers import Input, concatenate, Conv2D, MaxPooling2D, Conv2DTranspose, Dropout, UpSampling2D
from keras.optimizers import Adam, SGD
from keras.callbacks import ModelCheckpoint
from keras import backend as K
from keras.callbacks import History
from keras.models import model_from_json
print("Loading Libraries Ended.")
print('-'*30)
root = tkinter.Tk()
root.withdraw()

#paths
desktop = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop')
currentDate = datetime.datetime.now().strftime("%m-%d-%y %H-%M")

json_file_path = desktop + "\\PSGizmoLog\\Train\\" + currentDate + "\\JSONFiles\\" #save
model_file_path = desktop + "\\PSGizmoLog\\Train\\" + currentDate + "\\Model\\" #save
graph_file_path = desktop + "\\PSGizmoLog\\Train\\" + currentDate + "\\Graphs\\" #save

if not os.path.exists(model_file_path):
  os.makedirs(model_file_path)
if not os.path.exists(json_file_path):
  os.makedirs(json_file_path)
if not os.path.exists(graph_file_path):
  os.makedirs(graph_file_path)

#contain mask.npy and train.npy
print("Load Train Directory:")
data_numpy_path = filedialog.askdirectory()

print("Path: " + data_numpy_path)
print('-'*30)

K.set_image_data_format('channels_last')  # TF dimension ordering in this code

img_rows = int(512/2)
img_cols = int(512/2)
smooth = 1.

#comparision metrics
def dice_coef(y_true, y_pred):
    y_true_f = K.flatten(y_true)
    y_pred_f = K.flatten(y_pred)
    intersection = K.sum(y_true_f * y_pred_f)
    return (2. * intersection + smooth) / (K.sum(y_true_f) + K.sum(y_pred_f) + smooth)

def dice_coef_loss(y_true, y_pred):
    return -dice_coef(y_true, y_pred)

#limit choices
def inputNumber(message):
  while True:
    try:
       userInput = int(input(message))       
    except ValueError:
       print("Not an integer! Try again.")
       continue
    else:
       return userInput 
       break 

#CLASSICAL UNET ARCHITECTURE
def get_unet(sizeOfBatch,sizeOfEpoch,sizeOfValidation,pretrained_weights = None,input_size = (256,256,1)):
    inputs = Input((img_rows, img_cols, 1))
    conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(inputs)
    conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(conv1)
    pool1 = MaxPooling2D(pool_size=(2, 2))(conv1)

    conv2 = Conv2D(64, (3, 3), activation='relu', padding='same')(pool1)
    conv2 = Conv2D(64, (3, 3), activation='relu', padding='same')(conv2)
    pool2 = MaxPooling2D(pool_size=(2, 2))(conv2)

    conv3 = Conv2D(128, (3, 3), activation='relu', padding='same')(pool2)
    conv3 = Conv2D(128, (3, 3), activation='relu', padding='same')(conv3)
    pool3 = MaxPooling2D(pool_size=(2, 2))(conv3)

    conv4 = Conv2D(256, (3, 3), activation='relu', padding='same')(pool3)
    conv4 = Conv2D(256, (3, 3), activation='relu', padding='same')(conv4)
    pool4 = MaxPooling2D(pool_size=(2, 2))(conv4)

    conv5 = Conv2D(512, (3, 3), activation='relu', padding='same')(pool4)
    conv5 = Conv2D(512, (3, 3), activation='relu', padding='same')(conv5)

    up6 = concatenate([Conv2DTranspose(256, (2, 2), strides=(2, 2), padding='same')(conv5), conv4], axis=3)
    conv6 = Conv2D(256, (3, 3), activation='relu', padding='same')(up6)
    conv6 = Conv2D(256, (3, 3), activation='relu', padding='same')(conv6)

    up7 = concatenate([Conv2DTranspose(128, (2, 2), strides=(2, 2), padding='same')(conv6), conv3], axis=3)
    conv7 = Conv2D(128, (3, 3), activation='relu', padding='same')(up7)
    conv7 = Conv2D(128, (3, 3), activation='relu', padding='same')(conv7)

    up8 = concatenate([Conv2DTranspose(64, (2, 2), strides=(2, 2), padding='same')(conv7), conv2], axis=3)
    conv8 = Conv2D(64, (3, 3), activation='relu', padding='same')(up8)
    conv8 = Conv2D(64, (3, 3), activation='relu', padding='same')(conv8)

    up9 = concatenate([Conv2DTranspose(32, (2, 2), strides=(2, 2), padding='same')(conv8), conv1], axis=3)
    conv9 = Conv2D(32, (3, 3), activation='relu', padding='same')(up9)
    conv9 = Conv2D(32, (3, 3), activation='relu', padding='same')(conv9)

    conv10 = Conv2D(1, (1, 1), activation='sigmoid')(conv9)

    model = Model(inputs=[inputs], outputs=[conv10])

    model.summary()
    #plot_model(model, to_file='model.png')

    model.compile(optimizer=Adam(lr=1e-3), loss=dice_coef_loss, metrics=[dice_coef, 'acc'])
    
    return model

#DENSE UNET ARCHITECTURE
def get_densenet(sizeOfBatch,sizeOfEpoch,sizeOfValidation,pretrained_weights = None,input_size = (256,256,1)):
    inputs = Input((img_rows, img_cols, 1))
    conv11 = Conv2D(32, (3, 3), activation='relu', padding='same')(inputs)
    conc11 = concatenate([inputs, conv11], axis=3)
    conv12 = Conv2D(32, (3, 3), activation='relu', padding='same')(conc11)
    conc12 = concatenate([inputs, conv12], axis=3)
    pool1 = MaxPooling2D(pool_size=(2, 2))(conc12)

    conv21 = Conv2D(64, (3, 3), activation='relu', padding='same')(pool1)
    conc21 = concatenate([pool1, conv21], axis=3)
    conv22 = Conv2D(64, (3, 3), activation='relu', padding='same')(conc21)
    conc22 = concatenate([pool1, conv22], axis=3)
    pool2 = MaxPooling2D(pool_size=(2, 2))(conc22)

    conv31 = Conv2D(128, (3, 3), activation='relu', padding='same')(pool2)
    conc31 = concatenate([pool2, conv31], axis=3)
    conv32 = Conv2D(128, (3, 3), activation='relu', padding='same')(conc31)
    conc32 = concatenate([pool2, conv32], axis=3)
    pool3 = MaxPooling2D(pool_size=(2, 2))(conc32)

    conv41 = Conv2D(256, (3, 3), activation='relu', padding='same')(pool3)
    conc41 = concatenate([pool3, conv41], axis=3)
    conv42 = Conv2D(256, (3, 3), activation='relu', padding='same')(conc41)
    conc42 = concatenate([pool3, conv42], axis=3)
    pool4 = MaxPooling2D(pool_size=(2, 2))(conc42)

    conv51 = Conv2D(512, (3, 3), activation='relu', padding='same')(pool4)
    conc51 = concatenate([pool4, conv51], axis=3)
    conv52 = Conv2D(512, (3, 3), activation='relu', padding='same')(conc51)
    conc52 = concatenate([pool4, conv52], axis=3)

    up6 = concatenate([Conv2DTranspose(256, (2, 2), strides=(2, 2), padding='same')(conc52), conc42], axis=3)
    conv61 = Conv2D(256, (3, 3), activation='relu', padding='same')(up6)
    conc61 = concatenate([up6, conv61], axis=3)
    conv62 = Conv2D(256, (3, 3), activation='relu', padding='same')(conc61)
    conc62 = concatenate([up6, conv62], axis=3)

    up7 = concatenate([Conv2DTranspose(128, (2, 2), strides=(2, 2), padding='same')(conc62), conv32], axis=3)
    conv71 = Conv2D(128, (3, 3), activation='relu', padding='same')(up7)
    conc71 = concatenate([up7, conv71], axis=3)
    conv72 = Conv2D(128, (3, 3), activation='relu', padding='same')(conc71)
    conc72 = concatenate([up7, conv72], axis=3)

    up8 = concatenate([Conv2DTranspose(64, (2, 2), strides=(2, 2), padding='same')(conc72), conv22], axis=3)
    conv81 = Conv2D(64, (3, 3), activation='relu', padding='same')(up8)
    conc81 = concatenate([up8, conv81], axis=3)
    conv82 = Conv2D(64, (3, 3), activation='relu', padding='same')(conc81)
    conc82 = concatenate([up8, conv82], axis=3)

    up9 = concatenate([Conv2DTranspose(32, (2, 2), strides=(2, 2), padding='same')(conc82), conv12], axis=3)
    conv91 = Conv2D(32, (3, 3), activation='relu', padding='same')(up9)
    conc91 = concatenate([up9, conv91], axis=3)
    conv92 = Conv2D(32, (3, 3), activation='relu', padding='same')(conc91)
    conc92 = concatenate([up9, conv92], axis=3)

    conv10 = Conv2D(1, (1, 1), activation='sigmoid')(conc92)

    model = Model(inputs=[inputs], outputs=[conv10])

    model.summary()
    #plot_model(model, to_file='model.png')

    model.compile(optimizer=Adam(lr=1e-5, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=0.000000199), loss='binary_crossentropy', metrics=['accuracy'])

    return model

#RESNET ARCHITECTURE
def get_resnet(sizeOfBatch,sizeOfEpoch,sizeOfValidation,pretrained_weights = None,input_size = (256,256,1)):
    inputs = Input((img_rows, img_cols, 1))
    conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(inputs)
    conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(conv1)
    conc1 = concatenate([inputs, conv1], axis=3)
    pool1 = MaxPooling2D(pool_size=(2, 2))(conc1)

    conv2 = Conv2D(64, (3, 3), activation='relu', padding='same')(pool1)
    conv2 = Conv2D(64, (3, 3), activation='relu', padding='same')(conv2)
    conc2 = concatenate([pool1, conv2], axis=3)
    pool2 = MaxPooling2D(pool_size=(2, 2))(conc2)

    conv3 = Conv2D(128, (3, 3), activation='relu', padding='same')(pool2)
    conv3 = Conv2D(128, (3, 3), activation='relu', padding='same')(conv3)
    conc3 = concatenate([pool2, conv3], axis=3)
    pool3 = MaxPooling2D(pool_size=(2, 2))(conc3)

    conv4 = Conv2D(256, (3, 3), activation='relu', padding='same')(pool3)
    conv4 = Conv2D(256, (3, 3), activation='relu', padding='same')(conv4)
    conc4 = concatenate([pool3, conv4], axis=3)
    pool4 = MaxPooling2D(pool_size=(2, 2))(conc4)

    conv5 = Conv2D(512, (3, 3), activation='relu', padding='same')(pool4)
    conv5 = Conv2D(512, (3, 3), activation='relu', padding='same')(conv5)
    conc5 = concatenate([pool4, conv5], axis=3)

    up6 = concatenate([Conv2DTranspose(256, (2, 2), strides=(2, 2), padding='same')(conc5), conv4], axis=3)
    conv6 = Conv2D(256, (3, 3), activation='relu', padding='same')(up6)
    conv6 = Conv2D(256, (3, 3), activation='relu', padding='same')(conv6)
    conc6 = concatenate([up6, conv6], axis=3)

    up7 = concatenate([Conv2DTranspose(128, (2, 2), strides=(2, 2), padding='same')(conc6), conv3], axis=3)
    conv7 = Conv2D(128, (3, 3), activation='relu', padding='same')(up7)
    conv7 = Conv2D(128, (3, 3), activation='relu', padding='same')(conv7)
    conc7 = concatenate([up7, conv7], axis=3)

    up8 = concatenate([Conv2DTranspose(64, (2, 2), strides=(2, 2), padding='same')(conc7), conv2], axis=3)
    conv8 = Conv2D(64, (3, 3), activation='relu', padding='same')(up8)
    conv8 = Conv2D(64, (3, 3), activation='relu', padding='same')(conv8)
    conc8 = concatenate([up8, conv8], axis=3)

    up9 = concatenate([Conv2DTranspose(32, (2, 2), strides=(2, 2), padding='same')(conc8), conv1], axis=3)
    conv9 = Conv2D(32, (3, 3), activation='relu', padding='same')(up9)
    conv9 = Conv2D(32, (3, 3), activation='relu', padding='same')(conv9)
    conc9 = concatenate([up9, conv9], axis=3)

    conv10 = Conv2D(1, (1, 1), activation='sigmoid')(conc9)

    model = Model(inputs=[inputs], outputs=[conv10])

    model.summary()
    #plot_model(model, to_file='model.png')

    model.compile(optimizer=Adam(lr=1e-5, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=0.000000199), loss='binary_crossentropy', metrics=['accuracy'])

    return model

#ZHIXUHAONET UNET ARCHITECTURE
def get_zhixuhaonet(sizeOfBatch,sizeOfEpoch,sizeOfValidation,pretrained_weights = None,input_size = (256,256,1)):
    inputs = Input(input_size)
    conv1 = Conv2D(64, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(inputs)
    conv1 = Conv2D(64, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv1)
    pool1 = MaxPooling2D(pool_size=(2, 2))(conv1)
    conv2 = Conv2D(128, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(pool1)
    conv2 = Conv2D(128, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv2)
    pool2 = MaxPooling2D(pool_size=(2, 2))(conv2)
    conv3 = Conv2D(256, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(pool2)
    conv3 = Conv2D(256, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv3)
    pool3 = MaxPooling2D(pool_size=(2, 2))(conv3)
    conv4 = Conv2D(512, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(pool3)
    conv4 = Conv2D(512, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv4)
    drop4 = Dropout(0.5)(conv4)
    pool4 = MaxPooling2D(pool_size=(2, 2))(drop4)

    conv5 = Conv2D(1024, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(pool4)
    conv5 = Conv2D(1024, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv5)
    drop5 = Dropout(0.5)(conv5)

    up6 = Conv2D(512, 2, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(UpSampling2D(size = (2,2))(drop5))
    merge6 = concatenate([drop4,up6], axis = 3)
    conv6 = Conv2D(512, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(merge6)
    conv6 = Conv2D(512, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv6)

    up7 = Conv2D(256, 2, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(UpSampling2D(size = (2,2))(conv6))
    merge7 = concatenate([conv3,up7], axis = 3)
    conv7 = Conv2D(256, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(merge7)
    conv7 = Conv2D(256, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv7)

    up8 = Conv2D(128, 2, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(UpSampling2D(size = (2,2))(conv7))
    merge8 = concatenate([conv2,up8], axis = 3)
    conv8 = Conv2D(128, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(merge8)
    conv8 = Conv2D(128, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv8)

    up9 = Conv2D(64, 2, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(UpSampling2D(size = (2,2))(conv8))
    merge9 = concatenate([conv1,up9], axis = 3)
    conv9 = Conv2D(64, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(merge9)
    conv9 = Conv2D(64, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv9)
    conv9 = Conv2D(2, 3, activation = 'relu', padding = 'same', kernel_initializer = 'he_normal')(conv9)
    conv10 = Conv2D(1, 1, activation = 'sigmoid')(conv9)

    model = Model(input = inputs, output = conv10)

    model.compile(optimizer = Adam(lr = 1e-4), loss = 'binary_crossentropy', metrics = ['accuracy'])
    model.summary()
    
    return model
    

#select architecture and define paramaters
def get_architecture(sizeOfBatch = 1, sizeOfEpoch = 1, sizeOfValidation = 0.1):
    architectures = ["Classical U-Net","DenseNet","ResNet","zhixuhao U-Net"]
    print("Choose architecture:")
    for arch in architectures:
        print(str(architectures.index(arch) + 1) + ": " + arch)

    choice = input()
    sizeOfBatch = inputNumber("Batch Size: (Ex. 64)")
    sizeOfEpoch = inputNumber("Epoch Size: (Ex. 10)")
    sizeOfValidation = 0.0
    
    while sizeOfValidation <= 0.0 or sizeOfValidation >= 1.0:
      try:
        sizeOfValidation = float(input("Validation Split: (Ex. 0.2)"))
      except ValueError:
        print('Value must be between 0 and 1.')
        
    if(choice == '1'):
        model = get_unet(sizeOfBatch,sizeOfEpoch,sizeOfValidation)
    elif(choice == '2'):
        model = get_densenet(sizeOfBatch,sizeOfEpoch,sizeOfValidation)
    elif(choice == '3'):
        model = get_resnet(sizeOfBatch,sizeOfEpoch,sizeOfValidation)        
    elif(choice == '4'):
        model = get_zhixuhaonet(sizeOfBatch,sizeOfEpoch,sizeOfValidation)        
    else:
        get_architecture(sizeOfBatch,sizeOfEpoch,sizeOfValidation)

    return model, sizeOfBatch, sizeOfEpoch, sizeOfValidation


def load_train_data():
    imgs_train = np.load(data_numpy_path + '\\imgs_train.npy')
    masks_train = np.load(data_numpy_path + '\\masks_train.npy')
    print("Data is loaded.")
    print('-'*30)
    return imgs_train, masks_train

def preprocess(imgs):
    imgs_p = np.ndarray((imgs.shape[0], img_rows, img_cols), dtype=np.uint8)
    
    for i in range(imgs.shape[0]):
        imgs_p[i] = resize(imgs[i], (img_cols, img_rows), preserve_range=True)

    imgs_p = imgs_p[..., np.newaxis]
    print("Data is resized.")
    print('-'*30)
    return imgs_p

def train():
    
    #If you change raw files (dataset) don't forget to re-run create functions
    
    print('Loading and preprocessing train data...')
    print('-'*30)
    
    imgs_train, imgs_mask_train = load_train_data()

    imgs_train = preprocess(imgs_train)
    imgs_mask_train = preprocess(imgs_mask_train)

    print('Normalization of the Train Set is completed.')
    print('-'*30)
    
    imgs_train = imgs_train.astype('float32')
    
    mean = np.mean(imgs_train)  # mean for data centering
    std = np.std(imgs_train)  # std for data normalization

    imgs_train -= mean
    imgs_train /= std      
    
    imgs_mask_train = imgs_mask_train.astype('float32')

    print('Creating and compiling model...')
    print('-'*30)
    
    #Call Neural Network
    model, sizeOfBatch, sizeOfEpoch, sizeOfValidation  = get_architecture()
    
    #Save model weights
    model_checkpoint = ModelCheckpoint(model_file_path + 'weights.h5', monitor='val_loss', save_best_only=True)
    
    print('Saving the weights and the loss of the best predictions...')
    print('-'*30)
    
    print('Fitting model...')
    print('-'*30)
    
    history=model.fit(imgs_train, imgs_mask_train, batch_size=sizeOfBatch, epochs=sizeOfEpoch, verbose=1, 
                      shuffle=True, validation_split=sizeOfValidation, callbacks=[model_checkpoint])
        
    #Save Normalization Data to the JSON file
    normalization = '{"mean": ' + str(mean) + ', "std": ' + str(std) + '}'
    
    with open(json_file_path + "normalization.json", "w") as json_file:
        json_file.write(str(normalization))
    
    print("Normalization data is saved to the disk.")
    print('-'*30)
    
    #Save Model to the JSON file
    model_json = model.to_json()
    
    with open(json_file_path + "model.json", "w") as json_file:
        json_file.write(model_json)
        
    print("Model is saved to disk.")
    print('-'*30)
    
    #Save History to the JSON file    
    hist_df = pd.DataFrame(history.history) 
    
    with open(json_file_path + 'history.json' , mode='w') as f:
        hist_df.to_json(f)
              
    print("History is saved to disk.")   
    print('-'*30)

def graphs():
    
    #this function creates graphs from records in history.json    
    historyFile = open(json_file_path + 'history.json', 'r')
    historyString = historyFile.read()
    history = json.loads(historyString)
    historyFile.close()
    
    #number of epochs
    size_acc = len(history["acc"])
    size_val_acc = len(history["val_acc"])
    size_dice_coef = len(history["dice_coef"])
    size_val_dice_coef = len(history["val_dice_coef"])
    size_loss = len(history["loss"])
    size_val_loss = len(history["val_loss"])
    
    history_acc = []
    history_val_acc = []
    history_dice_coef = []
    history_val_dice_coef = []
    history_loss = []
    history_val_loss = []
    
    for i in range(0,size_acc):
        history_acc.append(history["acc"]["{}".format(i)])
    
    for i in range(0,size_val_acc):
        history_val_acc.append(history["val_acc"]["{}".format(i)])

    for i in range(0,size_dice_coef):
        history_dice_coef.append(history["dice_coef"]["{}".format(i)])
    
    for i in range(0,size_val_dice_coef):
        history_val_dice_coef.append(history["val_dice_coef"]["{}".format(i)])
        
    for i in range(0,size_loss):
        history_loss.append(history["loss"]["{}".format(i)])
    
    for i in range(0,size_val_loss):
        history_val_loss.append(history["val_loss"]["{}".format(i)])

    if not os.path.exists(graph_file_path):
        os.mkdir(graph_file_path)   
        
    print('Dice Coefficient is calculated.')
    print('-'*30)
    plt.plot(history_dice_coef)
    plt.plot(history_val_dice_coef)
    plt.title('Model Dice Coeff')
    plt.ylabel('Dice coeff')
    plt.xlabel('Epoch')
    plt.legend(['Train', 'Test'], loc='upper left')
    dice_coeff_graph = plt.gcf()
    dice_coeff_graph.savefig(os.path.join(graph_file_path) + 'Dice_Coeff.png')

    print('Loss is calculated.')
    print('-'*30)
    plt.plot(history_loss)
    plt.plot(history_val_loss)
    plt.title('Model Loss')
    plt.ylabel('loss')
    plt.xlabel('Epoch')
    plt.legend(['Train', 'Test'], loc='upper left')
    loss_graph = plt.gcf()
    loss_graph.savefig(os.path.join(graph_file_path) + 'Loss.png')
    
    print('Accuracy is calculated.')
    print('-'*30)
    plt.plot(history_acc)
    plt.plot(history_val_acc)
    plt.title('Model Accuracy')
    plt.ylabel('acc')
    plt.xlabel('Epoch')
    plt.legend(['Train', 'Test'], loc='upper left')
    acc_graph = plt.gcf()
    acc_graph.savefig(os.path.join(graph_file_path) + 'Accuracy.png')

if __name__ == '__main__':
    train()
    graphs()
    input("Press ENTER to exit")
