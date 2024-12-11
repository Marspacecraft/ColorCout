# ColorCout
 color cout for linux cpp    
   终端需要支持ANSI转义序列，一般linux终端都会支持，但一般都不会支持所有的指令，所以具体效果视终端而定。
   [unicode取值网站](https://symbl.cc/cn/unicode-table/#block-elements)
## 功能  
### font函数设置字体颜色、背景、斜体等   
    f_color类型:设置字体颜色
    f_backcolor类型:设置背景颜色
    f_cmd类型:设置粗体、下滑线、斜体等
### cursor函数设置光标移动
    c_cmd类型:设置光标操作
    后缀小写字母个数与调用哪个的重载函数有关
`colorcout& cursor(c_cmd);//后缀无小写字母
	colorcout& cursor(c_cmd,int);//后缀有一个小写字母 MOVE_RIGHT_n
	colorcout& cursor(c_cmd,int,int);//后缀有两个小写字母 SET_x_y`
### block函数显示特定图形
    b_block类型:unicode字符映射的类型
    b_color类型:颜色
    colorblock():生成一个色块，之间没有空隙
### command函数实现一些特定操作
    cc_common:指令类型，实现关回显、flush等功能
### sscreen函数实现终端分辨率修改
    测试没有效果，可能是终端不支持该指令
## 用法  
`// 禁用键盘输入回显
	ccout.command(cc_command::ECHO_DISABLE);
	// 隐藏光标
	ccout.cursor(c_cmd::HIDE);
	// 清屏
	ccout.command(cc_command::CLS);
	// 字体设置
	cout << "Hello" << ccout << " World!\n" ;
	ccout.font(f_color::RED) << "Hello" << cout << " World!\n" ;
	ccout.font(f_backcolor::GREEN) << "Hello " 
        << ccout.font(f_cmd::ITALICS|f_cmd::UNDERSCORE,f_color::YELLOW) 
        << "World!\n" ;
	// 输出类
	A a(10);
	ccout.font(f_cmd::LIGHTDOWN) << "Class a value is:" << a << "\n"; 
	// 输出unicode图形
	ccout.block(b_block::BLOCK_DOWN_8_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_7_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_6_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_5_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_4_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_3_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_2_8,b_color::RED);  
	ccout.block(b_block::BLOCK_DOWN_1_8,b_color::RED) << "\n";  
	// 显示光标
	ccout.cursor(c_cmd::SHOW);
	// 打开输入回显
	ccout.command(cc_command::ECHO_ENABLE);`

    ![结果](https://github.com/Marspacecraft/ColorCout/blob/main/pic.png)

