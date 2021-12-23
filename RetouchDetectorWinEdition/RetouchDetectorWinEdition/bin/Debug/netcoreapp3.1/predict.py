#from tensorflow.keras.preprocessing import image
width = 256
height = 256
#img = image.load_img('C:\\Users\\cetin\\Desktop\\test.jpg', target_size=(height, width))

import sys
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing import image
from tensorflow.python.keras.applications.imagenet_utils import decode_predictions

from efficientnet.layers import Swish, DropConnect
from efficientnet.model import ConvKernalInitializer
from tensorflow.keras.utils import get_custom_objects

get_custom_objects().update({
    'ConvKernalInitializer': ConvKernalInitializer,
    'Swish': Swish,
    'DropConnect':DropConnect
})

model = load_model("orig_vs_brush.h5")
path = sys.argv[1]

img = image.load_img(path, target_size=(height, width))
x = image.img_to_array(img)
x = x.reshape((1,) + x.shape)
x /= 255.
result = model.predict([x])[0][0]
print(result)
