import numpy as np
import cv2

original = cv2.imread('sample_img/cat_01.jpg')

dimpixel = 7
color = 100
space = 100

filter = cv2.bilateralFilter(original, dimpixel, color, space)
cv2.imshow('filter', filter)
cv2.waitKey(0)
