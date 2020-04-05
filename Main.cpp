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

// �����ϵ����ӵ㣬��225������(0, 0)��(14, 14))
struct pt
{
	int x; // ����x�����ϵ����꣬��0��ʼ
	int y; // ����y�����ϵ����꣬��0��ʼ
};

#pragma endregion

#pragma region virables

#define _or_ptx      0   // ����ԭ��x����
#define _or_pty      0   // ����ԭ��y����
#define _max_ptx    14   // �������x����
#define _max_pty    14   // �������y����
#define computerturn 1   // �ֵ���������
#define playturn     0   // �ֵ��������
#define maxelem     15   // ���̴�С�������У�����Ϊ15*15

pt m_pplastpos; // ����ߵ���һ����
pt m_pclastpos; // ������ߵ���һ����
bool m_bwfirst = false; // ���˭���ߣ�1Ϊ�������ߣ�0Ϊ�������
bool m_binit = false; // �ж���Ϸ�Ƿ��Ǵ��ڸտ�ʼ�׶�

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

static int mainflag = 0; // ָʾ�������Ƿ�ı䣬���û�иı��������������ֱ���ı�Ϊֹ

#pragma endregion

#pragma region declaration

// ��ʼ�����̺���
void InitializeBoard();

pt ComTurn();
int GiveScore(int type, int x, int y);
bool SearchBlank(int& i, int& j, int nowboard[][15]);
void GetBoard(int tempboard[][15], int nowboard[][15]);

pt getpoint(int table[maxelem][maxelem], int max);  // ���鱾������ָ��һ����ַ�ģ����Բ���Ҫ������Ҳ���Ըı����е�ֵ


int table[maxelem][maxelem];   // �������飬�����˻���Ч�����հ�λ�ü�Ϊ0������������ӱ��Ϊ1������������ɫ0x0b����������ӱ��Ϊ2�����������ɫ0x0e��

void gotoxy(int x, int y);  // �����ƣ�������ƶ�����x�е�y��
void gotoxy(pt p);   // ������ƶ�������p��

void   Chang_Console_size(int max_x,   // x�����ϵĳ��ȣ�����ֵ��1��ʼ 
	int max_y);  // y�����ϵĳ��ȣ�����ֵ��1��ʼ
void   color(int n_color);             // n_colorΪ��ɫֵ��ʮ��������ʽ

void   out(char* chars);   // ���chars��ָ����ַ���
void   out(int flag);      // ���溯����������ʽ��flag = 0ʱ�����flag = 1ʱ����������Ի�������

void   hidecur();          // ���ع��
char   getudlr();          // �����������Ҽ��س�����
int get_rnum(int maxrand);  // �õ�һ��������maxrand�������

bool check(pt checkpoint, int table[maxelem][maxelem], int max, int checkcpflag);  // ����Ƿ��ʤ��checkcpflag=1�Ǽ������Ƿ��ʤ��checkcpflag=2�Ǽ������Ƿ��ʤ
void begin();

#pragma endregion

int main()
{
	begin();
	while (mainflag++ != 0) { _getch(); _getch(); };
	main();
	return 0;
}

