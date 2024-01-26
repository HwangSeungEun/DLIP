import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Open Image in RGB
img = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\coins.jpg',cv.COLOR_BGR2GRAY)


# w/o threshold canny
edges = cv.Canny(img,50,200)

# Plot Results
#cv.imshow('Edges',edges)
titles = ['Original','Edges']
images = [img, edges]
for i in range(2):
    plt.subplot(1,2,i+1),plt.imshow(images[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()


# w/ threshold canny
thVal=127
ret,thresh1 = cv.threshold(img,thVal,255,cv.THRESH_BINARY)
edges = cv.Canny(thresh1,50,200)

# Plot Results
#cv.imshow('Edges',edges)
titles = ['Original','Edges']
images = [img, edges]
for i in range(2):
    plt.subplot(1,2,i+1),plt.imshow(images[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()