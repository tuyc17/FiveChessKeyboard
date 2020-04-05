#pragma region environments

# include <windows.h>
# include <stdio.h>
# include <conio.h>
# include <string>
# include <ctime>

#undef UNICODE

using namespace std;

#pragma endregion

#pragma region structs

// 棋盘上的落子点，共225个，从(0, 0)至(14, 14))
struct pt
{
	int x; // 棋盘x方向上的坐标，从0开始
	int y; // 棋盘y方向上的坐标，从0开始
};

#pragma endregion

#pragma region virables

#define _or_ptx      0   // 棋盘原点x坐标
#define _or_pty      0   // 棋盘原点y坐标
#define _max_ptx    14   // 棋盘最大x坐标
#define _max_pty    14   // 棋盘最大y坐标
#define computerturn 1   // 轮到电脑下棋
#define playturn     0   // 轮到玩家下棋
#define maxelem     15   // 棋盘大小。此题中，棋盘为15*15

pt m_pplastpos; // 玩家走的上一步棋
pt m_pclastpos; // 计算机走的上一步棋
bool m_bwfirst = false; // 标记谁先走，1为电脑先走，0为玩家先走
bool m_binit = false; // 判断游戏是否是处于刚开始阶段

// 
bool pwin;
bool cwin;
bool ctable[15][15][572];
int win[2][572];
bool ptable[15][15][572];

bool start;

bool player = false;

int board[15][15];
bool computer = false;

static int mainflag = 0; // 指示缓冲区是否改变，如果没有改变则调用主函数，直到改变为止

#pragma endregion

#pragma region declaration

// 初始化棋盘函数
void InitializeBoard();

pt ComTurn();
int GiveScore(int type, int x, int y);
bool SearchBlank(int& i, int& j, int nowboard[][15]);
void GetBoard(int tempboard[][15], int nowboard[][15]);

pt getpoint(int table[maxelem][maxelem], int max);  // 数组本来就是指向一个地址的，所以不需要加引用也可以改变其中的值


int table[maxelem][maxelem];   // 棋盘数组，决定了绘制效果。空白位置记为0，如果电脑下子标记为1（电脑棋子颜色0x0b），玩家下子标记为2（玩家棋子颜色0x0e）

void gotoxy(int x, int y);  // （疑似）将光标移动至第x列第y行
void gotoxy(pt p);   // 将光标移动至坐标p处

void   Chang_Console_size(int max_x,   // x方向上的长度，长度值从1开始 
	int max_y);  // y方向上的长度，长度值从1开始
void   color(int n_color);             // n_color为颜色值，十六进制形式

void   out(char* chars);   // 输出chars所指向的字符串
void   out(int flag);      // 上面函数的重载形式，flag = 0时输出●，flag = 1时输出■，用以绘制棋盘

void   hidecur();          // 隐藏光标
char   getudlr();          // 接受上下左右及回车按键
int get_rnum(int maxrand);  // 得到一个不大于maxrand的随机数

bool check(pt checkpoint, int table[maxelem][maxelem], int max, int checkcpflag);  // 检查是否获胜，checkcpflag=1是检查电脑是否获胜，checkcpflag=2是检查玩家是否获胜
void begin();

#pragma endregion

int main()
{
	begin();
	while (mainflag++ != 0) { _getch(); _getch(); };
	main();
	return 0;
}

