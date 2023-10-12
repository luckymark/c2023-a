from sklearn.datasets import load_digits

digits = load_digits()
images = digits.images

# 二值化
thresh = images.mean() + 0.5 * images.std()
binary_images = images > thresh
binary_images = binary_images.astype(int)

# 输出为.dat
# 输出图像像素数据
with open('images.dat', 'wb') as f:
    for img in binary_images:
        for i in range(8):
            for j in range(8):
                pixel = 0 if img[i,j] == 0 else 1
                f.write(bytes([pixel]))

            # 输出标签
with open('labels.dat', 'wb') as f:
    for label in digits.target:
        f.write(bytes([label]))

