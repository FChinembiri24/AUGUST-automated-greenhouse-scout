import cv2
import tensorflow as tf
from collections import Counter

# Load the saved model
model = tf.saved_model.load("MobileNetV2TomatoDiseaseDetection9635")

# Read image
image = cv2.imread("IMG_20230609_111752_743.jpg")

# Check for errors
if image is None:
    print("Error reading image")
    exit()

# Preprocess image for model input
input_image = image
input_image = cv2.resize(input_image, (224, 224))
input_image = cv2.cvtColor(input_image, cv2.COLOR_BGR2RGB)
input_image = input_image.astype('float32')
#input_image = input_image / 255.0
input_image = input_image.reshape(1, 224, 224, 3)

# Make a prediction
prediction = model(input_image)

# Compute index of maximum value along last axis
predicted_class = tf.argmax(prediction, axis=-1)[0]

# Convert predicted_class to integer
predicted_class = int(predicted_class)

# Display image and prediction
classes = ['Late_blight', 'Bacterial_spot', 'powdery_mildew', 'Early_blight', 'Tomato_mosaic_virus', 'Spider_mites Two-spotted_spider_mite', 'Target_Spot', 'Septoria_leaf_spot', 'healthy', 'Tomato_Yellow_Leaf_Curl_Virus', 'Leaf_Mold']
cv2.imshow('Frank', image)
print(classes[predicted_class])
cv2.putText(image, "Predicted class: {}".format(classes[predicted_class]), (10, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)

# Check for exit key
if cv2.waitKey(0) & 0xFF == ord('q'):
    cv2.destroyAllWindows()