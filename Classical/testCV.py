import cv2
img = cv2.imread("/home/ouyang/2.jpg")
win = cv2.namedWindow("test win", flags = 0)
cv2.imshow("test win",img)
cv2.waitKey(10000)

