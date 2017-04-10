import numpy as np
import cv2

img = cv2.imread('sample_img/cat_01.jpg', -1)
img = cv2.imwrite('sample_img/mocmeo.png', img)
cv2.imshow('Original', img)
cv2.waitKey(0)

