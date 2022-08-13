#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <bcm2835.h>
#include <ctime> 
#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define PIN RPI_BPLUS_GPIO_J8_40
#define tl 35
#define th 75

using namespace std;

void delay(double time)
{
    if(time>2147)
    {
        delay(2147.0);
        delay(time-2147);
    }
    else
    {
        clock_t  now = clock();
        //cout<<CLOCKS_PER_SEC<<endl;
        //cout<<now<<endl;
        while(((double)(clock() - now))/CLOCKS_PER_SEC < time)
            ;//cout<<((double)(clock() - now))/CLOCKS_PER_SEC<<endl;
        //cout<<CLOCKS_PER_SEC<<endl;
    }
}

double maap(double temp)
{
    if(temp<tl)
        return 0.0;
    if(temp>th)
        return 100.0;
    else
        return (temp-tl)/(th-tl)*100;
}

int main(void)
{
    if (!bcm2835_init())
    {
        ofstream log;
        log.open("./log",ios::app);
        log << "GPIO Error : Cannot open GPIO!" <<endl;
        log.close();
	    return 1;
    }
    bcm2835_gpio_fsel (PIN, BCM2835_GPIO_FSEL_OUTP);

    while(1)
    {
        ifstream file_temp;
        file_temp.open(TEMP_PATH, ios::in );
        if(!file_temp.is_open())
        {
            //cout<<"文件打开失败"<<endl;
            ofstream log;
            log.open("./log",ios::app);
            log << "File Error : Cannot open file!" <<endl;
            log.close();
            bcm2835_close();
            return 2;
        }
        double temp = 0;
        char data[10];
        file_temp >> data; 
        // 关闭文件
        file_temp.close();
        // 输出样例:39166\n
        // 转换为浮点数打印
        temp = atoi(data) / 1000.0;
        if (temp == 0)
        {
            ofstream log;
            log.open("./log",ios::app);
            log << "Data Error : Cannot get the correct data!" <<endl;
            log.close();
            bcm2835_close();
            return 3;
        }
        //cout<< data<<endl;
        //cout<<"temp="<<temp<<endl;
        //PWM:soft 
        //f=1khz
        //duty->temp
        int f = 1000, sec = 5*60;
        double speed = maap(temp);
        for(int i = 0;i<f*sec;i++)
        {
            bcm2835_gpio_set (PIN);
            delay(speed/f);
            bcm2835_gpio_clr (PIN);
            delay((100-speed)/f);
        }
    }
    
    bcm2835_close();
    return 0;
}