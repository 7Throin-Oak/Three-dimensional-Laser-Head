import cv2
import numpy as np
import serial
import time
import sys
from time import sleep

cap = cv2.VideoCapture(0)  # 使用默认摄像头
ser = serial.Serial('COM8', 9600, timeout=1)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # 转换图像为灰度
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 进行高斯模糊以减小噪音
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)

    # 使用霍夫圆变换检测圆环
    circles = cv2.HoughCircles(
        blurred,
        cv2.HOUGH_GRADIENT,
        dp=1,
        minDist=50,
        param1=50,
        param2=60,
        minRadius=20,
        maxRadius=100
    )

    # 如果找到了圆环
    if circles is not None:
        circles = np.uint16(np.around(circles))

        for i in circles[0, :]:
            # 画出圆环
            cv2.circle(frame, (i[0], i[1]), i[2], (0, 255, 0), 2)

            # 获取外接圆的圆心坐标
            center_coordinates = (i[0], i[1])
            cv2.circle(frame, center_coordinates, 5, (0, 0, 255), -1)

        # 在圆心处画出一个红点
        cv2.circle(frame, (i[0], i[1]), 5, (0, 0, 255), -1)


        x = i[0]
        y = i[1]
        y_ret = 60 - y / 7
        x_temp = 318 - x
        if x_temp >= 0:
            x_ret = x_temp / 8 + y_ret / 25
        elif x_temp < 0:
            x_ret = x_temp / 8 - y_ret / 12.5

        cv2.putText(frame, f' ({x_ret:.2f}, {y_ret:.2f})', (i[0] + 10, i[1] + 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5,
                    (0, 0, 0), 1)

        x_ret = int(x_ret)
        y_ret = int(y_ret)

        Rad_x = np.arctan(abs(x_ret) / 50)
        if x_ret >= 0:
            Angle_x = (180 * Rad_x) / 3.14
            Angle_x += 90
        elif x_ret < 0:
            Angle_x = (180 * Rad_x) / 3.14
            Angle_x = 90 - Angle_x

        y_2 = y_ret * 0.81 + 2.2
        if x_ret >= 0:
            Rad_y = np.arctan(y_2/50) - 0.001 * x
        else :
            Rad_y = np.arctan(y_2 / 50)
        Angle_y = (180 * Rad_y) / 3.14
        # x_ret_sh = hex(x_ret)
        # y_ret_sh = hex(y_ret)
        #
        # string = f"{x_ret_sh} {y_ret_sh}"
        # # while (data_send1!=0):
        #    # ser.write("FF")
        # ser.write(string.encode())

        # 假设 x_ret 和 y_ret 是您计算得到的坐标值
          # 示例坐标y
       # x_ret_sh = hex(x_ret+50)[2:]  # 转换为十六进制并移除"0x"
        #y_ret_sh = hex(y_ret)[2:]  # 转换为十六进制并移除"0x"
        Angle_x_hex = hex(round(Angle_x))
        Angle_y_hex = hex(round(Angle_y + 60))
        print(Angle_x_hex, Angle_y_hex)

        # 创建字符串
        string = f"{Angle_x_hex} {Angle_y_hex}"

        # 发送数据
        ser.write(string.encode())
        #time.sleep(0.5)
        # print(type(string.encode()))
        # print(size(string.encode()))
        # ser.write("0x12 0x34".encode())
        #  sleep(0.2)
        # tempx = int(ser.read(2).decode())
        # tempy = int(ser.read(2).decode())
        #
        # print(f"x:{Angle_x_hex}, {tempx}")
        # print(f"y:{Angle_y_hex}, {tempy}")
       # # print(string)
        # 显示图像
        cv2.imshow('Detected Circles', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()