bool check(pt checkpoint, int board[maxelem][maxelem], int max, int checkcpflag)  //检查是否获胜，checkcpflag=1是检查电脑是否获胜，checkcpflag=0是检查玩家是否获胜
{//本模块存在的问题：边缘判定具有BUG
	switch (checkcpflag)
	{
	case 1:
		if (1)
		{
			int ncount = 0;
			int ncount1 = 0;
			int ncount2 = 0;
			//横向扫描
			for (int i = checkpoint.x; board[i][checkpoint.y] == checkcpflag; i--)
			{
				if (i >= 0)
				{
					ncount1++;
				}

			}
			for (int j = checkpoint.x; board[j][checkpoint.y] == checkcpflag; j++)
			{
				if (j <= max)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			//纵向扫描
			for (int i = checkpoint.y; board[checkpoint.x][i] == checkcpflag; i--)
			{
				if (i >= 0)
				{
					ncount1++;
				}
			}
			for (int j = checkpoint.y; board[checkpoint.x][j] == checkcpflag; j++)
			{
				if (j <= max)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			//左上至右下扫描
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i--, j--)
			{
				if (i >= 0 && j >= 0)
				{
					ncount1++;
				}
			}
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i++, j++)
			{
				if (i <= max && j <= max)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			// 左下至右上扫描
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i--, j++)
			{
				if (i >= 0 && j <= max)
				{
					ncount1++;
				}

			}
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i++, j--)
			{
				if (i <= max && j >= 0)
				{
					ncount2++;
				}

			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
		}
		break;
	case 0:
		if (1)
		{
			int ncount = 0;
			int ncount1 = 0;
			int ncount2 = 0;
			//横向扫描
			for (int i = checkpoint.x; board[i][checkpoint.y] == checkcpflag; i--)
			{
				if (i >= 0)
				{
					ncount1++;
				}
			}
			for (int j = checkpoint.x; board[j][checkpoint.y] == checkcpflag; j++)
			{
				if (j <= max)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			//纵向扫描
			for (int i = checkpoint.y; board[checkpoint.x][i] == checkcpflag; i--)
			{
				if (i >= 0)
				{
					ncount1++;
				}

			}
			for (int j = checkpoint.y; board[checkpoint.x][j] == checkcpflag; j++)
			{
				if (j <= max)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			//左上至右下扫描
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i--, j--)
			{
				if (i >= 0 && j >= 0)
				{
					ncount1++;
				}

			}
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i++, j++)
			{
				if (i <= max && j <= max)
				{
					ncount2++;
				}

			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
			ncount = 0;
			ncount1 = 0;
			ncount2 = 0;
			//坐下至右上扫描
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i--, j++)
			{
				if (i >= 0 && j <= max)
				{
					ncount1++;
				}

			}
			for (int i = checkpoint.x, j = checkpoint.y; board[i][j] == checkcpflag; i++, j--)
			{
				if (i <= max && j >= 0)
				{
					ncount2++;
				}
			}
			ncount = ncount1 + ncount2;
			if (ncount >= 6)
			{
				return true;
			}
		}
		break;
	}
	return false;

}
// 电脑下棋函数
pt ComTurn()
{
	// bestx，besty为当前最佳位置，i，j是人能下的各种位置；pi，pj是计算机能下的各种位置
	int bestx = -1, besty = -1;
	int i, j, pi, pj, ptemp, ctemp, pscore = 10, cscore = -10000, ctempboard[15][15], ptempboard[15][15];
	int m, n, temp1[20], temp2[20];//暂存第一步搜索的信息
	if (start)
	{
		if (board[7][7] == 2)
		{
			bestx = 7;
			besty = 7;
		}
		else
		{
			bestx = 8;
			besty = 8;
		}
		start = false;
	}
	else
	{//寻找最佳位置
		GetBoard(ctempboard, board);
		while (SearchBlank(i, j, ctempboard))
		{
			n = 0;
			pscore = 10;
			GetBoard(ptempboard, board);
			ctempboard[i][j] = 3;//标记已被查找
			ctemp = GiveScore(1, i, j);
			for (m = 0; m < 572; m++)
			{//暂时更改玩家信息
				if (ptable[i][j][m])
				{
					temp1[n] = m;
					ptable[i][j][m] = false;
					temp2[n] = win[0][m];
					win[0][m] = 7;
					n++;
				}
			}
			ptempboard[i][j] = 1;

			//		ChangeStatus(ptempboard);
			pi = i;
			pj = j;
			while (SearchBlank(i, j, ptempboard))
			{

				ptempboard[i][j] = 3;//标记已被查找
				ptemp = GiveScore(0, i, j);
				if (pscore > ptemp)////此时为玩家下子，运用极小极大法时应选取最小值
					pscore = ptemp;
			}
			for (m = 0; m < n; m++)
			{//恢复玩家信息
				ptable[pi][pj][temp1[m]] = true;
				win[0][temp1[m]] = temp2[m];
			}
			if (ctemp + pscore > cscore)//此时为计算机下子，运用极小极大法时应选取最最大值
			{
				cscore = ctemp + pscore;
				bestx = pi;
				besty = pj;
			}
		}
	}


	board[bestx][besty] = 1;




	for (i = 0; i < 572; i++)
	{//修改计算机下子后，棋盘的变化状况
		if (ctable[bestx][besty][i] && win[1][i] != 7)
			win[1][i]++;
		if (ptable[bestx][besty][i])
		{
			ptable[bestx][besty][i] = false;
			win[0][i] = 7;
		}
	}

	pt bestpt;
	bestpt.x = bestx;
	bestpt.y = besty;
	return bestpt;

}

