import numpy as np
import cv2

original = cv2.imread('sample_img/brick-house.png', 0)
threshold_val1 = 250
threshold_val2 = 300

canny = cv2.Canny(original, threshold_val1, threshold_val2)

cv2.imshow('canny', canny)
cv2.waitKey(0)

