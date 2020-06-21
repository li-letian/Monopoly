# Monopoly

[开发文档](https://github.com/li-letian/Monopoly/tree/master/monopoly/doc/大富翁项目文档.md)

[使用说明](https://github.com/li-letian/Monopoly/tree/master/monopoly/doc/大富翁游戏说明.md)

### 编译

```bash
git clone git@github.com:li-letian/Monopoly.git
cd Monopoly
cd monopoly
mkdir win32-build
cd win32-build
cmake .. -G"Visual Studio 16 2019" -A Win32
cd ..
cocos run -p win32
```