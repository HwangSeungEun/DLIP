import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Read image
src = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\coins.jpg',0)

# Threshold
ret,thresh1 = cv.threshold(src,127,255,cv.THRESH_BINARY)
img=thresh1

# Structure Element for Morphology
cv.getStructuringElement(cv.MORPH_RECT,(5,5))
kernel = np.ones((5,5),np.uint8)

# Morphology
erosion = cv.erode(img,kernel,iterations = 1)
dilation = cv.dilate(img,kernel,iterations = 1)
opening = cv.morphologyEx(img, cv.MORPH_OPEN, kernel)
closing = cv.morphologyEx(img, cv.MORPH_CLOSE, kernel)


# Plot results
titles = ['Original ', 'Opening','Closing']
images = [src, opening, closing]

for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(images[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()