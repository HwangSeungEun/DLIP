import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt


# Load image
img = cv.imread('C:\\Users\\erich\source\\repos\\DLIP\\Image\\handonglogo.jpg')

# Show Image using colab imshow
cv.imshow('source',img) 

cv.waitKey(0)
cv.destroyAllWindows()