import cv2
import mediapipe as mp

# from GestureControl import hands

class gestureControl():
    def __init__(self, mode=False, maxHands=1, modelComplexity=1, detectionCon=0.5, trackCon=0.5):
        self.mode = mode
        self.maxHands = maxHands
        self.modelComplex = modelComplexity
        self.detectionCon = detectionCon
        self.trackCon = trackCon

        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands(self.mode, self.maxHands, self.modelComplex, self.detectionCon,
                                        self.trackCon)
        self.mpDraw = mp.solutions.drawing_utils

    def findShape(self, img, draw = True):
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        self.results = self.hands.process(imgRGB)
        # print(self.results.multi_hand_landmarks)

        if self.results.multi_hand_landmarks:
            # get the info from each hand
            for handLandmarks in self.results.multi_hand_landmarks:
                if draw:
                    self.mpDraw.draw_landmarks(img, handLandmarks, self.mpHands.HAND_CONNECTIONS)

        return img

    def findPosition(self, img, handNo = 0, draw = True):

        landMarks = []
        if self.results.multi_hand_landmarks:
            whichHand = self.results.multi_hand_landmarks[handNo]
            # which hand are we talking about
            for id, ln in enumerate(whichHand.landmark):
                # print(id, ln)

                # width and height
                h, w, c = img.shape

                # center
                cx, cy = int(ln.x * w), int(ln.y * h)  # issue - getting for all

                # print(id, cx, cy)
                landMarks.append([id, cx, cy])
                # define a specific point
                if id == 0:
                    cv2.circle(img, (cx, cy), 15, (255, 0, 255), cv2.FILLED)

        return landMarks

def main():
    cap = cv2.VideoCapture(0)
    shape = gestureControl()

    while True:
        success, img = cap.read()
        img = shape.findShape(img)

        landMarks = shape.findPosition(img)
        if len(landMarks) != 0:
            print(landMarks[7])

        cv2.imshow("Image", img)
        cv2.waitKey(1)


if __name__ == "__main__":
    main()