bool check(pt checkpoint, int board[maxelem][maxelem], int max, int checkcpflag)  //����Ƿ��ʤ��checkcpflag=1�Ǽ������Ƿ��ʤ��checkcpflag=0�Ǽ������Ƿ��ʤ
{//��ģ����ڵ����⣺��Ե�ж�����BUG
	switch (checkcpflag)
	{
	case 1:
		if (1)
		{
			int ncount = 0;
			int ncount1 = 0;
			int ncount2 = 0;
			//����ɨ��
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
			//����ɨ��
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
			//����������ɨ��
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
			// ����������ɨ��
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
			//����ɨ��
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
			//����ɨ��
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
			//����������ɨ��
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
			//����������ɨ��
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
// �������庯��
pt ComTurn()
{
	// bestx��bestyΪ��ǰ���λ�ã�i��j�������µĸ���λ�ã�pi��pj�Ǽ�������µĸ���λ��
	int bestx = -1, besty = -1;
	int i, j, pi, pj, ptemp, ctemp, pscore = 10, cscore = -10000, ctempboard[15][15], ptempboard[15][15];
	int m, n, temp1[20], temp2[20];//�ݴ��һ����������Ϣ
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
	{//Ѱ�����λ��
		GetBoard(ctempboard, board);
		while (SearchBlank(i, j, ctempboard))
		{
			n = 0;
			pscore = 10;
			GetBoard(ptempboard, board);
			ctempboard[i][j] = 3;//����ѱ�����
			ctemp = GiveScore(1, i, j);
			for (m = 0; m < 572; m++)
			{//��ʱ���������Ϣ
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

				ptempboard[i][j] = 3;//����ѱ�����
				ptemp = GiveScore(0, i, j);
				if (pscore > ptemp)////��ʱΪ������ӣ����ü�С����ʱӦѡȡ��Сֵ
					pscore = ptemp;
			}
			for (m = 0; m < n; m++)
			{//�ָ������Ϣ
				ptable[pi][pj][temp1[m]] = true;
				win[0][temp1[m]] = temp2[m];
			}
			if (ctemp + pscore > cscore)//��ʱΪ��������ӣ����ü�С����ʱӦѡȡ�����ֵ
			{
				cscore = ctemp + pscore;
				bestx = pi;
				besty = pj;
			}
		}
	}


	board[bestx][besty] = 1;




	for (i = 0; i < 572; i++)
	{//�޸ļ�������Ӻ����̵ı仯״��
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

pt getpoint(int table[maxelem][maxelem], int max)  //ע�����鱾������ָ��һ����ַ�ģ����Բ���Ҫ������Ҳ���Ըı����е�ֵ
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
		//�������
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
		//����
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
	//��ʼ������
	int i, j, count = 0, k;
	m_pclastpos.x = -1;
	m_pclastpos.y = -1;
	m_pplastpos.x = -1;
	m_pplastpos.y = -1;
	start = true;
	//�ж��ķ��ȿ�ʼ
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
	//��ʼ�����������ҵĻ�ʤ������
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





// ���һ������
void out(char* chars)
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), chars, lstrlen(chars), 0, 0);
}
// ���Ƶ��Ժ���ҵ�����
void out(int flag)
{
	char* chars = nullptr;
	if (flag == 0)
	{
		chars = "��";
	}
	else if (flag == 1)
	{
		chars = "��";
	}
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), chars, lstrlen(chars), 0, 0);
}
// gotoxy()������ƶ����������ڴ���������ͼ�������λ��
void gotoxy(int x, int y) //�߼���
{
	// �߼�ԭ��
	int orx = 2;
	int ory = 2;
	COORD pos = { 2 * (x + orx), y + ory };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void gotoxy(pt p) //�߼���
{
	//�߼�ԭ��
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
void Chang_Console_size(int max_x, int max_y) //�߼���
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;		                            // ���ڻ�������Ϣ
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bInfo);// ��ȡ���ڻ�������Ϣ
	COORD size = { 2 * max_x, max_y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);  // �������û�������С
	SMALL_RECT rc = { 0, 0, 2 * max_x - 1, max_y - 1 };		                    // ���ô���λ�úʹ�С
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
}

int get_rnum(int maxrand)
{
	srand((unsigned)time(NULL));
	int rnum = rand() % maxrand;
	return rnum;
}
// ��ȡ�������������ĺ�������������س�����
char getudlr()
{
	string u = "�H";   // ���ϡ� ��˫ASSIC��ֵ���
	string d = "�P";   // ���¡� ��˫ASSIC��ֵ���
	string l = "�K";   // ���� ��˫ASSIC��ֵ���
	string r = "�M";   // ���ҡ� ��˫ASSIC��ֵ���
	string str = "";   //  ����մ�
	char ch = 0;
	do {
		ch = _getch();
		if (ch == '\r') {
			return 'e'/*enter*/;     //����ǻس��ͷ����ַ�'e'
		}
		else if (ch == 'q') {
			return 'q';
		}
	} while (ch != -32);
	str = str + ch;
	ch = _getch();
	str = str + ch;

	if (str == u)
		return 'u'/*up*/;       //������Ͼͷ����ַ�'u'
	else if (str == d)
		return 'd'/*down*/;     //������¾ͷ����ַ�'d'
	else if (str == l)
		return 'l'/*left*/;     //�������ͷ����ַ�'l'
	else if (str == r)
		return 'r'/*right*/;    //������Ҿͷ����ַ�'r'
	else
		return '\0';
}

