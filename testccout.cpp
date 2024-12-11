
#include <iostream>
#include "ccout.h"

using namespace std;

class A
{
public:
	A(int a):_a(a){};
	int Get()const {return _a;}
private:
	int _a;
};
// 只需针对ostream类进行重载
ostream & operator <<(ostream & out,const A& a)
{
	out << a.Get();
	return out;
} 

int main()
{
	// 禁用键盘输入回显
	ccout.command(cc_command::ECHO_DISABLE);
	// 隐藏光标
	ccout.cursor(c_cmd::HIDE);
	// 清屏
	ccout.command(cc_command::CLS);
	// 字体设置
	cout << "Hello" << ccout << " World!\n" ;
	ccout.font(f_color::RED) << "Hello" << cout << " World!\n" ;
	ccout.font(f_backcolor::GREEN) << "Hello " << ccout.font(f_cmd::ITALICS|f_cmd::UNDERSCORE,f_color::YELLOW) << "World!\n" ;
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
	ccout.command(cc_command::ECHO_ENABLE);
	return 0;
}