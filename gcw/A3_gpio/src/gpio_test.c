#include <stdio.h>
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

/*
{
    "name": "@ohos/A3_gpio",
    "description": "gcw gpio test",
    "version": "3.1",
    "license": "Apache License 2.0",
    "publishAs": "code-segment",
    "segment": {
        "destPath": "gcw/A3_gpio"
    },
    "dirs": {},
    "scripts": {},
    "component": {
        "name": "A3_gpio",
        "subsystem": "gcw",
        "syscap": [],
        "features": [],
        "adapted_system_type": ["standard"],
        "rom": "100KB",
        "ram": "100KB",
        "deps": {
            "components": [     //需要两个依赖，公共基础库和hdf框架
                "c_utils",    
                "hdf_core"
            ],
            "third_party": []
        },
        "build": {
            "sub_component": [
                "//gcw/A3_gpio:A3_gcwgpio"
            ],
            "inner_kits": [],
            "test": []
        }
    }
}
*/