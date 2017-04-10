from PIL import Image
import os, glob
import numpy as np
import matplotlib.pyplot as plt

def list_files(path):
    for f in os.listdir(path):
        print f

def get_imlist(path):
    """ Returns a list of filenames for
    all jpg images in a directory. """
    return [os.path.join(path, f) for f in os.listdir(path) if f.endswith('.png')]

def imresize(im, sz):
    """ Resize an image array using PIL"""
    pil_im = Image.fromarray(np.uint8(im))
    return pil_im.resize(sz)

def histeq(im,nbr_bins=256):
    """ Histogram equalization of a grayscale image. """
    # get image histogram
    imhist,bins = np.histogram(im.flatten(),nbr_bins,normed=True)
    cdf = imhist.cumsum() # cumulative distribution function
    cdf = 255 * cdf / cdf[-1] # normalize

    # use linear interpolation of cdf to find new pixel values
    im2 = np.interp(im.flatten(),bins[:-1],cdf)
    return im2.reshape(im.shape), cdf


# print get_imlist('/home/mocmeo/Images')

#for infile in get_imlist("/home/mocmeo/Images"):
#    outfile = os.path.splitext(infile)[0] + ".jpg"
#    if infile != outfile:
#        try:
#            Image.open(infile).save(outfile)
#        except IOError:
#            print "Cannot convert", infile

size = 128, 128
box = (100, 100, 400, 400)

#for infile in glob.glob("*.png"):
#    f, ext = os.path.splitext(infile)
#    im = Image.open(infile)
#    im.thumbnail(size)
#    im.save(f + '-thumbnail', 'JPEG')

#for infile in glob.glob("*.png"):
#    pil_im = Image.open(infile)
#    region = pil_im.crop(box)
#    region = region.transpose(Image.ROTATE_180)
#    pil_im.paste(region, box)
#    pil_im.save('brick-house-rotate.png')

pil_img = Image.open("/home/mocmeo/road-cv/sample_img/cat06.jpg")
pil_img = imresize(pil_img, (600, 450))
pil_img.save("cat_06_sz.jpg")
