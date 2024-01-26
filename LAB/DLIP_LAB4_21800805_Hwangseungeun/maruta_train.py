# 내 경로 설정을 해야 현재 내가 다운로드를 받은 ultralytics를 받아올 수 있다
import sys
sys.path.append('C:\\Users\\erich\\source\\repos\\DLIP\\Tutorial\\yolov8')

from ultralytics import YOLO

model = YOLO('yolov8l.pt')

if __name__ == '__main__':
    model.train(data='C:\\Users\\erich\\source\\repos\\DLIP\\Tutorial\\yolov8\\mask_box\\data.yaml',
                epochs=100, patience=50, batch=10,
                device=0, half=True)


