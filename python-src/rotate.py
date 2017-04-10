import cv2
import numpy as np

original = cv2.imread('sample_img/cat_01.jpg')
rows = original.shape[0]
cols = original.shape[1]
center = (cols/2, rows/2)
angle = -90;

M = cv2.getRotationMatrix2D(center, angle, 0.5)
rotated = cv2.warpAffine(original, M, (cols, rows))

cv2.imshow('rotated', rotated)
cv2.waitKey(0)
cv2.destroyAllWindows()
