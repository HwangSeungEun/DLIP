import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt


# Webcam is used for *.py code. 
# Using webcam in notebook(colab, jupyter) requires more complex setup.

cap = cv.VideoCapture(0)

while(1):
    _, frame = cap.read()

    cv.imshow('frame',frame)
    
    k = cv.waitKey(5) & 0xFF
    if k == 27:
        break

cv.destroyAllWindows()
cap.release()