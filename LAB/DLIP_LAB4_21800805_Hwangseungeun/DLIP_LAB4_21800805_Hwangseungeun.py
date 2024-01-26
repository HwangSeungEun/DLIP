""""
* author   :   Seung-Eun Hwang
* Date     :   2023 - 05 - 26
* Brief    :   DLIP LAB4 Parking management using deep learning
"""

import cv2
import torch
from ultralytics import YOLO
import numpy as np
import time

# 내 경로 설정을 해야 현재 내가 다운로드를 받은 ultralytics를 받아올 수 있다
import sys
sys.path.append('C:\\Users\erich\source\\repos\DLIP\LAB\DLIP_LAB3_21800805_Hwangseungeun')

# model = YOLO('yolov8l.pt')
model = YOLO('yolov8l-seg.engine')

def Trackbar(val):
    return val

# Open the video file
video_path = "DLIP_parking_test_video.avi"
cap     = cv2.VideoCapture(video_path)

# frame width height
width   = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height  = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
roi_region   = [[0,280], [1280,280], [1280,410], [0, 410]]

size_cut = 5000

num_frame   = 0
user_font    = cv2.FONT_HERSHEY_COMPLEX

box_dist_thr =  20

# 영상 저장 initialize
fourcc = cv2.VideoWriter_fourcc(*'XVID')
output_filename = 'output.mp4'
fps = 30
frame_size = (width, height)
out = cv2.VideoWriter(output_filename, fourcc, fps, frame_size)

with open('counting_result.txt', 'w') as f:
    f.write('')

# Loop through the video frames
while cap.isOpened():

    start_time = time.time()
    prev_time = start_time

    # Read a frame from the video
    ret, frame      = cap.read()
    

    num_max_park = 13

    if ret == True: # Run YOLOv8 inference on the frame

        mask = np.zeros_like(frame)
        cv2.fillPoly(mask, np.array([roi_region], dtype=np.int32), (255, 255, 255))
        mask_frame = cv2.bitwise_and(frame, mask)

        results = model(mask_frame, imgsz=640)
        result = results[0]
        len_result = len(result)
                    
        num_car = 0
        num_park = 0
        
        x_centers = []

        for idx in range(len_result):

            detection = result[idx]
            box = detection.boxes.cpu().numpy()[0]

            cls = int(box.cls[0])
            conf = box.conf[0]
            r = box.xyxy[0].astype(int) # box
            s = box.xywh[0].astype(int) # for box size
            size = s[2] * s[3]
            #         car         bus        truck
            if (cls == 2 or cls == 6 or cls == 7):
                x_cen = (r[0] + r[2])/2

                if any([abs(x_cen - prevcenX) < box_dist_thr for prevcenX in x_centers]):  
                    continue                      
                
                x_centers.append(x_cen)

                if size_cut < size: # 특정 위치 아래로 내려가면 주차를 하지 않은것으로 인식
                    # cv2.putText(frame, str(size), r[:2], user_font, 1, (0, 255, 0), 1)
                    cv2.rectangle(frame, r[:2], r[2:], (51, 153, 255), 2)
                    num_car += 1

        num_park = num_max_park - num_car

        # Write the current frame and parking numbers to the text file
        with open('counting_result.txt', 'a') as f:
            f.write(f'{num_frame},{num_car}\n')

        num_frame += 1

        # Break if num_frame exceeds 2500
        if num_frame > 2500:
            break

        diff_time = time.time() - prev_time
        
        if diff_time > 0:
            fps = 1 / diff_time

        cv2.putText(frame, f'Frame : {num_frame}', (20, 530), user_font, 1, (255, 255, 255), 2)
        cv2.putText(frame, f'FPS : {fps:.2f}', (20, 580), user_font, 1,  (255, 255, 255), 2)
        cv2.putText(frame, f'# of cars : {num_car}', (20, 630), user_font, 1,  (255, 255, 255), 2)
        cv2.putText(frame, f'# of available parking space : {num_park}', (20, 680), user_font, 1,  (255, 255, 255), 2)


        out.write(frame)

        # Display the annotated frame
        cv2.imshow("result", frame)
        # cv2.imshow("mask", mask_frame)

        k = cv2.waitKey(1) & 0xFF
        if k == ord('q')   :   break
        elif k == ord('s') :   cv2.waitKey()

    else:
        print("Video is terminated ...!")
        break


# Release the video capture object and close the display window
cap.release()
out.release()
cv2.destroyAllWindows()