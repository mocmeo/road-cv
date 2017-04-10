import cv2
import matplotlib.pyplot as plt
import matplotlib.cm
import numpy as np

original = cv2.imread('doremon.jpg')
result = cv2.imread('doremon.jpg')
img = cv2.cvtColor(original, cv2.COLOR_BGR2GRAY)

threshold_value = 65

ret,thresh = cv2.threshold(img, threshold_value, 255, cv2.THRESH_BINARY_INV)
image, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)


for cnt in contours:
    hull = cv2.convexHull(cnt)
    cv2.drawContours(result, [cnt], -1, 255, -1)
    cv2.drawContours(result, [hull], -1, 255, -1)


plt.figure(dpi=192)
plt.subplot(121), plt.imshow(original)
plt.subplot(122), plt.imshow(thresh)
plt.show()

print cv2.moments(contours[0])


