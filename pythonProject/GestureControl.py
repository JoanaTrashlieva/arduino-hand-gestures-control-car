import cv2
import mediapipe as mp
import serial
import HTModule as ht

serialPath = '/dev/tty.usbserial-14120'
bluetoothConnection = '/dev/tty.Bluetooth-Incoming-Port'
ser = serial.Serial(serialPath, 9600)
print("...Arduino detected") #print statement #1

# Camera window size
wCam, hCam = 640, 480

cap = cv2.VideoCapture(0)
cap.set(3, wCam)
cap.set(4, hCam)

mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils
detector = ht.gestureControl(detectionCon=0.7)
tipIds = [4, 8, 12, 16, 20]

# def led_on_off():


while True:
    success, img = cap.read()
    img = detector.findShape(img)
    lmList = detector.findPosition(img, draw=False)

    if len(lmList) != 0:
        fingers = []

        # # Thumb position (folded or not)
        # if lmList[tipIds[0]][1] < lmList[tipIds[0] - 1][1]:
        #     fingers.append(1)
        # else:
        #     fingers.append(0)

        # Thumb position (above palm or not)
        if lmList[tipIds[0]][1] < lmList[tipIds[0] - 1][1]:
            fingers.append(1)
        else:
            fingers.append(0)

        # The rest of the fingers (folded or not)
        for id in range(1, 5):
            if lmList[tipIds[id]][2] <= lmList[tipIds[id] - 2][2]:
                fingers.append(1)
            else:
                fingers.append(0)

        # print(fingers)
        # [0,0,0,0,0]

        s = ''.join(str(i) for i in sorted(fingers))
        # print(s)

        if '00000' in s:
            print("Stop")
            ser.write(b'S')

        if '11111' in s:
            print("Going Forward")
            ser.write(b'F')

        if '00001' in s:
            print("Going back")
            ser.write(b'B')

        if '00011' in s:
            print("Turning Left")
            ser.write(b'L')

        if '00111' in s:
            print("Turning Right")
            ser.write(b'R')

    cv2.imshow("Image", img)
    cv2.waitKey(1)
