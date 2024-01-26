import cv2 as cv
import numpy as np
import time
import math

color_b = (255, 0, 0)
color_r = (0, 0, 255)
color_g = (0, 255, 0)
color_y = (0, 255, 255)
color_p = (255, 0, 255)



class Linedetect:

    width : int     = 0
    height : int    = 0
    ssibal : int    = 0

    def __init__ (self):
        self.gray               = None
        self.blur               = None
        self.thresh             = None
        self.canny              = None
        self.mask               = None
        self.roi                = None
        self.lines              = None
        self.hough_rho:int      = 1
        self.hough_theta:float  = np.pi / 180
        self.line_img           = None
        self.canny_low:int      = 100
        self.canny_high:int     = 200
        self.hough_thr :int     = 60
        self.binary_thr :int    = 160
        # self.rho                = None 
        # self.theta              = None
        self.slope:float        = 0.0
        self.lines_pos          = []
        self.lines_neg          = []
        self.avg_rho_pos:float  = 0.0
        self.avg_theta_pos:float  = 0.0
        self.avg_rho_neg:float  = 0.0
        self.avg_theta_neg:float  = 0.0
        self.prev_line_pos     = [0, 0]
        self.prev_line_neg     = [0, 0]
        self.intersection:tuple (int, int) = (0,0)
        self.line_point_pos    = [0, 0]  
        self.line_point_neg    = [0, 0]  
        self.color_pos         = [0, 0, 0]
        self.color_neg         = [0, 0, 0]
        self.color_ven         = [0, 0, 0]
        self.prev_x1 = 0
        self.prev_y1 = 0
        self.prev_x2 = 0
        self.prev_y2 = 0
         
        self.result            = None
               
    def Initialize(self, cap):        
        self.width = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
        self.height   = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

        cv.namedWindow('Track bar', cv.WINDOW_NORMAL)
        cv.createTrackbar('Canny Low', 'Track bar', self.canny_low, 200, self.Trackbar)
        cv.createTrackbar('Canny High', 'Track bar', self.canny_high, 200, self.Trackbar)
        cv.createTrackbar('Hough Threshold', 'Track bar', self.hough_thr, 200, self.Trackbar)
        cv.createTrackbar('Binary Threshold', 'Track bar', self.binary_thr, 200, self.Trackbar)

        self.fourcc = cv.VideoWriter_fourcc(*'XVID')
        self.output_filename = 'output.mp4'
        self.fps = 30
        self.frame_size = (self.width, self.height)
        self.out = cv.VideoWriter(self.output_filename, self.fourcc, self.fps, self.frame_size)

    def Trackbar(self, val):
        return val


    def Preprocessing(self, _frame):
        self.canny_low = cv.getTrackbarPos('Canny Low', 'Track bar')
        self.canny_high = cv.getTrackbarPos('Canny High', 'Track bar')
        self.hough_thr = cv.getTrackbarPos('Hough Threshold', 'Track bar')
        self.binary_thr = cv.getTrackbarPos('Binary Threshold', 'Track bar')

        self.gray = cv.cvtColor(_frame, cv.COLOR_BGR2GRAY)
        # self.blur = cv.GaussianBlur(self.gray, (5, 5), 0)
        _, self.thresh = cv.threshold(self.gray, self.binary_thr, 255, cv.THRESH_BINARY)  
        self.canny = cv.Canny(self.thresh, self.canny_low, self.canny_high)
        
    def ROI(self):
        
        self.mask = np.zeros_like(self.canny)
        # self.roi  = np.array([[(50, self.height - 90),(self.width/2-40, self.height/2+50), 
        #                   (self.width/2+20, self.height/2+50), (self.width-50,self.height - 90)]], dtype=np.int32)
        self.roi  = np.array([[(50, self.height - 90),(self.width/2, self.height/2+60), 
                          (self.width/2, self.height/2+60), (self.width-50,self.height - 90)]], dtype=np.int32)
        cv.fillPoly(self.mask , self.roi, 255)
        self.roi = cv.bitwise_and(self.canny, self.mask)

    def getLines(self, _frame):
        self.lines = cv.HoughLines(self.roi, self.hough_rho, self.hough_theta, self.hough_thr)
        
        # 넘파이는 height 다음 width  입니다!!!
        self.line_img = np.zeros((self.height, self.width, 3), dtype=np.uint8)
        self.lines_pos = []
        self.lines_neg = []
        if self.lines is not None and len(self.lines) > 0:
            for i in range(len(self.lines)):
                for rho, theta in self.lines[i]:

                    self.slope = np.tan(theta)
                    if(self.slope > 0): 
                        self.lines_pos.append((rho, theta))
                    else:
                        self.lines_neg.append((rho, theta))
                        
                    line_size = 2000
                    a = np.cos(theta)
                    b = np.sin(theta)
                    x0 = a * rho
                    y0 = b * rho
                    x1 = int(x0 + line_size * (-b))
                    y1 = int(y0 + line_size * (a))
                    x2 = int(x0 - line_size * (-b))
                    y2 = int(y0 - line_size * (a))               
                    cv.line(self.line_img, (x1, y1), (x2, y2), color_p, 2)  # Blue color
                    

            if len(self.lines_pos) > 0:
                self.avg_rho_pos, self.avg_theta_pos = np.mean(self.lines_pos, axis = 0)
                # print('theta_pos: ' + str(self.avg_theta_pos * 180 / np.pi))
                self.prev_line_pos = (self.avg_rho_pos, self.avg_theta_pos)
                self.color_pos = color_g
                # print("Using current pos line:", self.prev_line_pos)

            elif self.prev_line_pos is not None:
                self.avg_rho_pos, self.avg_theta_pos = self.prev_line_pos
                self.color_pos = color_y
                # print("Using previous pos line:", self.prev_line_pos)
            
            if len(self.lines_neg) > 0:
                self.avg_rho_neg, self.avg_theta_neg = np.mean(self.lines_neg, axis = 0)
                # print('theta_neg: ' + str(self.avg_theta_neg * 180 / np.pi))
                self.prev_line_neg = (self.avg_rho_neg, self.avg_theta_neg)
                self.color_neg = color_g
                # print("Using current neg line:", self.prev_line_neg)

            elif self.prev_line_neg is not None:
                self.avg_rho_neg, self.avg_theta_neg = self.prev_line_neg
                self.color_neg = color_y
                # print("Using previous neg line:", self.prev_line_neg)

        self.intersection = self.Intersection(self.prev_line_pos, self.prev_line_neg)
        self.line_point_pos, self.line_point_neg = self.drawLines(self.prev_line_pos, self.prev_line_neg)
        # print('line point pos: ' + str(self.line_point_pos))
        # print('line point neg: ' + str(self.line_point_neg))

        if self.intersection is not None:
            cv.circle(self.line_img, self.intersection,  3, (0, 255, 0), 3)
            cv.line(self.line_img, self.intersection, self.line_point_pos, self.color_pos, 5)
            cv.line(self.line_img, self.intersection, self.line_point_neg, self.color_neg, 5)
            mask = np.zeros_like(_frame)
            pts = np.array([self.intersection, self.line_point_pos, self.line_point_neg], dtype=np.int32)
            cv.fillConvexPoly(mask, pts, (0, 255, 0))
            self.result = cv.addWeighted(_frame, 0.7, mask, 0.3, 0)
            self.result = cv.addWeighted(self.result, 0.7, self.line_img, 1, 0)
            self.showVid("drawlines", self.result)
 
    def Intersection(self, line1, line2):

        rho1, theta1 = line1
        rho2, theta2 = line2

        A = np.array([
            [np.cos(theta1), np.sin(theta1)],
            [np.cos(theta2), np.sin(theta2)]
        ])
        b = np.array([[rho1], [rho2]])
        x0, y0 = np.linalg.solve(A, b)
        x0, y0 = int(np.round(x0)), int(np.round(y0))
    
        return [x0, y0]    
       
    def drawLines(self, line1, line2):
        extended_y = self.height + 100

        rho1, theta1 = line1
        m1 = -np.cos(theta1) / np.sin(theta1)
        b1 = rho1 / np.sin(theta1)

        if not np.isinf(m1) and not np.isnan(m1):
            x1 = int((extended_y - b1) / m1)
            y1 = extended_y
            self.prev_x1 = x1
            self.prev_y1 = y1
        else:
            x1 = self.prev_x1
            y1 = self.prev_y1

        rho2, theta2 = line2
        m2 = -np.cos(theta2) / np.sin(theta2)
        b2 = rho2 / np.sin(theta2)

        if not np.isinf(m2) and not np.isnan(m2):
            x2 = int((extended_y - b2) / m2)
            y2 = extended_y
            self.prev_x2 = x2
            self.prev_y2 = y2
        else:
            x2 = self.prev_x2 
            y2 = self.prev_y2

        return (x1, y1), (x2, y2)

    def showVid(self, _name:(str), _vid):
        cv.imshow(_name, _vid)

    def outResult(self, _image):
        self.out.write(_image)

    def closeAll(self):
        self.out.release()

def main():

    LD = Linedetect()

    # cap = LD.getVideo('road_straight_student.mp4')
    cap = cv.VideoCapture('road_lanechange_student.mp4')
    LD.Initialize(cap)


    while(cap.isOpened()):
        
        ret, frame = cap.read()
        
        if not ret:
            break
            
        # src show check
        LD.showVid("src", frame)
        
        LD.Preprocessing(frame)
        # LD.showVid("canny", LD.canny)

        LD.ROI()
        LD.showVid("roi", LD.roi)
        
        LD.getLines(frame)

        LD.outResult(LD.result)

        k = cv.waitKey(10) & 0xFF
        if k == ord('q')   :   break
        elif k == ord('s') :   cv.waitKey()

    LD.closeAll()


if __name__ == "__main__":
    main()