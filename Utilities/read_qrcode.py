import pyzbar
import cv2
 
file_path = "image/QR2.jpg"
 
# Zbar 라이브러리로 QR코드를 인식하기위해서 openCV로 이미지를 그레이 스케일로 읽어옵니다
im = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)

qrcode_data = ""
 
#Zbar는 다중 QR 검출도 가능합니다
#인식된 QR 데이터들을 가져옵니다
scanner = pyzbar.Scanner()
results = scanner.scan(im)
for result in results:
    qrcode_data = result.data
 
# QR 코드가 인식이 되지 않았다면
# QR Code not detected
if(qrcode_data=="null"):
    print("QR Code not detected")
else:
    # QR 코드가 인식이 되었다면
    # 인식된 QR 코드의 데이터를 출력해준다
   print("Decoded Data : {}".format(qrcode_data))