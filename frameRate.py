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

    # Check for errors
    if not ret:
        print("Error reading frame")
        break

    # Preprocess frame for model input
    input_frame = frame
    input_frame = cv2.resize(frame, (224, 224))
    input_frame = cv2.cvtColor(input_frame, cv2.COLOR_BGR2RGB)
    input_frame = input_frame.astype('float32')
    #input_frame = input_frame / 255.0
    input_frame = input_frame.reshape(1, 224, 224, 3)

    # Make a prediction
    prediction = model(input_frame)

    # Check for unexpected input
    if prediction.shape[1] != 1000:
        print("Unexpected input shape")
        continue

    # Compute index of maximum value along last axis
    predicted_class = tf.argmax(prediction, axis=-1)[0]

    # Convert predicted_class to integer
    predicted_class = int(predicted_class)

    # Update tally
    tally[predicted_class] += 1

    # Display frame and tally
    cv2.imshow('Frank', frame)
    cv2.putText(frame, "Frame rate: {:.2f}".format(cap.get(cv2.CAP_PROP_FPS)), (10, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)
    print(tally)

    # Check for exit key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release video capture and destroy windows
cap.release()
cv2.destroyAllWindows()
