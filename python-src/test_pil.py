from PIL import Image

# img = Image.open('brick-house.png').convert('L')
# img.show()
# img.save('brick-house-gs', 'png')
# img.save('brick-image', 'jpeg')

img = Image.open('brick-house.png').convert('L')
size = 128, 128
#new_img = img.resize((256, 256))
#new_img.save('brick-house-256x256', 'png')

img.thumbnail(size)
img.save('brick-house-thumbnail.png')

