#include <stdio.h>
#include <stdlib.h>    //goto函数
#include <stdint.h>    //unint8_t
#include <unistd.h>    //sleep()  //s

//#include "hdf_log.h"    //路径：    "//drivers/hdf_core/interfaces/inner_api/utils",
#include "uart_if.h"    //路径：    "//drivers/hdf_core/framework/include/platform",

// static int32_t UartTestSample(void)
// {

// }

int main(){
    printf("uart_test begin\r\n");

    printf("---------------------------\n");

    int32_t ret;
    uint32_t port;
    uint32_t baud;
    DevHandle handle = NULL;
    uint8_t wbuff[5] = { 1, 2, 3, 4, 5 };
    uint8_t rbuff[5] = { 0 };
    struct UartAttribute attribute;

    attribute.dataBits = UART_ATTR_DATABIT_7;                  // UART传输数据位宽，一次传输7个bit
    attribute.parity = UART_ATTR_PARITY_NONE;                  // UART传输数据无校检
    attribute.stopBits = UART_ATTR_STOPBIT_1;                  // UART传输数据停止位为1位
    attribute.rts = UART_ATTR_RTS_DIS;                         // UART禁用RTS
    attribute.cts = UART_ATTR_CTS_DIS;                         // UART禁用CTS
    attribute.fifoRxEn = UART_ATTR_RX_FIFO_EN;                 // UART使能RX FIFO
    attribute.fifoTxEn = UART_ATTR_TX_FIFO_EN;                 // UART使能TX FIFO

    port = 3;                                                  // UART设备端口号，要填写实际平台上的端口号

    handle = UartOpen(port);                                   // 获取UART设备句柄
    if (handle == NULL) {
        printf("UartOpen(port) failed \r\n");
        return HDF_FAILURE;
    }

    ret = UartSetBaud(handle, 9600);                           // 设置UART波特率为9600
    if (ret != 0) {
        printf("UartSetBaud: set baud failed, ret %d\n", ret);
        goto ERR;
    }
    printf("UartOpen successful and uart port = %d\n",port);

    ret = UartGetBaud(handle, &baud);                          // 获取UART波特率
    if (ret != 0) {
        printf("UartGetBaud: get baud failed, ret %d\n", ret);
        goto ERR;
    }
    printf("UartSetBaud successful and uart baudrate = %d\n", baud);

    ret = UartSetAttribute(handle, &attribute);                // 设置UART设备属性
    if (ret != 0) {
        printf("UartSetAttribute: set attribute failed, ret %d\n", ret);
        goto ERR;
    }
    printf("UartSetAttribute successful\n");

    ret = UartGetAttribute(handle, &attribute);                // 获取UART设备属性
    if (ret != 0) {
        printf("UartGetAttribute: get attribute failed, ret %d\n", ret);
        goto ERR;
    }
    printf("UartGetAttribute successful\n");


    ret = UartSetTransMode(handle, UART_MODE_RD_BLOCK);     // 设置UART传输模式为阻塞模式
    if (ret != 0) {
        printf("UartSetTransMode: set trans mode failed, ret %d\n", ret);
        goto ERR;
    }
    printf("UartSetTransMode successful\n");

    ret = UartWrite(handle, wbuff, 5);                         // 向UART设备写入5字节的数据
    if (ret != 0) {
        printf("UartWrite: write data failed, ret %d\n", ret);
        goto ERR;
    }
    //printf("UartWrite successful and wbuff:  %u\n",wbuff);       //这里输出的为整型，所以引用符号应为d
    //printf(wbuff);
     for(int i=0;i<5;i++){
        printf("write:%hhu\r\n",wbuff[i]);
     }

    // ret = UartRead(handle, rbuff, 5);                          // 从UART设备读取5字节的数据
    // if (ret < 0) {
    //     printf("UartRead: read data failed, ret %d\n", ret);
    //     goto ERR;
    // }
    // //printf("UartRead successful and rbuff:   %u\n",rbuff);
    // //printf(rbuff);
    //  for(int i=0;i<5;i++){
    //     printf("%u",rbuff[i]);
    //  }
    
    int j=1;
     while(1){
        ret=UartRead(handle, rbuff, 5);
        if(ret<0){
            printf("read fail\r\n");
            goto ERR;
        }
        if(ret==-1||ret==0){
            continue;    //如果没读到，那就跳出循环再读
        }
        printf("readlen=:%d\n",ret);
        for(int i=0;i<ret;i++){
            printf("read:%02x\r\n",rbuff[i]); //按十六进制输出
        }
        j++;
        printf("\n");
        usleep(10*1000); //sleep 10ms
        if(j>3)break;
     }


    printf(" function tests end\r\n");
ERR:
    UartClose(handle);                                         // 销毁UART设备句柄
    return ret;

    printf("---------------------------\n");

}


