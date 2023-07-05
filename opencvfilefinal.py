import cv2
import tensorflow as tf
from collections import Counter

# Load the saved model
model = tf.saved_model.load("MobileNetV2TomatoDiseaseDetection9635")

# Set up video capture
cap = cv2.VideoCapture(0)
# Set up object tally
tally = Counter()


while True:
    # Read frame from video capture
    ret, frame = cap.read()

    # Preprocess frame for model input
    input_frame = frame
    input_frame = cv2.resize(frame, (224, 224))
    input_frame = cv2.cvtColor(input_frame, cv2.COLOR_BGR2RGB)
    input_frame = input_frame.astype('float32')
    #input_frame = input_frame / 255.0
   
    input_frame = input_frame.reshape(1, 224, 224, 3)

    prediction = model(input_frame)

    # Compute index of maximum value along last axis
    predicted_class = tf.argmax(prediction, axis=-1)[0]

   # Convert predicted_class to integer
    predicted_class = int(predicted_class)
    classes = ['Bacterial_spot','Early_blight','Late_blight','Leaf_Mold','Septoria_leaf_spot','Spider_mites Two-spotted_spider_mite','Target_Spot','Tomato_Yellow_Leaf_Curl_Virus','Tomato_mosaic_virus','healthy','powdery_mildew']
      
    # Update tally
    tally[predicted_class] += 1
    # Display frame and tally
    cv2.putText(frame, "Predicted class: {}".format(classes[predicted_class]), (100, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
    cv2.imshow('Frank', frame)
    confidence = prediction[0][predicted_class]
    if(confidence > 0.5):
        classes = ['Bacterial_spot','Early_blight','Late_blight','Leaf_Mold','Septoria_leaf_spot','Spider_mites Two-spotted_spider_mite','Target_Spot','Tomato_Yellow_Leaf_Curl_Virus','Tomato_mosaic_virus','healthy','powdery_mildew']
        print(classes[predicted_class])
        print(tally)

    # Check for exit key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release video capture and destroy windows
cap.release()
cv2.destroyAllWindows()