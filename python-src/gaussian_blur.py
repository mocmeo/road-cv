import numpy as np
import cv2

original = cv2.imread('sample_img/cat_01.jpg')
matrix = (7, 7)

blur = cv2.GaussianBlur(original, matrix, 0)

cv2.imshow('blur', blur)
cv2.waitKey(0)

