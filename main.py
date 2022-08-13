import RPi.GPIO as gpio

'''
gpio.setmode(gpio.BOARD)
#使用PWM类定义EN使能端,PWM频率为1kHz
gpio.setup(40, gpio.OUT)
fans = gpio.PWM(40,1000)
#占空比为0,确保风扇停转
fans.start(0)
'''
file = open("/sys/class/thermal/thermal_zone0/temp")
# 读取结果，并转换为浮点数
temp = float(file.read()) / 1000
# 关闭文件
file.close()
#print("temp="+str(temp))