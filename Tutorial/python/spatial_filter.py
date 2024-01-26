import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Load image
img = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\Pattern_original.tif')

# Spatial Filter
blur = cv.blur(img,(5,5))
gblur = cv.GaussianBlur(img,(5,5),0)
median = cv.medianBlur(img,5)

# Plot results
plt.subplot(221),plt.imshow(img),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.subplot(222),plt.imshow(blur),plt.title('Blurred')
plt.xticks([]), plt.yticks([])
plt.subplot(223),plt.imshow(gblur),plt.title('Gaussian Blurred')
plt.xticks([]), plt.yticks([])
plt.subplot(224),plt.imshow(median),plt.title('Median')
plt.xticks([]), plt.yticks([])
plt.show()
