import numpy as np
import cv2

original = np.zeros((500, 500, 3), dtype='uint8')
cv2.rectangle(original, (0, 0), (500, 150), 
        (134, 154, 232), 3, lineType=8, shift=0)
cv2.line(original, (100, 100), (300, 300), (0, 0, 255))


color = (255, 255, 255)
cv2.circle(original, (250, 250), 50, color)

font = cv2.FONT_HERSHEY_DUPLEX
cv2.putText(original, 'Mocmeo', (100, 100), font, 2, 
            (255, 255,255), 3, cv2.LINE_8)
cv2.imshow('dark', original)
cv2.waitKey(0)
