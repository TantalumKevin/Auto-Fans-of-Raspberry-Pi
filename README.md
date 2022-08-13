# Auto Fans of Raspberry Pi

## 由来
这个项目说起来也没什么，不过是今天(2022.8.13)收到了新的树莓派散热外壳，便想到为其上面的风扇写一个温控，但是又因为电流过大反而不能控制了，就权当写着玩了，说不准以后用得到呢😂。

## 简介
本项目分为```C++```版和```Python```版，分别对应```main.cpp```以及```main.py```。
使用时可分别采用以下方法:
```c
//C++
//Way 1
sudo g++ main.cpp -o main -l bcm2835
sudo ./main

//Way 2,此方法自动运行
sudo ./first_run.sh
```

```Python
#Pyton
python main.py
```
如需后台运行可以使用nohup或其他适宜方法

## 注意
- ```C++```版本编译依赖于```BCM2835```库，相关安装方法请见[BCM官方网站](http://www.airspayce.com/mikem/bcm2835/)
- 风扇供电引脚为板载40Pin中:```P40-GPIO(+)```、```P39-GND(-)```，注意区分正负
