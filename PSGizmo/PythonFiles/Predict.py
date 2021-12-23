print("Loading Libraries...")
import os
import numpy as np
import json
import tensorflow as tf
import nibabel
import sys
import nibabel as nib
import datetime
import tkinter
from tkinter import filedialog
import SimpleITK as sitk
from skimage import io
from skimage.io import imsave
from skimage.segmentation import mark_boundaries
from skimage.transform import resize
from skimage.exposure import rescale_intensity

from keras import backend as K
from keras.models import model_from_json
print("Loading Libraries Ended.")
print('-'*30)
root = tkinter.Tk()
root.withdraw()
desktop = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop')
currentDate = datetime.datetime.now().strftime("%m-%d-%y %H-%M")

nii_save_path = desktop + "\\PSGizmoLog\\Predict\\" + currentDate + "\\" #save

if not os.path.exists(nii_save_path):
  os.makedirs(nii_save_path)
imageRows = int(512/2)
imageCols = int(512/2) 
smooth = 1.
global affineValue

def Dice_Coef(y_true, y_pred):
    y_true_f = K.flatten(y_true)
    y_pred_f = K.flatten(y_pred)
    intersection = K.sum(y_true_f * y_pred_f)
    return (2. * intersection + smooth) / (K.sum(y_true_f) + K.sum(y_pred_f) + smooth)

def Dice_Coef_Loss(y_true, y_pred):
    return -Dice_Coef(y_true, y_pred)

def Adapt_Data(imgs):
    imgs_p = np.ndarray((imgs.shape[0], imageRows, imageCols), dtype='float32')
    for i in range(imgs.shape[0]):
        imgs_p[i] = resize(imgs[i], (imageCols, imageRows), preserve_range=True)
    imgs_p = imgs_p[..., np.newaxis]
    
    print("File is resized.");
    print('-'*30)
    return imgs_p

def Load_Prediction_Images():
    print("Load .npy to predict:")
    prediction_data_path = filedialog.askopenfilename()
    imgst = np.load(prediction_data_path)
    return imgst

def nifti_format(imgst, layerst):
    print("Exporting...")
    if not os.path.exists(nii_save_path +"\\Nifti"):
        os.makedirs(nii_save_path +"\\Nifti")
        
    filtered_image = sitk.GetImageFromArray(imgst)
    writer = sitk.ImageFileWriter()
    writer.SetFileName(nii_save_path +"\\Nifti\\Liver.nii.gz")
    writer.Execute(filtered_image)
    
    filtered_mask = sitk.GetImageFromArray(layerst)
    writer = sitk.ImageFileWriter()
    writer.SetFileName(nii_save_path + "\\Nifti\\Layer.nii.gz")
    writer.Execute(filtered_mask)
    print("Exporting is completed.")
    print('-'*30)
    ch = input("Do you want to check the results using MRIcron? (y/n): ")
    if ch == 'y' or ch == 'Y':
       os.startfile(".\\AdditionalSources\\MRIcron\\mricron.exe")
#TODO
def png_format(imgToPredict, predictedImage):
    if not os.path.exists(nii_save_path + "PNG"):
      os.mkdir(nii_save_path + "PNG")
    if not os.path.exists(nii_save_path + "PNG\\Numpy"):
      os.mkdir(nii_save_path + "PNG\\Numpy")

    np.save(nii_save_path + "PNG\\Numpy" + '\\imgs_mask_test.npy', predictedImage)
    
    print('Saving predicted masks to files...')
    print('-' * 30)
    
    print('Saving Our Predictions in the Directory preds')   
    print('-' * 30) 
    
    for k in range(len(predictedImage)):
        a=rescale_intensity(imgToPredict[k][:,:,0],out_range=(-1,1))
        b=(predictedImage[k][:,:,0]).astype(np.uint8)
        io.imsave(os.path.join(nii_save_path + "PNG\\", str(k) + '_pred.png'), mark_boundaries(a, b,color=(1,1,0), mode='thick'))
        
    print('Saving predictions is completed!')
    print('-' * 30)

def Predict():
    #Load Normalization Values
    print("Load JSON files directory:")
    json_data_path = filedialog.askdirectory()
    print("Selected JSON path: " + json_data_path)
    normalizationFile = open(json_data_path + '\\normalization.json', 'r')
    normalizationString = normalizationFile.read()
    normalizationData = json.loads(normalizationString)
    normalizationFile.close()
    
    #Load Model
    jsonFile = open( json_data_path + '\\model.json', 'r')
    loadedModelJson = jsonFile.read()
    model = model_from_json(loadedModelJson)
    jsonFile.close()
    
    #model.summary()
    
    imgToPredict = Load_Prediction_Images()
    imgToPredict = Adapt_Data(imgToPredict)
    
    mean = normalizationData["mean"]
    std = normalizationData["std"]
    
    imgToPredict = imgToPredict.astype('float32')
    imgToPredict -= mean
    imgToPredict /= std

    print("Load weights.h5 file: ")
    model_data_path = filedialog.askopenfilename()
    print(model_data_path + "is weights.h5 path")
    print('-'*30)
    
    model.load_weights( model_data_path)
    
    print("Model is loaded.")
    print('-'*30)
    
    predictedImageAsNumpy = model.predict(imgToPredict, verbose=1)
    print("Prediction is completed.")
    print('-'*30)
    return imgToPredict, predictedImageAsNumpy

def Export_Prediction():
    imgToPredict, predictedImage = Predict()
        
    print("Exporting predictions...")
    print('-'*30)
    new_images = [] 
    imgst = np.ndarray((imageRows, imageCols, 0), dtype='float32')
    layerst = np.ndarray((imageRows, imageCols, 0), dtype='float32')

    print("Slices are being adapted...")
    for k in range(len(predictedImage)):
        a=rescale_intensity(imgToPredict[k][:,:,0],out_range=(-1,1))
        b=(predictedImage[k][:,:,0]).astype(np.uint8)
        imgst = np.dstack((imgst, a))
        layerst = np.dstack((layerst, b))
    print("Slices are adapted.")
    print('-'*30)
    
    print("1: Mask and Resized CT in nifti format")
    print("2: Slices in png format")
    print("3: Transparent png format")
    print("4: GIF Format")

    choice = input()
    
    if(choice == '1'):
        nifti_format(imgst,layerst)
    elif(choice == '2'):
        png_format(imgToPredict, predictedImage)
    else:
        print("Invalid choice")
        while(choice != '1' or choice != '2'):
          choice = input()
        if(choice == '1'):
          nifti_format(imgst,layerst)
        elif(choice == '2'):
          png_format(imgToPredict, predictedImage)
    print('-'*30)

if __name__ == '__main__':
    Export_Prediction()
    input("Press ENTER to Exit")
