
#include <iostream>
#include <unistd.h>
#include "./ccout.h"
#ifdef _WIN32
#include <windows.h>
#elif __unix__ || __MACH__
#include <termios.h>
#include <sys/ioctl.h>
#include <cstdlib> 
#endif

const char * colorcout::RESET = "\033[0m";

const f_cmd::ccmd_type f_cmd::NONE=0;						//默认
const f_cmd::ccmd_type f_cmd::DEFAULT=0x00001 << 0;			// 取消格式
const f_cmd::ccmd_type f_cmd::LIGHTUP=0x00001 << 1;			// 高亮 
const f_cmd::ccmd_type f_cmd::LIGHTDOWN=0x00001 << 2;		// 变暗
const f_cmd::ccmd_type f_cmd::ITALICS=0x00001 << 3;			// 斜体
const f_cmd::ccmd_type f_cmd::UNDERSCORE=0x00001 << 4;		// 下划线
const f_cmd::ccmd_type f_cmd::BLINK=0x00001 << 5;			// 闪烁
const f_cmd::ccmd_type f_cmd::FASTBLINK=0x00001 << 6;		// 快闪
const f_cmd::ccmd_type f_cmd::REFLECT=0x00001 << 7;			// 反显
const f_cmd::ccmd_type f_cmd::BLANKING=0x00001 << 8;		// 消隐
const f_cmd::ccmd_type f_cmd::SLASH=0x00001 << 9;			// 中横线
const f_cmd::ccmd_type f_cmd::HOLD=0xffffff;				// 保持


const std::string sg_block[] = 
{	
	"▁",// 0 BLOCK_DOWN_1_8
	"▂",// 1 BLOCK_DOWN_2_8
	"▃",// 2 BLOCK_DOWN_3_8
	"▄",// 3 BLOCK_DOWN_4_8
	"▅",// 4 BLOCK_DOWN_5_8
	"▆",// 5 BLOCK_DOWN_6_8
	"▇",// 6 BLOCK_DOWN_7_8
	"█",// 7 BLOCK_DOWN_8_8 
	"▀",// 8 BLOCK_UP_4_8 

	"▏",// 9 BLOCK_LEFT_1_8
	"▎",// 10 BLOCK_LEFT_2_8
	"▍",// 11 BLOCK_LEFT_3_8
	"▌",// 12 BLOCK_LEFT_4_8
	"▋",// 13 BLOCK_LEFT_5_8
	"▊",// 14 BLOCK_LEFT_6_8
	"▉",// 15 BLOCK_LEFT_7_8
	"█",// 16 BLOCK_LEFT_8_8
	"▐",// 17 BLOCK_RIGHT_4_8

	"▖",// 18 EDGE_1_1
	"▘",// 19 EDGE_1_2
	"▝",// 20 EDGE_1_3
	"▗",// 21 EDGE_1_4

	"▚",// 22 EDGE_2_1
	"▞",// 22 EDGE_2_2
	"▙",// 23 EDGE_3_1
	"▛",// 24 EDGE_3_2
	"▜",// 25 EDGE_3_3
	"▟",// 26 EDGE_3_4
	"■",// 27 EDGE_FULL
};

#ifdef _WIN32
static int TerminalWidth() 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
        return 100;
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

static int getCursorPosition() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) 
	{  
        return 0;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) 
	{
        return 0;
    }

    return csbi.dwCursorPosition.X;
}

void disableEcho() 
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode); 
    mode &= ~ENABLE_ECHO_INPUT;    
    SetConsoleMode(hStdin, mode); 
}

void enableEcho() 
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode); 
    mode |= ENABLE_ECHO_INPUT;    
    SetConsoleMode(hStdin, mode); 
}

static int set_echo_mode(int option)
{
	if(option)
		enableEcho()
	else
		disableEcho();
}

