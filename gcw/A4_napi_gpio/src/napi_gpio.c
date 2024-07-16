#include <stdio.h>      //c基本头文件
//#include <stdlib.h>    //goto函数
#include <stdint.h>    //uint8_t
#include <unistd.h>     //sleep


#include "hdf_log.h"    //路径：    "//drivers/hdf_core/interfaces/inner_api/utils",
#include "gpio_if.h"    //路径：    "//drivers/hdf_core/framework/include/platform",




int main(){
    printf("gpio_test begin\r\n");
    printf("---------------------------\n");
    int32_t ret;  //32位返回值
    uint16_t pin=114;   //pin value 114
    ret= GpioSetDir(pin,GPIO_DIR_OUT);
    if(ret==0){
        printf("gpiosetdir successfully!");
        HDF_LOGI("HDF_LOGI:gpiosetdir successfully!");
    }
    else{
        printf("gpiosetdir failed!");
        HDF_LOGE("HDF_LOGE:gpiosetdir failed!");
    }
    for(int i=0;i<100;i++){
        ret=GpioWrite(pin,1);
        if(ret==-1){
            printf("write failed");
            break;
        }
        sleep(1);   //sleep 1s
        ret=GpioWrite(pin,0);
        if(ret==-1){
            printf("write failed");
            break;
        }
        sleep(1);
    }

    printf("---------------------------\n");
    return 0;
}

