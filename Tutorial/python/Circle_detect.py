import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Open Image in RGB
src = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\coins.jpg')
# Read Image
# cv.imshow('source', src)
# cv.waitKey(0)
# cv.destroyAllWindows()

# Convert it to grayscale:
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
# cv.imshow('gray', gray)
# cv.waitKey(0)
# cv.destroyAllWindows()

# Reduce noise and avoid false circle detection
blur = cv.medianBlur(gray, 5)
# cv.imshow('blur', blur)
# cv.waitKey(0)
# cv.destroyAllWindows()


# Hough Circle Transform
rows = blur.shape[0]
circles = cv.HoughCircles(blur, cv.HOUGH_GRADIENT, 1, rows / 8, 
                               param1=80, param2=30,
                               minRadius=1, maxRadius=30)
print(circles)


# Draw circle
if circles is not None:
    circles = np.uint16(np.around(circles))
    for i in circles[0, :]:
        print("작동중...")
        center = (i[0], i[1])
        # Draw circle center
        cv.circle(src, center, 1, (0, 100, 100), 3)
        # Draw circle outline
        radius = i[2]
        cv.circle(src, center, radius, (255, 0, 0), 3)


# Plot images
titles = ['Original with Circle Detected']
srcPlt=cv.cvtColor(src,cv.COLOR_BGR2RGB)
plt.imshow(srcPlt)
plt.title(titles)
plt.xticks([]),plt.yticks([])
plt.show()

