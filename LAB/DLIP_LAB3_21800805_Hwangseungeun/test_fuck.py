import cv2 as cv
import numpy as np

def canny_threshold(val):
    return val

def hough_params(val):
    return val

def find_intersection(p1_l, p2_l, p1_r, p2_r):
    x1, y1 = p1_l
    x2, y2 = p2_l
    x3, y3 = p1_r
    x4, y4 = p2_r

    denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if denom == 0:
        return None

    px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom
    py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom

    return int(px), int(py)


def process_frame(frame, rho, theta, threshold, prev_p1_l, prev_p2_l, prev_p1_r, prev_p2_r):

    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    blur = cv.GaussianBlur(gray, (5, 5), 0)
    canny = cv.Canny(blur, canny_low, canny_high)
    
    mask = np.zeros_like(canny)
    height, width = frame.shape[:2]
    roi = np.array([[(50,height - 90),(width/2-40, height/2+60), 
                          (width/2+40, height/2+60), (width-50,height - 90)]], dtype=np.int32)
    cv.fillPoly(mask, roi, 255)
    roi = cv.bitwise_and(canny, mask)
    # cv.imshow("roi", roi)
    lines = cv.HoughLines(roi, rho, theta, threshold)

    line_img = np.zeros((frame.shape[0], frame.shape[1], 3), dtype=np.uint8)

    # 이거 지금 안옮김
    p1_l, p2_l, p1_r, p2_r = prev_p1_l, prev_p2_l, prev_p1_r, prev_p2_r

    if lines is not None:
        detect_l, detect_r = False, False  # Initialize line detect per frame
        count_l, count_r = 0, 0  # Reset count
        a_l_sum, b_l_sum, rho_l_sum = 0, 0, 0
        a_r_sum, b_r_sum, rho_r_sum = 0, 0, 0

        for line in lines:
            rho, theta = line[0]
            if 0.9 <= theta <= 1.1:  # Left lane angle range
                a_l = np.cos(theta)
                b_l = np.sin(theta)
                a_l_sum += a_l
                b_l_sum += b_l
                rho_l_sum += rho
                count_l += 1
                detect_l = True

            if 2.15 <= theta <= 2.45:  # Right lane angle range
                a_r = np.cos(theta)
                b_r = np.sin(theta)
                a_r_sum += a_r
                b_r_sum += b_r
                rho_r_sum += rho
                count_r += 1
                detect_r = True
        if count_l != 0:
        # Calculate the average a, b, rho values for both left and right lanes
            print('count_l' + str(count_l))
            a_l_avg, b_l_avg, rho_l_avg = a_l_sum / count_l, b_l_sum / count_l, rho_l_sum / count_l
        if count_r != 0:
            print('count_r' + str(count_r))
            a_r_avg, b_r_avg, rho_r_avg = a_r_sum / count_r, b_r_sum / count_r, rho_r_sum / count_r

        x1_r, y1_r, x2_r, y2_r = 0, 0, 0, 0
        x1_l, y1_l, x2_l, y2_l = 0, 0, 0, 0
        line_size = 2000

        if detect_l:

            x0_l = a_l_avg * rho_l_avg
            y0_l = b_l_avg * rho_l_avg
            x1_l = int(x0_l + line_size * (-b_l_avg))
            y1_l = int(y0_l + line_size * (a_l_avg))
            x2_l = int(x0_l - line_size * (-b_l_avg))
            y2_l = int(y0_l - line_size * (a_l_avg))
            p1_l = (x1_l, y1_l)
            p2_l = (x2_l, y2_l)
            # cv.line(line_img, (x1_l, y1_l), (x2_l, y2_l), (255, 0, 0), 2)  # Blue color
            color_l = (255, 0, 0)
        else: 
            # if prev_p1_l != 0 or prev_p2_l != 0:
            # cv.line(line_img, prev_p1_l, prev_p2_l, (0, 255, 255), 2)
            p1_l, p2_l = prev_p1_l, prev_p2_l   
            color_l = (0, 255, 255)


        if detect_r:
            x0_r = a_r_avg * rho_r_avg
            y0_r = b_r_avg * rho_r_avg
            x1_r = int(x0_r + line_size * (-b_r_avg))
            y1_r = int(y0_r + line_size * (a_r_avg))
            x2_r = int(x0_r - line_size * (-b_r_avg))
            y2_r = int(y0_r - line_size * (a_r_avg))
            p1_r = (x1_r, y1_r)
            p2_r = (x2_r, y2_r)
            # cv.line(line_img, (x1_r, y1_r), (x2_r, y2_r), (255, 0, 0), 2)  # Blue color
            color_r = (255, 0, 0)
        else:
            # if prev_p1_r != 0 or prev_p2_r != 0:
            # cv.line(line_img, prev_p1_r, prev_p2_r, (0, 255, 255), 2)
            p1_r, p2_r = prev_p1_r, prev_p2_r        
            color_r = (0, 255, 255)   
        
        vanishing_point = find_intersection(p1_l, p2_l, p1_r, p2_r)
        height = frame.shape[0]


        # 좌표값 다시 계산하기
        cv.circle(line_img, vanishing_point, 3, (0, 255, 0), 3)
        cv.line(line_img, vanishing_point, (p1_l[0], p1_l[1]), color_l, 2)
        cv.line(line_img, vanishing_point, (p2_r[0], p2_r[1]), color_r, 2)

    result = cv.addWeighted(frame, 0.7, line_img, 1, 0)
    return result, p1_l, p2_l, p1_r, p2_r

cap = cv.VideoCapture('road_straight_student.mp4')

width = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

cv.namedWindow('Line Detection', cv.WINDOW_NORMAL)
cv.createTrackbar('Canny Low', 'Line Detection', 50, 200, canny_threshold)
cv.createTrackbar('Canny High', 'Line Detection', 150, 200, canny_threshold)
cv.createTrackbar('Hough Threshold', 'Line Detection', 170, 200, hough_params)

rho = 3
theta = np.pi / 180

# 이전 프레임의 line 변수 초기화
prev_p1_l, prev_p2_l, prev_p1_r, prev_p2_r = None, None, None, None

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    
    canny_low = cv.getTrackbarPos('Canny Low', 'Line Detection')
    canny_high = cv.getTrackbarPos('Canny High', 'Line Detection')
    threshold = cv.getTrackbarPos('Hough Threshold', 'Line Detection')
    
    result, prev_p1_l, prev_p2_l, prev_p1_r, prev_p2_r = process_frame(frame, rho, theta, threshold, prev_p1_l, prev_p2_l, prev_p1_r, prev_p2_r)
    cv.imshow('Line Detection', result)
    
    if cv.waitKey(10) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
