import RPi.GPIO as gpio, time, sys


gpio.setmode(gpio.BOARD)
#使用PWM类定义EN使能端,PWM频率为1kHz
gpio.setup(40, gpio.OUT)
fans = gpio.PWM(40,1000)
#占空比为0,确保风扇停转
fans.start(0)

#while True:
try:
    with open("/sys/class/thermal/thermal_zone0/temp",'r') as file:
        # 读取结果，并转换为浮点数
        #print(file.read())
        temp = float(file.read()) / 1000
    #print(temp)
    # 35-75+ -> 0-100
    if temp == 0:
        raise Exception('温度文件异常')
    speed = int((temp - low)/(high-low)*100) if temp<high and temp >low else 0 if temp<=low else 1
    fans.ChangeDutyCycle(speed)
except :
    with open('./log','a') as file:
        file.writelines([time.ctime(),'\n',sys.exc_info()[0],'\n'])
    break

gpio.cleanup()

#print("temp="+str(temp))