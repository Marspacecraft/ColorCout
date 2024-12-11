#ifndef _COLOR_COUT_H_
#define _COLOR_COUT_H_

#include <iostream>

/*****************************
	终端需要支持ANSI转义序列
	一般linux终端都会支持
	win10之前的终端可能不支持
	https://web.archive.org/web/20060206022229/http://enterprise.aacc.cc.md.us/~rhs/ansi.html
*****************************/


enum class f_color:int
{
	NONE=0,     	// 默认
	HOLD=1,			// 保持
	BLOCK=30,      	// 黑
	RED=31,      	// 红
	GREEN=32,      	// 绿
	YELLOW=33,    	// 黄
	BLUE=34,      	// 蓝
	PURPLE=35,    	// 粉
	CYAN=36,      	// 青
	WHITE=37,      	// 灰
};

enum class f_backcolor:int
{
	NONE=0,     	// 默认
	HOLD=1,			// 保持
	BLOCK=40,      	// 黑
	RED=41,      	// 红
	GREEN=42,      	// 绿
	YELLOW=43,   	// 黄
	BLUE=44,      	// 蓝
	PURPLE=45,    	// 粉
	CYAN=46,      	// 青
	WHITE=47,      	// 灰
};

class f_cmd
{
public:
	typedef unsigned int ccmd_type;
	static const ccmd_type NONE;		//默认
	static const ccmd_type DEFAULT;		// 取消格式
	static const ccmd_type LIGHTUP;		// 高亮 
	static const ccmd_type LIGHTDOWN;	// 变暗
	static const ccmd_type ITALICS;		// 斜体
	static const ccmd_type UNDERSCORE;	// 下划线
	static const ccmd_type BLINK;		// 闪烁
	static const ccmd_type FASTBLINK;	// 快闪
	static const ccmd_type REFLECT;		// 反显
	static const ccmd_type BLANKING;	// 消隐
	static const ccmd_type SLASH;		// 中横线
	static const ccmd_type HOLD;		// 保持
};

enum class c_cmd:int
{
	MOVE_LEFT_n=0,	// 左移n位
	MOVE_UP_n,		// 右移n位
	MOVE_RIGHT_n,	// 上移n位
	MOVE_DOWN_n,	// 下移n位
	HOME,			// 移动到第一列
	ENTER,			// 下一行第一列
	X_x,			// 移动到第x列
	Y_UP_n,			// 上移n行 第1列
	Y_DOWN_n,		// 下移n行 第1列
	SET_x_y,		// 设置光标位置

	DEL_FRONT,		// 删除前面
	DEL_BEHIND,		// 删除后面
	DEL_ALL,		// 删除所有
	DEL_ROW_FRONT,	// 删除行前面
	DEL_ROW_BEHIND,	// 删除行后面
	DEL_ROW_ALL,	// 删除行所有

	SHOW,			// 隐藏光标
	HIDE,			// 显示光标
	STORAGE,		// 保存当前位置
	RECOVERY,		// 恢复上次保存位置
};

enum class cc_command:int
{
	CLS=0,			// 清屏
	FLUSH,			// 清缓存
	BEEP,			// 警告音
	ECHO_ENABLE,	// 打开终端输入回显 system("stty echo");
	ECHO_DISABLE,	// 关闭终端输入回显 system("stty -echo");
};

enum class s_cmd:int
{
	SCREEN_40X25_mono_txt=0,	//40×25 黑白（文本）
	SCREEN_40X25_color_txt,		//40×25 彩色（文本）
	SCREEN_80X25_mono_txt,		//80×25 黑白（文本）
	SCREEN_80X25_color_txt,		//80×25 彩色（文本）
	SCREEN_320X200_4color_grap,	//320×200 4 色（图形）
	SCREEN_320X200_mono_grap,	//320×200 黑白（图形）
	SCREEN_640X200_mono_grap,	//640×200 黑白（图形）
	SCREEN_AUTO,				//启用自动换行
	SCREEN_320X200_color_grap,	//320×200 彩色（图形）
	SCREEN_640X200_16color_grap,//640×200 彩色（16 色图形）
	SCREEN_640X350_mono_grap,	//640×350 黑白（2 色图形）
	SCREEN_640X350_16color_grap,//640×350 彩色（16 色图形）
	SCREEN_640X480_mono_grap,	//640×480 黑白（2 色图形）
	SCREEN_640X480_16color_grap,//640×480 彩色（16 色图形）
	SCREEN_320X200_256color_grap,//320×200 彩色（256 色图形）
	SCREEN_RESET,				// 重置上面上次模式， reset AUTO 为关闭自动换行
};


