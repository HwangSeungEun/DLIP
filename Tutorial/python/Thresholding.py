import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt


# Open Image
img = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\coins.jpg',0)

thVal=127

# Apply Thresholding
ret,thresh1 = cv.threshold(img,thVal,255,cv.THRESH_BINARY)
ret,thresh2 = cv.threshold(img,thVal,255,cv.THRESH_BINARY_INV)

# Plot results
titles = ['Original Image','BINARY','BINARY_INV']
images = [img, thresh1, thresh2]

for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(images[i],'gray',vmin=0,vmax=255)
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