#elif __unix__ || __MACH__
static int getCursorPosition() 
{
    char buf[8];
	int curline;
	char cmd[]="echo -e '\033[6n'";//> /dev/null
	struct termios save,raw;

	ccout.command(cc_command::FLUSH);
	tcgetattr(0,&save);
	cfmakeraw(&raw); tcsetattr(0,TCSANOW,&raw);
	if (isatty(fileno(stdin))) 
	{
		write(1,cmd,sizeof(cmd));
		read (0 ,buf ,sizeof(buf));
		//printf("\n\rCurrent Line: %s\n\r" , &buf[2]);
	}
	tcsetattr(0,TCSANOW,&save);
	ccout.cursor(c_cmd::MOVE_LEFT_n,10);
	ccout.cursor(c_cmd::DEL_BEHIND);
	int x=0,y=0,f=0;
	for(int i=2;i<8;++i)
	{
		if(buf[i]>='0'&&buf[i]<='9')
		{
			if(f)		
				x = 10*x + buf[i] - '0';
			else
				y = 10*y + buf[i] - '0';
		}
		else
		{
			if(++f>1)
				break;
		}
	}

	if(x > 10)
		x-=10;
	return x;
}
static int TerminalWidth() 
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) 
        return 100;
    return w.ws_col+10;

}
static int set_echo_mode(int option)
{
	int err;
	struct termios term;
	if(tcgetattr(STDIN_FILENO ,&term)==-1)
		return -1;
	
	if(option)
		term.c_lflag |=(ECHO | ECHOE | ECHOK | ECHONL);
	else
		term.c_lflag &=~(ECHO | ECHOE | ECHOK | ECHONL);

	err=tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);
	if(err==-1 && err==EINTR)
		return 1; 
	
	return 0;
}

#endif


