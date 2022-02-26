# DCacheDemoServer
[TARS-Docker](https://github.com/CyrusZhou-CN/TARS-Docker) 测试调试项目
### DCache 读写测试
 应用配置CacheDemo.conf 用来配置要操作的 DCache 模块名 、 服务名
 ```
<root>
AppName=Test
KValueModuleName=TestKv22
</root>
 ```
## 已知错误
DCacheDemoServer.h:10:10: fatal error: Proxy.h: No such file or directory</br>
重新编译一下 DCache ,注意DCache项目路径不要变</br>
```
mkdir -p /develop/DCache/build
cd /develop/DCache/build
cmake .. && make -j4
```
# 使用方式
## 创建DCache服务模块
参考 [安装DCache](https://github.com/Tencent/DCache/blob/master/docs/install.md)
### 1、DCache => 发布包管理->设置默认包
注意要所有列表的都设置
![image](https://user-images.githubusercontent.com/4635861/155584389-53afd7f8-bcac-48fa-b8e3-57c5a0273faf.png)
### 2、DCache => 服务创建 => 地区 =>新增地区
![image](https://user-images.githubusercontent.com/4635861/155584642-4ef3fafb-7219-4984-be58-cb028cae9056.png)
### 3、DCache => 服务创建 => 创建应用 =>创建应用
![image](https://user-images.githubusercontent.com/4635861/155584832-4c1b279b-e1b4-4377-9fb4-03dfb819aaa2.png)
### 4、DCache => 服务创建 => 创建应用 =>创建 router、proxy 服务
![image](https://user-images.githubusercontent.com/4635861/155702193-a1455403-ae7f-4ddc-987d-1f2e9c817dce.png)
### 5、DCache => 服务创建 => 创建应用 =>安装发布
![image](https://user-images.githubusercontent.com/4635861/155702308-b5e195b2-15de-4c0e-9be2-36f14ac99092.png)
### 6、DCache => 服务创建 => 创建模块 =>下一步
![image](https://user-images.githubusercontent.com/4635861/155702507-f4756a33-fbff-4157-baf1-cdb7348686bc.png)
### 7、DCache => 服务创建 => 模块配置 =>下一步
![image](https://user-images.githubusercontent.com/4635861/155702585-08fc72b2-6f60-42c7-9d95-002451f5f960.png)
### 8、DCache => 服务创建 => 服务配置 =>下一步
![image](https://user-images.githubusercontent.com/4635861/155702659-be0d152f-0e38-4c59-92f5-747d1a1600e6.png)
### 9、DCache => 服务创建 => 服务配置 =>安装发布
![image](https://user-images.githubusercontent.com/4635861/155702805-e8e1405c-2141-46c6-9b92-99bbfedfa667.png)
### 10、查看服务
![image](https://user-images.githubusercontent.com/4635861/155702937-a7c4b27d-d6db-45a0-b6e2-90b876f0a983.png)
## 创建TARS应用服务
### 1、TARS 运维管理 => 应用管理 => 新建应用
应用名：DCacheDemo
![image](https://user-images.githubusercontent.com/4635861/155703460-e4cbb481-2918-4cb4-b9d4-8ce40a01bb95.png)
### 2、TARS 运维管理 => 部署申请
应用：DCacheDemo
服务名称：DCacheDemoServer
OBJ：DCacheDemoServantObj
点获取端口,注意名称不要填错
![image](https://user-images.githubusercontent.com/4635861/155703852-fa476de7-2158-463c-8a52-ee5a881bf2e4.png)
提示部署完成后，点击TARS查看服务，点击如图的刷新按钮，就可以看到新创建的服务。
![image](https://user-images.githubusercontent.com/4635861/155704153-728f7d63-411e-4c7f-931e-033f11380315.png)
![image](https://user-images.githubusercontent.com/4635861/155704261-d1b0ca67-234e-4394-b593-7d940da7d3a8.png)
### 3、点击=>重启 启动服务
![image](https://user-images.githubusercontent.com/4635861/155705591-32941749-d5db-4c09-8c02-29fdbfd220b1.png)
### 4、配置服务
配置内容
 ```
<root>
AppName=Test
KValueModuleName=TestKv22
</root>
 ```
![image](https://user-images.githubusercontent.com/4635861/155707376-a4f26cf4-2453-4b8c-a9ab-dc349297b160.png)
### 3、进入容器编译发布服务
#### 进入容器
```
docker exec -it tars-develop /bin/bash
cd DCacheDemoServer/build
```
![image](https://user-images.githubusercontent.com/4635861/155704715-9e6682e0-5a40-4e20-b0de-952d6455b1ed.png)
#### 编译设置
```
cmake .. -DTARS_WEB_HOST=${WEBHOST} -DTARS_TOKEN=${TARS_TOKEN} 
```
![image](https://user-images.githubusercontent.com/4635861/155704955-5200c5d3-66c3-42f2-bc0e-07e72914a3a2.png)
#### 编译发布
```
make DCacheDemoServer-upload
```
![image](https://user-images.githubusercontent.com/4635861/155705241-a517a8ef-2073-4382-bf0c-ae07e784a616.png)

提示 active server, please start server first! 说明服务没有启动，点击重启来启动服务
![image](https://user-images.githubusercontent.com/4635861/155706985-942e6bf2-9083-4745-a8c7-d1379591952f.png)
## 使用服务
点击更多命令 =>  发送自定义命令 => help
![image](https://user-images.githubusercontent.com/4635861/155709903-601a6d08-7603-4021-9151-69d07dcd47c6.png)
```
test: 测试KValue读写
listkv: KValue 获取前1000 key列表
setkv: KValue 写入操作(命令格式：setkv key:value)
getkv: KValue 读取操作(命令格式：getkv key)
delkv: KValue 删除操作(命令格式：delkv key)
```
#### 可以看到测试命令的使用方式
#### 发送test测试读写命令
![image](https://user-images.githubusercontent.com/4635861/155710217-aeb57aad-0d3a-43fa-b5ef-6bc3a81577aa.png)
#### 表示服务正常