pt getpoint(int table[maxelem][maxelem], int max)  //注：数组本来就是指向一个地址的，所以不需要加引用也可以改变其中的值
{
	pt bestpt;
	bestpt.x = 0;
	bestpt.y = 0;

	bestpt.x = get_rnum(10);
	bestpt.y = get_rnum(10);

	return bestpt;
}

int GiveScore(int type, int x, int y)
{
	int i, score = 0;
	for (i = 0; i < 572; i++)
	{
		//计算机下
		if (type == 1)
		{
			if (ctable[x][y][i])
			{
				switch (win[1][i])
				{
				case 1:
					score += 5;
					break;
				case 2:
					score += 50;
					break;
				case 3:
					score += 100;
					break;
				case 4:
					score += 10000;
					break;
				default:
					break;
				}
			}
		}
		//人下
		else
		{
			if (ptable[x][y][i])
			{
				switch (win[0][i])
				{
				case 1:
					score -= 5;
					break;
				case 2:
					score -= 50;
					break;
				case 3:
					score -= 500;
					break;
				case 4:
					score -= 5000;
					break;
				default:
					break;
				}
			}
		}
	}
	return score;

}

void GetBoard(int tempboard[][15], int nowboard[][15])
{
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (i == 9)
				i = 9;
			tempboard[i][j] = nowboard[i][j];
		}
}

bool SearchBlank(int& i, int& j, int nowboard[][15])
{
	int x, y;
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
		{
			if (nowboard[x][y] == 2 && nowboard[x][y] != 3)
			{
				i = x;
				j = y;
				return true;
			}
		}
	return false;
}

void InitializeBoard()
{
	//初始化函数
	int i, j, count = 0, k;
	m_pclastpos.x = -1;
	m_pclastpos.y = -1;
	m_pplastpos.x = -1;
	m_pplastpos.y = -1;
	start = true;
	//判断哪方先开始
	if (m_bwfirst)
	{
		player = false;
		computer = true;
	}
	else
	{
		player = true;
		computer = false;
	}
	pwin = cwin = false;
	//初始化计算机和玩家的获胜组合情况
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			for (k = 0; k < 572; k++)
			{
				ptable[i][j][k] = false;
				ctable[i][j][k] = false;
			}
	for (i = 0; i < 2; i++)
		for (j = 0; j < 572; j++)
			win[i][j] = 0;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			board[i][j] = 2;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				ptable[j + k][i][count] = true;
				ctable[j + k][i][count] = true;
			}
			count++;
		}
	for (i = 0; i < 15; i++)
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				ptable[i][j + k][count] = true;
				ctable[i][j + k][count] = true;
			}
			count++;
		}
	for (i = 0; i < 11; i++)
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				ptable[j + k][i + k][count] = true;
				ctable[j + k][i + k][count] = true;
			}
			count++;
		}
	for (i = 0; i < 11; i++)
		for (j = 14; j >= 4; j--)
		{
			for (k = 0; k < 5; k++)
			{
				ptable[j - k][i + k][count] = true;
				ctable[j - k][i + k][count] = true;
			}
			count++;
		}
}





// 输出一行文字
void out(char* chars)
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), chars, lstrlen(chars), 0, 0);
}
// 绘制电脑和玩家的棋子
void out(int flag)
{
	char* chars = nullptr;
	if (flag == 0)
	{
		chars = "●";
	}
	else if (flag == 1)
	{
		chars = "■";
	}
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), chars, lstrlen(chars), 0, 0);
}
// gotoxy()，光标移动函数，用于处理文字与图画输出的位置
void gotoxy(int x, int y) //逻辑的
{
	// 逻辑原点
	int orx = 2;
	int ory = 2;
	COORD pos = { 2 * (x + orx), y + ory };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void gotoxy(pt p) //逻辑的
{
	//逻辑原点
	int orx = 2;
	int ory = 2;
	COORD pos = { 2 * (p.x + orx), p.y + ory };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void color(int n_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n_color);
}
void hidecur()
{
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 50;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}
void Chang_Console_size(int max_x, int max_y) //逻辑的
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;		                            // 窗口缓冲区信息
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bInfo);// 获取窗口缓冲区信息
	COORD size = { 2 * max_x, max_y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);  // 重新设置缓冲区大小
	SMALL_RECT rc = { 0, 0, 2 * max_x - 1, max_y - 1 };		                    // 重置窗口位置和大小
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
}

