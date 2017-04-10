from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.cm
import numpy as np

# read image to array
my_img = Image.open("piano-cat.jpg").convert('L')
img = np.array(my_img, 'f')

# plot the image
#plt.figure(dpi=192)
#plt.gray()
#plt.imshow(img)

# some points
#x = [100,100,400,400]
#y = [200,500,200,500]
#
#plt.plot(x, y, 'r*')
#plt.plot(x[:2], y[:2])
#plt.savefig('mocmeo.png', dpi=192)
#
## Add title and show the plot 
#plt.title("Plotting: Brick-house.png")
#plt.show()

#plt.figure(dpi=192)
#plt.contour(img, origin='image')
#plt.axis('equal')
#plt.axis('off')
#plt.show()
#
#plt.figure(dpi=192)
#plt.hist(img.flatten(), 128)
#plt.show()

plt.figure(dpi=192)
plt.imshow(img, cmap=matplotlib.cm.Greys_r)
#print "Please click 3 points"
#x = plt.ginput(3)
#print "You click", x

print img.shape, img.dtype
plt.show()






