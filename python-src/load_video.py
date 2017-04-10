import numpy as np
import cv2

cap = cv2.VideoCapture('sample_vid/road1.avi')
fourcc = cv2.VideoWriter_fourcc(*'XVID')
fps = 30
frame_size = (720, 576)
out = cv2.VideoWriter('sample_vid/output.avi',fourcc, fps, frame_size)

while (cap.isOpened()):
    ret, frame = cap.read()
    out.write(frame)
    cv2.imshow('Video', frame)
    if cv2.waitKey(50) & 0xFF == ord('q'):
        break

cap.release()
out.release()
cv2.destroyAllWindows()

