【openharmony学习】【DAYU200】【RK3568】

# 代码结构
.//gcw  放在根目录下面
```
├── A1_hello    //验证编译构建体系
│   ├── BUILD.gn
│   ├── bundle.json
│   ├── include
│   └── src
├── A2_uart     //测试串口
│   ├── BUILD.gn
│   ├── bundle.json
│   ├── include
│   └── src
├── A3_gpio     //Gpio实验，点灯
│   ├── BUILD.gn
│   ├── bundle.json
│   ├── include
│   └── src
├── B1_hello    //测试编译
│   ├── BUILD.gn
│   ├── bundle.json
│   ├── include
│   └── src
└── README.md
```

# 整体结构
gcw为子系统，下面每个文件夹为一个部件（component），在build/subsystem_config.json文件中声明子系统，加入构建：  
 "gcw": {
    "path": "gcw",
    "name": "gcw"
  },
在vendor/hihope/rk3568/config.json 中声明gcw子系统的各个部件，加入编译。
```
    {
      "subsystem": "gcw",
      "components": [
        {
          "component": "A1_helloworld",
          "features": []
        },
        {
          "component": "B1_helloworld",
          "features": []
        },
        {
          "component": "A2_uart",
          "features": []
        },
        {
          "component": "A3_gpio",
          "features": []
        }
      ]
    },
```
再在每个部件中分别添加BUILD.gn和 bundle.json ，声明每个部件所需的模块和依赖，eg：在A3中
```
.
├── BUILD.gn      //描述模块
├── bundle.json   //描述部件
├── include       //头文件
│   ├── gpio_if.h
│   └── hdf_log.h
└── src           //c文件
    └── gpio_test.c
```
下面分析BUILD.gn和 bundle.json怎么写：
## （1）BUILD.gn （文件中不能备注，否则无法编译）
```
import("//build/ohos.gni")              //引入系统编译文件
import("//drivers/hdf_core/adapter/uhdf2/uhdf.gni")  //引入hdf框架编译文件

print("gcw  gpio_test BUILD.gn file")       //编译中可以起提醒作用
ohos_executable("A3_gcwgpio") {             //executable是可执行文件。此外还有共享库等
  sources = [ "src/gpio_test.c" ]           //要编译的源文件
  include_dirs = [                          //需要编译的头文件的路径
    "include",                                            //尝试备注  这里将drivers下的头文件复制到这进行编译
    "//drivers/hdf_core/framework/include/platform",     //gpio_if.h
    "//third_party/bounds_checking_function/include",     //secure.h
  ]

  deps = []

  external_deps = [               //依赖外部的部件      格式  部件：共享库
    "c_utils:utils", // code/release_4_0/rk3568/commonlibrary/c_utils/base/BUILD.gn    c++公共基础库
    "hdf_core:libhdf_utils", //hdf框架  ohos_shared_library("libhdf_utils")  code/release_4_0/rk3568/drivers/hdf_core/adapter/BUILD.gn c语言常用库
    "hdf_core:libhdf_platform", //驱动子系统平台框架
  ]

  cflags = [       //可以保持默认
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wno-format",
    "-Wno-format-extra-args",
  ]

  part_name = "A3_gpio"       //部件名称，须与bundle.json对应
  install_enable = true       
}
```
## （2） bundle.json
```
{
    "name": "@ohos/A3_gpio",   //生成的包名
    "description": "gcw gpio test",
    "version": "3.1",
    "license": "Apache License 2.0",
    "publishAs": "code-segment",
    "segment": {
        "destPath": "gcw/A3_gpio"     //部件文件夹路径
    },
    "dirs": {},
    "scripts": {},
    "component": {                   //部件相关描述
        "name": "A3_gpio",           //须和BUILD.gn文件中相同
        "subsystem": "gcw",         //所属子系统
        "syscap": [],
        "features": [],
        "adapted_system_type": ["standard"],    //设配的系统
        "rom": "100KB",                 //预先估计的存储和内存
        "ram": "100KB",
        "deps": {                          //依赖的外部部件和三方库
            "components": [
                "c_utils",    
                "hdf_core",
                "hilog"
            ],
            "third_party": []
        },
        "build": {                         //所要编译的部件
            "sub_component": [
                "//gcw/A3_gpio:A3_gcwgpio"  //可执行名称
            ],
            "inner_kits": [],
            "test": []
        }
    }
}
```

## 驱动节点配置
在 vendor/hihope/rk3568/hdf_config/khdf/device_info/device_info.hcs 中确认设备节点：  
在 vendor/hihope/rk3568/hdf_config/khdf/platform/rk3568_uart_config.hcs  
在 drivers/hdf_core/adapter/khdf/linux/platform/uart/uart_adapter.c 编写了对接linux驱动的代码


