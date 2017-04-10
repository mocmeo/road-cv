import cv2
import numpy as np
import math

cap = cv2.VideoCapture('sample_vid/road1.avi')
fourcc = cv2.VideoWriter_fourcc(*'XVID')
fps = 30
width = int(cap.get(3))
height = int(cap.get(4))
frame_size = (width, height)
out = cv2.VideoWriter('sample_vid/output.avi',fourcc, fps, frame_size)


# Region of Interest
roiWidth = width
roiHeight = height
roiX = 0
roiY = int(height * 2/3)

#Process for lines on the road
def slope(vx1, vx2, vy1, vy2):         #Parameters to calculate slope
    m=float(vy2-vy1)/float(vx2-vx1)        #Slope equation
    theta = math.atan(m)                  #calculate the slope angle
    return theta*(180/np.pi)              #Calculated angle in radians

# Image processing
while (cap.isOpened()):
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)            

    #Using histogram equalization to increase image contrast
    hist = cv2.equalizeHist(gray)                              
    video = cv2.cvtColor(gray,cv2.COLOR_GRAY2BGR)
    cv2.rectangle(video, (roiX, roiY), (width, height), (255, 0, 0),1) 

    # Change color space to extract lane color
    hsv = cv2.cvtColor(video, cv2.COLOR_BGR2HSV)              
    grayROI  = hsv[roiY:roiY+roiHeight, roiX:roiX+roiWidth]  
    low_white = np.array([0,0,90],dtype=np.uint8)            
    high_white = np.array([255,255,255],dtype=np.uint8)      
    mask = cv2.inRange(grayROI,low_white,high_white)          


    #Length for lines to find
    minLineLength = 100
    maxLineGap = 40
    lines = cv2.HoughLinesP(mask,1,np.pi/180,10,minLineLength,maxLineGap)
    frameClone = frame.copy()
    for x1,y1,x2,y2 in lines[0]:
      if (round(x2-x1)!=0):
            arctan = slope(x1,x2,y1,y2)
            if (round(arctan>=round(-80)) and round(arctan<=round(-30))):

                cv2.rectangle(frameClone, (x1 + roiX, y1 + roiY), (x2 + roiX, y2 + roiY), (0, 255, 0), 3, lineType=8, shift=0)
            if (round(arctan>=round(30)) and round(arctan<=round(80))):
                #cv2.line(frameClone,(x1 + roiX,y1 + roiY),(x2 + roiX,y2 + roiY),(0, 255, 0),2)
                cv2.rectangle(frameClone, (x1 + roiX, y1 + roiY), (x2 + roiX, y2 + roiY), (0, 255, 0), 3, lineType=8, shift=0)
                #print x1 + roiX

    cv2.imshow('Video', frameClone)
    out.write(frameClone)
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break


cap.release()
out.release()
cv2.destroyAllWindows()



