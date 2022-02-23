# DCacheDemoServer
### DCache 读写测试
 应用配置CacheDemo.conf 用来配置 DCache 模块名 
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
