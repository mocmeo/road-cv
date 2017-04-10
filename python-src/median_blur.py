import numpy as np
import cv2

original = cv2.imread('sample_img/cat_01.jpg')
kernal = 5

median = cv2.medianBlur(original, kernal)

cv2.imshow('median', median)
cv2.waitKey(0)