int get_rnum(int maxrand)
{
	srand((unsigned)time(NULL));
	int rnum = rand() % maxrand;
	return rnum;
}
// 获取并处理键盘输入的函数（方向键、回车键）
char getudlr()
{
	string u = "郒";   // “上” 的双ASSIC码值组合
	string d = "郟";   // “下” 的双ASSIC码值组合
	string l = "郖";   // “左” 的双ASSIC码值组合
	string r = "郙";   // “右” 的双ASSIC码值组合
	string str = "";   //  定义空串
	char ch = 0;
	do {
		ch = _getch();
		if (ch == '\r') {
			return 'e'/*enter*/;     //如果是回车就返回字符'e'
		}
		else if (ch == 'q') {
			return 'q';
		}
	} while (ch != -32);
	str = str + ch;
	ch = _getch();
	str = str + ch;

	if (str == u)
		return 'u'/*up*/;       //如果是上就返回字符'u'
	else if (str == d)
		return 'd'/*down*/;     //如果是下就返回字符'd'
	else if (str == l)
		return 'l'/*left*/;     //如果是左就返回字符'l'
	else if (str == r)
		return 'r'/*right*/;    //如果是右就返回字符'r'
	else
		return '\0';
}

void begin()
{
	InitializeBoard();
	///*//必要模块
	pt or_pt;   //光标能够到达的最左上点
	pt max_pt;  //光标能够到达的最右下点
	or_pt.x = _or_ptx;
	or_pt.y = _or_pty;
	max_pt.x = _max_ptx;
	max_pt.y = _max_pty;
	//*/
	// 固定窗口大小的语句块。等待重新写成函数
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
	RECT rc;
	GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形
	//改变cmd窗口风格
	SetWindowLongPtr(hWnd,
		GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);

	// 显示文字
	system("title og ahpla五子棋人机对战");
	system("color 30");
	Chang_Console_size(19, 19);
	hidecur();
	//
	// SetConsoleFontSize(10);
	//
	gotoxy(5, 5);
	out("五子棋");
	gotoxy(6, 12);
	out("清华大学软件学院");
	gotoxy(9, 13);
	out("野田豪 涂亦驰");
	gotoxy(5, 15);
	out("按1或2开始");
	gotoxy(0, 16);
	out("1：玩家先手  2：电脑先手");

	// 主函数循环
	while (mainflag != 0) {
		// 决定先手
		char who_first;
		int cpflag; // cpflag标记轮流走棋，当cpflag=2时为玩家下棋，当cpflag=1时为电脑下棋
		while (true) {
			who_first = _getch();
			if (who_first == '1') {
				cpflag = playturn;
				break;
			}
			else if (who_first == '2') {
				cpflag = computerturn;
				break;
			}
		}
		// 先手确定之后，清屏并绘制棋盘
		system("cls");
		gotoxy(1, 15);
		out("PS: 方向键移动，回车落子");        
		// 初始化描述棋盘落子状态的table数组，并绘制棋盘格子
		{
			for (int x = 0; x < maxelem; x++)
			{
				for (int y = 0; y < maxelem; y++)
				{
					table[x][y] = 0;
					Sleep(1);	// 避免棋盘错位的关键一句，具体为什么会错位疑似与执行速度过快光标位置错误有关
					gotoxy(x, y);
					////////////////////棋盘格子背景颜色，希望能改成米黄色//////////////////////////
					color(0xc0);
					out(table[x][y] + 1);
				}
			}
		}
		// 定义并初始化坐标追踪变量
		pt movestep;  //当前的点
		pt orstep;    //上一次的点
		movestep.x = 7;
		movestep.y = 7;
		orstep.x = 7;
		orstep.y = 7;

		gotoxy(movestep);  //定位初始落子点（此时为默认初始位置：棋盘中心）
		////////////////////棋盘光标点的形状及颜色//////////////////////////
		color(0x0f);
		out("⊙");

		char ch; // 追踪玩家键盘输入的字符变量
		bool isplaywin = false;  // 玩家是否获胜
		bool iscomputerwin = false;  // 电脑是否获胜
		while (1)
		{
			switch ((cpflag++) % 2) // 电脑和玩家轮流下棋
			{
				// 电脑下棋
				case computerturn:
				{
				//pt computerpt = getpoint(table, maxelem);
				pt computerpt = ComTurn();

				//table[computerpt.x][computerpt.y]=1;
				gotoxy(computerpt);

				if (board[computerpt.x][computerpt.y] == 1)
				{
					////////////////////电脑落子的形状及颜色//////////////////////////
					color(0x0d);
					out(0);
				}
				// 检查是否获胜
				iscomputerwin = check(computerpt, board, maxelem, 1);
				if (iscomputerwin == true)
				{
					gotoxy(5, -2);
					out("电脑胜利\a\a");
					iscomputerwin = false;
					_getch();
					system("cls");
					// TODO : 在begin里调用main的操作非常不好，应该修改
					main();
				}
			}
			break;
			// 玩家的回合
			case playturn:
			{
				int quit = 1;
				while (quit) {
					ch = getudlr(); // 获取键盘上下左右键、回车键、q字母键
					switch (ch)
					{
						case 'u': // 上
						orstep.y = movestep.y;
						orstep.x = movestep.x;
						if (movestep.y != or_pt.y)
						{
							movestep.y -= 1;
						}
						break;
					case 'd': // 下
						orstep.y = movestep.y;
						orstep.x = movestep.x;
						if (movestep.y != max_pt.y)
						{
							movestep.y += 1;
						}
						break;
					case 'l': // 左
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						if (movestep.x != or_pt.x)
						{
							movestep.x -= 1;
						}
						break;
					case 'r': // 右
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						if (movestep.x != max_pt.x)
						{
							movestep.x += 1;
						}
						break;
					case 'e': // 回车
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						// 若此处无子，可以落子
						if (board[movestep.x][movestep.y] == 2)
						{
							board[movestep.x][movestep.y] = 0;
							quit = 0;
						}
						// 检查是否获胜
						isplaywin = check(movestep, board, maxelem, 0);
						{
							m_pplastpos.x = movestep.x;
							m_pplastpos.y = movestep.y;
							for (int i = 0; i < 572; i++)
							{//修改玩家下子后棋盘状态的变化
								if (ptable[movestep.x][movestep.y][i] && win[0][i] != 7)
									win[0][i]++;
								if (ctable[movestep.x][movestep.y][i])
								{
									ctable[movestep.x][movestep.y][i] = false;
									win[1][i] = 7;
								}
							}
						}
						break;
					case 'q':  // 退出
						gotoxy(0, 15);
						out("    ");
						exit(-1);
						break;
					}
					// 恢复上一次的足迹（将上一次的棋盘点恢复至原有的样子）
					gotoxy(orstep);
					if (board[orstep.x][orstep.y] == 2)
					{
						////////////////////棋盘格子原有的形状和颜色//////////////////////////
						color(0xc0);
						out(1);
					}
					else if (board[orstep.x][orstep.y] == 1)
					{
						////////////////////棋盘格子原有的形状和颜色//////////////////////////
						color(0x0d);
						out(0);
					}
					else if (board[orstep.x][orstep.y] == 0)
					{
						////////////////////棋盘格子原有的形状和颜色//////////////////////////
						color(0x0a);
						out(0);
					}
					// 绘制当前落子点
					gotoxy(movestep);
					////////////////////光标的形状和颜色//////////////////////////
					color(0x0f);
					out("⊙");

					if (isplaywin == true)
					{
						// 当玩家胜利后，把当前点由绿色变成黄色
						gotoxy(movestep);
						////////////////////胜利后当前点的颜色//////////////////////////
						color(0x0e);
						out(0);

						gotoxy(5, -2);
						out("玩家胜利\a");
						isplaywin = false;
						_getch();
						system("cls");
						main();
					}
				}
			}
			break;
			}
		}
	}
}
/*⊙*/
