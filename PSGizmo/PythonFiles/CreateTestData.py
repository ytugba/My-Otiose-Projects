import tkinter
from tkinter import filedialog

import os
import numpy as np
import nibabel
import datetime

image_rows = int(512/2)
image_cols = int(512/2)

root = tkinter.Tk()
root.withdraw()

desktop = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop')
currentDate = datetime.datetime.now().strftime("%m-%d-%y %H-%M")

print("Select .nii folder path:")
test_data_path = filedialog.askdirectory()

test_data_save_path = desktop + "\\PSGizmoLog\\Data\\Test\\" + currentDate + "\\" 
if not os.path.exists(test_data_save_path):
  os.makedirs(test_data_save_path)
  
print('-'*30)
print("Selected Data Path: " + test_data_path)
images = os.listdir(test_data_path)

print('-'*30)
print('Creating test data...')
   
imgs_test=[]

for image_name in images:
    if 'orig' in image_name:
        img=nibabel.load(os.path.join(test_data_path,image_name))
        for k in range(img.shape[2]):  
            img_2d=np.array(img.get_data()[::2,::2,k])
            imgs_test.append(img_2d)            
      
imgst = np.ndarray(
        (len(imgs_test), image_rows, image_cols), dtype=np.uint8
        )
for index,img in enumerate(imgs_test):
    imgst[index,:,:]=img
print('-'*30)    
print("File(s) are ready!")
print('-'*30)
print("Do you want to save file? y/n")

option = input()
option = str(option)
if(option == 'y' or option == 'Y'):
    print('-'*30)
    print("Saved Data Path: " + test_data_save_path)
    np.save(test_data_save_path + '\\imgs_test.npy', imgst)
    print('Saving .npy file\'s done.')
    input("Press ENTER to exit")
    
elif(option == 'N' or option == 'n'):
    print('-'*30)
    input("Press ENTER to exit")
else:
    while(not((option == "y" or option == "Y") or (option == "n" or option == "N"))):
        print('-'*30)
        print("Do you want to save file? y/n")
        option = input()
        option = str(option)
        if(option == "y" or option == "Y"):
            print('-'*30)
            print("Saved Data Path: " + test_data_save_path)
            np.save(test_data_save_path + '\\imgs_test.npy', imgst)
            print('Saving .npy file\'s done.')
            input("Press ENTER to exit")            
        elif(option == "N" or option == "n"):
            print('-'*30)
            input("Press ENTER to exit")