typedef f_color b_color;
enum class b_block: int
{
	//https://symbl.cc/cn/unicode-table/#block-elements

	BLOCK_DOWN_1_8 = 0,	// "▁" 
	BLOCK_DOWN_2_8,		// "▂" 
	BLOCK_DOWN_3_8,		// "▃" 
	BLOCK_DOWN_4_8,		// "▄" 
	BLOCK_DOWN_5_8,		// "▅"
	BLOCK_DOWN_6_8,		// "▆"
	BLOCK_DOWN_7_8,		// "▇"
	BLOCK_DOWN_8_8,		// "█"
	BLOCK_UP_4_8,		// "▀" 

	BLOCK_LEFT_1_8,		// "▏"
	BLOCK_LEFT_2_8,		// "▎"
	BLOCK_LEFT_3_8,		// "▍"
	BLOCK_LEFT_4_8,		// "▌"
	BLOCK_LEFT_5_8,		// "▋"
	BLOCK_LEFT_6_8,		// "▊"
	BLOCK_LEFT_7_8,		// "▉"
	BLOCK_LEFT_8_8,		// "█"
	BLOCK_RIGHT_4_8,	// "▐"

	EDGE_1_1,			// "▖" 
	EDGE_1_2,			// "▘"
	EDGE_1_3,			// "▝" 
	EDGE_1_4,			// "▗" 
	EDGE_2_1,			// "▚"
	EDGE_2_2,			// "▞" 
	EDGE_3_1,			// "▙" 
	EDGE_3_2,			// "▛" 
	EDGE_3_3,			// "▜" 
	EDGE_3_4,			// "▟" 
	EDGE_FULL,			// "■" 
	
};

class colorcout
{
public:
	/*****************************
		实例化接口
	*****************************/
	static  colorcout& GetInstance()
	{
		static colorcout _ccout;
		return _ccout;
	}
	// 重置设置
	static const char * RESET;
	/*****************************
		设置字体显示接口
	*****************************/
	// 设置字体颜色
	colorcout& font(f_color);
	// 设置字体背景颜色
	colorcout& font(f_backcolor);
	// 设置字体格式
	colorcout& font(f_cmd::ccmd_type);
	// 设置字体和背景颜色
	colorcout& font(f_color,f_backcolor);
	// 设置字体格式和颜色
	colorcout& font(f_cmd::ccmd_type,f_color);
	// 设置字体格式、颜色和背景
	colorcout& font(f_cmd::ccmd_type,f_color,f_backcolor);

	f_color GetColor()const {return _font;}
	f_backcolor GetBackColor()const {return _bkgd;}
	std::string GetCmd() const;
	/*****************************
		光标操作接口
	*****************************/
	colorcout& cursor(c_cmd);
	colorcout& cursor(c_cmd,int);
	colorcout& cursor(c_cmd,int,int);

	/*****************************
		unicode图形接口
	*****************************/
	colorcout& block(b_block,b_color=b_color::NONE);
	colorcout& block(b_block,int x,int y,b_color=b_color::NONE);
	colorcout& block(b_block,int x,int y,int n,b_color=b_color::NONE);

	/*****************************
		色块接口
	*****************************/
	colorcout& colorblock(b_color,int n=1);
	colorcout& colorblock(b_color,int x,int y,int n=1);


	/*****************************
		命令接口
	*****************************/
	colorcout& command(cc_command);

	/*****************************
		屏幕接口
	*****************************/
	colorcout& screen(s_cmd);

private:
	colorcout() = default;
	f_color _font;
	f_backcolor _bkgd;
	f_cmd::ccmd_type _cmd;
};

extern colorcout& ccout;
// 重载<< 可以切换类型
extern colorcout& operator<<(colorcout& out,colorcout& a);
extern colorcout& operator<<(std::ostream& out,colorcout& a);
extern std::ostream& operator<<(colorcout& a,std::ostream& out);
// 重载<< 
template<class T>
colorcout& operator<<(colorcout& out,const T& a)
{

	std::cout <<"\033[" << out.GetCmd();
	if(f_backcolor::BLOCK <= out.GetBackColor())
	{
		std::cout << ";" << static_cast<int>(out.GetBackColor());
	}
	if(f_color::BLOCK <= out.GetColor())
	{
		std::cout << ";" << static_cast<int>(out.GetColor());
	}

	std::cout << "m" << a <<  colorcout::RESET;

	return out;
}

#endif


