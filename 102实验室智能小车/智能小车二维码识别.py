import sensor, image, time, math, struct,pyb
import json
from pyb import UART
from pyb import Servo
from pyb import UART
import lcd
uart = pyb.UART(3, 115200)  #串口3，波特率115200
uart.init(115200, bits=8, parity=None, stop=1)  #8位数据位，无校验位，1位停止位
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) # can be QVGA on M7...
sensor.skip_frames(30)
sensor.set_auto_gain(False) # must turn this off to prevent image washout...
lcd.init() # Initialize the lcd screen.

class Line(object):
    x = 0
line1 = Line()


def UART_Sent():
    data_pack = bytearray([line1.x])
    uart.write(data_pack)    #打印所有所需数据
    print("OPENMV发送的数据：",data_pack)

while(True):
    img = sensor.snapshot()
    img.lens_corr(1.8) # strength of 1.8 is good for the 2.8mm lens.
    lcd.display(img) # Take a picture and display the image.
    for code in img.find_qrcodes():
        img.draw_rectangle(code.rect(), color = (250, 0, 0),thickness = 4)
        img.draw_cross(int(code.x()+code.w()/2), int(code.y()+code.h()/2),
        size = 10,color = (250, 0, 0),thickness = 4)
        lcd.display(img)
        line1.x = int(code[4])
        UART_Sent()