void begin()
{
	InitializeBoard();
	///*//��Ҫģ��
	pt or_pt;   //����ܹ�����������ϵ�
	pt max_pt;  //����ܹ�����������µ�
	or_pt.x = _or_ptx;
	or_pt.y = _or_pty;
	max_pt.x = _max_ptx;
	max_pt.y = _max_pty;
	//*/
	// �̶����ڴ�С�����顣�ȴ�����д�ɺ���
	HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
	RECT rc;
	GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����
	//�ı�cmd���ڷ��
	SetWindowLongPtr(hWnd,
		GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);

	// ��ʾ����
	system("title og ahpla�������˻���ս");
	system("color 30");
	Chang_Console_size(19, 19);
	hidecur();
	//
	// SetConsoleFontSize(10);
	//
	gotoxy(5, 5);
	out("������");
	gotoxy(6, 12);
	out("�廪��ѧ���ѧԺ");
	gotoxy(9, 13);
	out("Ұ��� Ϳ���");
	gotoxy(5, 15);
	out("��1��2��ʼ");
	gotoxy(0, 16);
	out("1���������  2����������");

	// ������ѭ��
	while (mainflag != 0) {
		// ��������
		char who_first;
		int cpflag; // cpflag����������壬��cpflag=2ʱΪ������壬��cpflag=1ʱΪ��������
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
		// ����ȷ��֮����������������
		system("cls");
		gotoxy(1, 15);
		out("PS: ������ƶ����س�����");        
		// ��ʼ��������������״̬��table���飬���������̸���
		{
			for (int x = 0; x < maxelem; x++)
			{
				for (int y = 0; y < maxelem; y++)
				{
					table[x][y] = 0;
					Sleep(1);	// �������̴�λ�Ĺؼ�һ�䣬����Ϊʲô���λ������ִ���ٶȹ�����λ�ô����й�
					gotoxy(x, y);
					////////////////////���̸��ӱ�����ɫ��ϣ���ܸĳ��׻�ɫ//////////////////////////
					color(0xc0);
					out(table[x][y] + 1);
				}
			}
		}
		// ���岢��ʼ������׷�ٱ���
		pt movestep;  //��ǰ�ĵ�
		pt orstep;    //��һ�εĵ�
		movestep.x = 7;
		movestep.y = 7;
		orstep.x = 7;
		orstep.y = 7;

		gotoxy(movestep);  //��λ��ʼ���ӵ㣨��ʱΪĬ�ϳ�ʼλ�ã��������ģ�
		////////////////////���̹������״����ɫ//////////////////////////
		color(0x0f);
		out("��");

		char ch; // ׷����Ҽ���������ַ�����
		bool isplaywin = false;  // ����Ƿ��ʤ
		bool iscomputerwin = false;  // �����Ƿ��ʤ
		while (1)
		{
			switch ((cpflag++) % 2) // ���Ժ������������
			{
				// ��������
				case computerturn:
				{
				//pt computerpt = getpoint(table, maxelem);
				pt computerpt = ComTurn();

				//table[computerpt.x][computerpt.y]=1;
				gotoxy(computerpt);

				if (board[computerpt.x][computerpt.y] == 1)
				{
					////////////////////�������ӵ���״����ɫ//////////////////////////
					color(0x0d);
					out(0);
				}
				// ����Ƿ��ʤ
				iscomputerwin = check(computerpt, board, maxelem, 1);
				if (iscomputerwin == true)
				{
					gotoxy(5, -2);
					out("����ʤ��\a\a");
					iscomputerwin = false;
					_getch();
					system("cls");
					// TODO : ��begin�����main�Ĳ����ǳ����ã�Ӧ���޸�
					main();
				}
			}
			break;
			// ��ҵĻغ�
			case playturn:
			{
				int quit = 1;
				while (quit) {
					ch = getudlr(); // ��ȡ�����������Ҽ����س�����q��ĸ��
					switch (ch)
					{
						case 'u': // ��
						orstep.y = movestep.y;
						orstep.x = movestep.x;
						if (movestep.y != or_pt.y)
						{
							movestep.y -= 1;
						}
						break;
					case 'd': // ��
						orstep.y = movestep.y;
						orstep.x = movestep.x;
						if (movestep.y != max_pt.y)
						{
							movestep.y += 1;
						}
						break;
					case 'l': // ��
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						if (movestep.x != or_pt.x)
						{
							movestep.x -= 1;
						}
						break;
					case 'r': // ��
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						if (movestep.x != max_pt.x)
						{
							movestep.x += 1;
						}
						break;
					case 'e': // �س�
						orstep.x = movestep.x;
						orstep.y = movestep.y;
						// ���˴����ӣ���������
						if (board[movestep.x][movestep.y] == 2)
						{
							board[movestep.x][movestep.y] = 0;
							quit = 0;
						}
						// ����Ƿ��ʤ
						isplaywin = check(movestep, board, maxelem, 0);
						{
							m_pplastpos.x = movestep.x;
							m_pplastpos.y = movestep.y;
							for (int i = 0; i < 572; i++)
							{//�޸�������Ӻ�����״̬�ı仯
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
					case 'q':  // �˳�
						gotoxy(0, 15);
						out("    ");
						exit(-1);
						break;
					}
					// �ָ���һ�ε��㼣������һ�ε����̵�ָ���ԭ�е����ӣ�
					gotoxy(orstep);
					if (board[orstep.x][orstep.y] == 2)
					{
						////////////////////���̸���ԭ�е���״����ɫ//////////////////////////
						color(0xc0);
						out(1);
					}
					else if (board[orstep.x][orstep.y] == 1)
					{
						////////////////////���̸���ԭ�е���״����ɫ//////////////////////////
						color(0x0d);
						out(0);
					}
					else if (board[orstep.x][orstep.y] == 0)
					{
						////////////////////���̸���ԭ�е���״����ɫ//////////////////////////
						color(0x0a);
						out(0);
					}
					// ���Ƶ�ǰ���ӵ�
					gotoxy(movestep);
					////////////////////������״����ɫ//////////////////////////
					color(0x0f);
					out("��");

					if (isplaywin == true)
					{
						// �����ʤ���󣬰ѵ�ǰ������ɫ��ɻ�ɫ
						gotoxy(movestep);
						////////////////////ʤ����ǰ�����ɫ//////////////////////////
						color(0x0e);
						out(0);

						gotoxy(5, -2);
						out("���ʤ��\a");
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
/*��*/
