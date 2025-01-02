import cv2
import mediapipe as mp
import serial
import time


arduino = serial.Serial(port='COM12', baudrate=9600, timeout=1)
time.sleep(2)  

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

def calculate_finger_position(hand_landmarks):
    positions = []
    for i in [4, 8, 12, 16, 20]:  
        tip_y = hand_landmarks.landmark[i].y
        base_y = hand_landmarks.landmark[i - 2].y
        if tip_y < base_y:
            positions.append(0)  
        else:
            positions.append(180)  
    return positions

cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)  
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = hands.process(rgb_frame)

    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            positions = calculate_finger_position(hand_landmarks)
            data_str = ','.join(map(str, positions)) + '\n'
            arduino.write(data_str.encode('utf-8'))  

    cv2.imshow('Hand Tracking', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
