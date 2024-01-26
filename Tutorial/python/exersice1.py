import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

src = cv.imread ('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\rice.png')

cv.imshow('source', src)
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)

blur = cv.blur(gray,(3,3))
cv.imshow('blur', blur)



histSize = 256
histRange = (0, 256) # the upper boundary is exclusive
b_hist = cv.calcHist(blur, [0], None, [histSize], histRange, False)

hist_w = 512
hist_h = 400
bin_w = int(round( hist_w/histSize ))
histImage = np.zeros((hist_h, hist_w, 3), dtype=np.uint8)

# Normalize histogram output
cv.normalize(b_hist, b_hist, alpha=0, beta=hist_h, norm_type=cv.NORM_MINMAX)

for i in range(1, histSize):
    cv.line(histImage, ( bin_w*(i-1), hist_h - int(b_hist[i-1]) ),
            ( bin_w*(i), hist_h - int(b_hist[i]) ),
            ( 255, 0, 0), thickness=2)
cv.imshow('histogram', histImage)



ret, threshold  = cv.threshold(blur,127,255,cv.THRESH_BINARY)
cv.imshow('threshold', threshold)


kernel = np.ones((5,5),np.uint8)
closing = cv.morphologyEx(threshold, cv.MORPH_CLOSE, kernel)
cv.imshow('morph', closing)
cv.waitKey(0)
cv.destroyAllWindows()


