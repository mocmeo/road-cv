import numpy as np
import cv2

original = cv2.imread('sample_img/cat_01.jpg')
rows = original.shape[0]
cols = original.shape[1]

M = np.float32([[1, 0, -150], [0,1,-70]])
shifted = cv2.warpAffine(original, M, (cols, rows))

cv2.imshow('shifted', shifted)
cv2.waitKey(0)
cv2.destroyAllWindows()
