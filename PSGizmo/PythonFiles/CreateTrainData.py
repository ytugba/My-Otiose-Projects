import tkinter
from tkinter import filedialog

import os
import numpy as np
import nibabel
import datetime

image_rows = int(512/2)
image_cols = int(512/2)

print("Select .nii folder path:")

root = tkinter.Tk()
root.withdraw()

train_data_path = filedialog.askdirectory()
desktop = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop')
currentDate = datetime.datetime.now().strftime("%m-%d-%y %H-%M")

train_data_save_path = desktop + "\\PSGizmoLog\\Data\\Train\\" + currentDate + "\\" 
if not os.path.exists(train_data_save_path):
  os.makedirs(train_data_save_path)

print('-'*30)
print("Selected data path: " + train_data_path)

print('-'*30)
print('Creating training data...')

images = os.listdir(train_data_path)

#training images
imgs_train=[] 
#training masks (corresponding to the liver)
masks_train=[]

print('-'*30)
print('Loading and resampling data...')

for image_name in images:
    if ('orig' in image_name) or ('liver' in image_name):
        img=nibabel.load(os.path.join(train_data_path,image_name))
        for k in range(img.shape[2]):  
            img_2d=np.array(img.get_data()[::2,::2,k])
            if ('orig' in image_name):
                imgs_train.append(img_2d)            
            if ('liver' in image_name):
                masks_train.append(img_2d)   
                
imgs = np.ndarray(
        (len(imgs_train), image_rows, image_cols), dtype=np.uint8
        )
imgs_mask = np.ndarray(
        (len(masks_train), image_rows, image_cols), dtype=np.uint8
        )
for index,img in enumerate(imgs_train):
    imgs[index,:,:]=img
for index,img in enumerate(masks_train):
    imgs_mask[index,:,:]=img
    
print('-'*30)
print("Files are ready!")
print("Do you want to save files? y/n")
option = input()
option = str(option)
if(option == 'y' or option == 'Y'):
    print('-'*30)
    print("Saved Data Path: " + train_data_save_path)

    np.save(train_data_save_path + '\\imgs_train.npy', imgs)
    np.save(train_data_save_path + '\\masks_train.npy', imgs_mask) 

    print('-'*30)
    print('Saving .npy file\'s done.')
    input("Press ENTER to exit")
elif(option == 'N' or option == 'n'):
    print('-'*30)
    input("Press ENTER to exit")
else:
    while(not((option == "y" or option == "Y") or (option == "n" or option == "N"))):
        print('-'*30)
        print("Do you want to save files? y/n")
        option = input()
        option = str(option)
        if(option == "y" or option == "Y"):
            print('-'*30)
            print("Saved Data Path: " + train_data_save_path)

            np.save(train_data_save_path + '\\imgs_train.npy', imgs)
            np.save(train_data_save_path + '\\masks_train.npy', imgs_mask)
            print('-'*30)
            print('Saving .npy file\'s done.')
            input("Press ENTER to exit")            
        elif(option == "N" or option == "n"):
            print('-'*30)
            input("Press ENTER to exit")
