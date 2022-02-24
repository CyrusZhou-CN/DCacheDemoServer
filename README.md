# DCacheDemoServer
### DCache 读写测试
 应用配置CacheDemo.conf 用来配置 DCache 模块名 、 服务名
 ```
<root>
AppName=Test
KValueModuleName=TestKv22
</root>
 ```
## 已知错误
DCacheDemoServer.h:10:10: fatal error: Proxy.h: No such file or directory</br>
重新编译一下 DCache </br>
```
mkdir -p /develop/DCache/build
cd /develop/DCache/build
cmake .. && make -j4
```
# 使用方式
### 1、DCache => 发布包管理->设置默认包
![image](https://user-images.githubusercontent.com/4635861/155584389-53afd7f8-bcac-48fa-b8e3-57c5a0273faf.png)</br>
### 2、DCache => 服务创建 => 地区 =>新增地区
![image](https://user-images.githubusercontent.com/4635861/155584642-4ef3fafb-7219-4984-be58-cb028cae9056.png)</br>
### 3、DCache => 服务创建 => 创建应用 =>创建应用
![image](https://user-images.githubusercontent.com/4635861/155584832-4c1b279b-e1b4-4377-9fb4-03dfb819aaa2.png)</br>
### 4、DCache => 服务创建 => 创建模块 =>下一步
![image](https://user-images.githubusercontent.com/4635861/155585210-31555d2e-2a70-4740-a2fa-7b2a69850fa2.png)
