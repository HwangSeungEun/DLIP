import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Load image
img = cv.imread('C:\\Users\\erich\source\\repos\\DLIP\\Image\\handonglogo.jpg')


# Show Image using matplotlib
# matplotlib에서 rgb 채널 순서가 다름
# matplot:  R-B-G
# OpenCV:   B-G-R
imgPlt = cv.cvtColor(img, cv.COLOR_BGR2RGB)

plt.imshow(imgPlt),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.show()

