# ColorCout
 color cout for linux cpp    
终端需要支持ANSI转义序列，一般linux终端都会支持，但可能不会支持所有的指令，所以具体效果视终端而定。   
[unicode取值网站](https://symbl.cc/cn/unicode-table/#block-elements)
## 功能  
### font函数设置字体颜色、背景、斜体等   
***f_color***类型:设置字体颜色  
***f_backcolor***类型:设置背景颜色  
***f_cmd***类型:设置粗体、下滑线、斜体等  
### cursor函数设置光标移动  
***c_cmd***类型:设置光标操作  
后缀小写字母个数与调用哪个的重载函数有关  
`colorcout& cursor(c_cmd);//后缀无小写字母  
colorcout& cursor(c_cmd,int);//后缀有一个小写字母 MOVE_RIGHT_n  
colorcout& cursor(c_cmd,int,int);//后缀有两个小写字母 SET_x_y`  
### block函数显示特定图形
***b_block***类型:unicode字符映射的类型  
***b_color***类型:颜色  
***colorblock***:生成一个色块，之间没有空隙  
### command函数实现一些特定操作  
***cc_common***:指令类型，实现关回显、flush等功能  
### screen函数实现终端分辨率修改  
 测试没有效果，可能是终端不支持该指令  
## 用法  
![用法](https://github.com/Marspacecraft/ColorCout/blob/main/pic2.png)
![结果](https://github.com/Marspacecraft/ColorCout/blob/main/pic.png)