colorcout& colorcout::font(f_color font)
{
	static colorcout fontcout;
	if(f_color::HOLD == font)
		return fontcout;
	fontcout._font = font;
	fontcout._bkgd = f_backcolor::NONE;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_backcolor::HOLD == bkgd)
		return fontcout;
	fontcout._font = f_color::NONE;
	fontcout._bkgd = bkgd;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd)
{
	static colorcout fontcout;
	if(f_cmd::HOLD == cmd)
		return fontcout;
	fontcout._font = f_color::NONE;
	fontcout._bkgd = f_backcolor::NONE;
	fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::font(f_color font,f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	
	if(f_backcolor::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd,f_color font)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	fontcout._bkgd = f_backcolor::NONE;
	if(f_cmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd,f_color font,f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	if(f_backcolor::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	if(f_cmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}


colorcout& colorcout::fulllines(f_color color,const std::string str,std::string c)
{
	ccout.font(color)<<str;
	int width = terminanwidth();
	int pos = cursorposition();

	pos %=width;
	pos = width - pos;
	//pos /= c.length();

	for(int i=0;i<pos;i++)
		ccout.font(color)<<c;

	return *this;
}

std::string colorcout::GetCmd() const
{
	std::string ret("0");
	if(0 == _cmd)
		return ret;
	
	for(int i=1;i<10;i++)
	{
		if(_cmd & (0x00001 << i))
		{
			ret += std::string(";")+ std::to_string(i);
		}
	}
	return ret;
}



colorcout& colorcout::cursor(c_cmd cmd)
{
	switch(cmd)
	{
		case c_cmd::HOME:
		std::cout << "\033[1G";
		break;
		case c_cmd::END:
		std::cout << "\033[1F";
		break;
		case c_cmd::ENTER:
		std::cout << "\033[1E";
		break;
		case c_cmd::SHOW:
		std::cout << "\033[?25h";
		break;
		case c_cmd::HIDE:
		std::cout << "\033[?25l";
		break;
		case c_cmd::STORAGE:
		std::cout << "\033[s";
		break;
		case c_cmd::RECOVERY:
		std::cout << "\033[u";
		break;
		case c_cmd::DEL_FRONT:
		std::cout << "\033[1J";
		break;
		case c_cmd::DEL_BEHIND:
		std::cout << "\033[0J";
		break;
		case c_cmd::DEL_ALL:
		std::cout << "\033[2J";
		break;
		case c_cmd::DEL_ROW_FRONT:
		std::cout << "\033[1K";
		break;
		case c_cmd::DEL_ROW_BEHIND:
		std::cout << "\033[0K";
		break;
		case c_cmd::DEL_ROW_ALL:
		std::cout << "\033[2K";
		break;
		default:
		break;
	}

	return *this;
}

colorcout& colorcout::cursor(c_cmd cmd,int n)
{
	switch(cmd)
	{
		case c_cmd::MOVE_LEFT_n:
		std::cout << "\033[" << n << "D";
		break;
		case c_cmd::MOVE_UP_n:
		std::cout << "\033[" << n << "A";
		break;
		case c_cmd::MOVE_RIGHT_n:
		std::cout << "\033[" << n << "C";
		break;
		case c_cmd::MOVE_DOWN_n:
		std::cout << "\033[" << n << "B";
		break;
		case c_cmd::X_x:
		std::cout << "\033[" << n << "G";
		break;
		case c_cmd::Y_UP_n:
		std::cout << "\033[" << n << "F";
		break;
		case c_cmd::Y_DOWN_n:
		std::cout << "\033[" << n << "E";
		break;
		default:
		break;
	}

	return *this;
}

colorcout& colorcout::cursor(c_cmd cmd,int x,int y)
{
	switch(cmd)
	{
		case c_cmd::SET_x_y:
		std::cout << "\033[" << y << ";" << x << "H";
		break;
		default:
		break;
	}

	return *this;
}

colorcout& colorcout::command(cc_command cmd)
{
	switch(cmd)
	{
		case cc_command::CLS:
		cursor(c_cmd::DEL_ALL);
		cursor(c_cmd::SET_x_y,0,0);
		break;
		case cc_command::FLUSH:
		std::cout <<std::flush;
		break;
		case cc_command::BEEP:
		std::cout << '\a';
		break;
		case cc_command::ECHO_DISABLE:
		set_echo_mode(0);
		break;
		case cc_command::ECHO_ENABLE:
		set_echo_mode(1);
		break;
	}

	return *this;
}



colorcout& colorcout::block(b_block type,b_color color)
{
	std::cout <<"\033[0;" <<static_cast<int>(color) << "m"<<sg_block[static_cast<int>(type)]<<RESET;
	return *this;
}

colorcout& colorcout::block(b_block type,int x,int y,b_color color)
{
	cursor(c_cmd::SET_x_y,x,y);
	block(type,color);
	return *this;
}

colorcout& colorcout::block(b_block type,int x,int y,int n,b_color color)
{
	std::string s("m");

	cursor(c_cmd::SET_x_y,x,y);
	std::cout <<"\033[0;" <<static_cast<int>(color);

	for(int i=0;i<n;i++)
		s+=sg_block[static_cast<int>(type)];
	std::cout << s << RESET;
	return *this;
}

colorcout& colorcout::colorblock(b_color color,int n)
{
	std::string a("m");
	int tmp = static_cast<int>(color);
	if(b_color::HOLD == color)
		tmp = 0;
	if(0 != tmp)
		tmp += 10;
	for(int i=0;i<n;i++)
		a += " ";
	std::cout <<"\033[0;" << tmp << a << RESET;
	return *this;
}

colorcout& colorcout::colorblock(b_color color,int x,int y,int n)
{
	ccout.cursor(c_cmd::SET_x_y,x,y);
	colorblock(color,n);
	return *this;
}

colorcout& colorcout::screen(s_cmd cmd)
{
	static s_cmd _cmd = s_cmd::SCREEN_RESET;

	if(_cmd == cmd)
	{
		return *this;
	}

	if(s_cmd::SCREEN_RESET == cmd)
	{
		std::cout << "\033[=" << static_cast<int>(_cmd)<<"l";
		_cmd = s_cmd::SCREEN_RESET;
		return *this;
	}

	if(s_cmd::SCREEN_RESET != _cmd)
		std::cout << "\033[=" << static_cast<int>(_cmd)<<"l";
	std::cout << "\033[=" << static_cast<int>(cmd)<<"h";
	_cmd = cmd;
	return *this;
}

int colorcout::terminanwidth()
{
	return TerminalWidth();
}

int colorcout::cursorposition()
{
	return getCursorPosition();
}

colorcout& ccout = colorcout::GetInstance();
colorcout& operator<<(colorcout& out,colorcout& a)
{
	return a;
}

colorcout& operator<<(std::ostream& out,colorcout& a)
{
	return a;
}
std::ostream& operator<<(colorcout& a,std::ostream& out)
{
	return out;
}

