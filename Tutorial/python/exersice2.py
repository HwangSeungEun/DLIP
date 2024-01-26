import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

# Callback function for the trackbars
def do_nothing(x):
    pass

src = cv.imread ('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\color_ball.jpg')
cv.imshow('source', src)
hsv = cv.cvtColor(src, cv.COLOR_BGR2HSV)

blur = cv.GaussianBlur(hsv,(5,5), 0)
cv.imshow('blur', blur)

cv.namedWindow('image')

cv.namedWindow('image')
cv.createTrackbar('H_min', 'image', 0, 179, do_nothing)
cv.createTrackbar('H_max', 'image', 179, 179, do_nothing)
cv.createTrackbar('S_min', 'image', 0, 255, do_nothing)
cv.createTrackbar('S_max', 'image', 255, 255, do_nothing)
cv.createTrackbar('V_min', 'image', 0, 255, do_nothing)
cv.createTrackbar('V_max', 'image', 255, 255, do_nothing)

kernel = np.ones((5,5),np.uint8)

while True:
    # Get trackbar positions
    h_min = cv.getTrackbarPos('H_min', 'image')
    h_max = cv.getTrackbarPos('H_max', 'image')
    s_min = cv.getTrackbarPos('S_min', 'image')
    s_max = cv.getTrackbarPos('S_max', 'image')
    v_min = cv.getTrackbarPos('V_min', 'image')
    v_max = cv.getTrackbarPos('V_max', 'image')

    # Apply the color range and find the contours
    lower_bound = np.array([h_min, s_min, v_min])
    upper_bound = np.array([h_max, s_max, v_max])
    mask = cv.inRange(blur, lower_bound, upper_bound)

    morph = cv.morphologyEx(mask, cv.MORPH_CLOSE, kernel)

    cv.imshow('mask', morph)

    contours, _ = cv.findContours(morph, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

    min_w = 100
    min_h = 100


    # Draw bounding boxes around the detected objects
    for contour in contours:
        x, y, w, h = cv.boundingRect(contour)
        if min_w < w  and min_h < h:
            cv.rectangle(src, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # Show the original image with the bounding boxes
    cv.imshow('image', src)

    # Reset the image for the next frame
    src = cv.imread('C:\\Users\\erich\\source\\repos\\DLIP\\Image\\color_ball.jpg')

    # Break the loop if the 'q' key is pressed
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cv.destroyAllWindows()

