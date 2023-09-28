import numpy as np
import torch

images = open('train-images-idx3-ubyte','rb')
images.read(16)
img_data = images.read()

img_array = np.frombuffer(img_data, dtype=np.uint8).reshape(-1,28,28)
labels = open('train-labels-idx1-ubyte','rb')
labels.read(8)
label_data = labels.read()

label_array = np.frombuffer(label_data, dtype=np.uint8)
images_8x8 = []
for img in img_array:
    img_8x8 = img.reshape(28,28)//4
    img_8x8 = (img_8x8 > 0) * 1
    images_8x8.append(img_8x8)

data = torch.utils.data.TensorDataset(
    torch.tensor(images_8x8), torch.tensor(label_array))