# 模板匹配
## 功能特点
- 支持多模板匹配, 自动匹配模板文件夹下的的文件
## 使用方法
编译为exe后，在cmd运行 `test.exe 模板文件夹路径 查找图片的路径`
eg：
```
TM.exe C:\Users\xiao\source\repos\TemplateMatching\TemplateMatching\templ C:\Users\xiao\source\repos\TemplateMatching\TemplateMatching\img1.png
```
## others
- 运用了一些win32的库，来检索文件夹下的文件
- 需要事先配置好opencv环境
- 代码的的编码为GB2312（后续改进）
