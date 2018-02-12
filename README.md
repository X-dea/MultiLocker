MultiLocker is a opensource lock framework based on Arduino.  
MultiLocker是一个基于Arduino开发的（多功能）锁框架。

These authentication methods are supported:  
支持的认证方式：  
Fingerprint authentication by R308 fingerPrint module  
ID Card/NFC authentication by RC522 based RFID module  

## Project Address / 项目地址
GitlabX: [https://git.xdea.xyz/ctrysbita/MultiLocker](https://git.xdea.xyz/ctrysbita/MultiLocker)  
Github: [https://github.com/CTBeta/MultiLocker](https://github.com/CTBeta/MultiLocker)  

## Build / 构建
The Project is developed by PlatformIO IDE. If you want to build the code with Arduino IDE, please reset the path name and import libraries manually.  
本项目使用PlatformIO IDE构建，如果你需要使用ArduinoIDE，请手动更改文件路径名称并导入库文件。

Libraries used:  
使用的库文件：  
U8g2lib from [@olikraus](https://github.com/olikraus)  

You may need to reburn [optiboot](https://github.com/Optiboot/optiboot) bootloader to support the hardware watchdog of arduino.  
您可能需要重新烧写 [optiboot](https://github.com/Optiboot/optiboot) 引导程序以支持 Arduino 的硬件看门狗功能。
