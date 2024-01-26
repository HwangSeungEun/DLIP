import cv2
import torch
from ultralytics import YOLO

# 내 경로 설정을 해야 현재 내가 다운로드를 받은 ultralytics를 받아올 수 있다
import sys
sys.path.append('C:\\Users\erich\source\\repos\DLIP\LAB\yolov8')

model = YOLO('yolov8x.pt')
model.predict(source='DLIP_parking_test_video.avi', save=True, imgsz=640, conf=0.5, show=True, half=True)








# def predict(cfg=DEFAULT_CFG, use_python=True):
#     """Runs YOLO object detection on an image or video source."""
#     # model = cfg.model or 'yolov8l-seg.pt'
#     model = 'D:\HADA\HADA_3rd\Camera\yolov8\\runs\segment\\train17\weights\\best.pt'
#     # source = cfg.source if cfg.source is not None else ROOT / 'assets' if (ROOT / 'assets').exists() \
#     #     else 'https://ultralytics.com/images/bus.jpg'
    
#     source = 0
#     show = True
#     conf = 0.7

#     args = dict(model=model, source=source, show = show, conf = conf, stream = True, vid_writer = True)
#     if use_python:
#         from ultralytics import YOLO
#         YOLO(model)(**args)
#     else:
#         predictor = SegmentationPredictor(overrides=args)
#         predictor.predict_cli()



