#include "essential_graph.h"
#include <iostream>
#include <windows.h>
int main()
{
    initgraph(400, 482);   // 创建绘图窗口，大小为 242*482 像素，横向20个方格，纵向40个方格
/*	HWND hwnd = GetHWnd(); // 全屏代码
	SetWindowLong(hwnd , GWL_STYLE , GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hwnd , HWND_TOP , 0 , 0 , GetSystemMetrics(SM_CXSCREEN) , GetSystemMetrics(SM_CXSCREEN) , SWP_SHOWWINDOW);*/
	line(243, 0, 243, 481);
	srand(clock());
	Graph *p;
	int flag = 0;
	settextcolor(WHITE);
	settextstyle(5, 7, 0);
	TCHAR s1[] = _T("Score : ");
	outtextxy(260, 241, s1);
	int a;
	while(true){
		TCHAR s[12];
		_stprintf_s(s, _T("%d"), score);
		outtextxy(320, 241, s);
		red = 0, yellow = 0, green = 0, blue = 0;
		pause_time = 300 - clock()/1000 + time_bonus * 100;
		if (flag == 0){                   // 生成图形
			switch (rand() %7){
			case 0: 
				p = new L1(10, 0);
				break;
			case 1: 
				p = new L2(10, 0);
				break;
			case 2: 
				p = new Solid(10, 0);
				break;
			case 3: 
				p = new Rope(10, 0);
				break;
			case 4: 
				p = new Tu(10, 0);
				break;
			case 5: 
				p = new Zhe1(10, 0);
				break;
			case 6: 
				p = new Zhe2(10, 0);
				break;
			}
			flag = 1;
		}
		int fall_return;
		if (kbhit()){
			switch (_getch()){              // 输入控制
				case 'w':
					(*p).clockwise_rotate();
					fall_return = (*p).move_down();
					break;
				case 'W':
					(*p).clockwise_rotate();
					fall_return = (*p).move_down();
					break;
				case 's':
					(*p).counterclockwise_rotate();
					fall_return = (*p).move_down();
					break;
				case 'S':
					(*p).counterclockwise_rotate();
					fall_return = (*p).move_down();
					break;
				case 'a':
					(*p).move_left();
					fall_return = (*p).move_down();
					break;
				case 'A':
					(*p).move_left();
					fall_return = (*p).move_down();
					break;
				case 'd':
					(*p).move_right();
					fall_return = (*p).move_down();
					break;
				case 'D':
					(*p).move_right();
					fall_return = (*p).move_down();
					break;
				case ' ':
					(*p).move_down();
					fall_return = (*p).move_down();
					break;
				case 'b':
					while((*p).move_down() != 0){Sleep(15);}
					fall_return = (*p).move_down();
				case 'B':
					while((*p).move_down() != 0){Sleep(15);}
					fall_return = (*p).move_down();
             /*	case 'p':                            // 暂停功能尚不完善
					_getch();
					fall_return = 0;
					break;
				case 'P':
					_getch();
					fall_return = 0;
					break;*/
				default:
					fall_return = (*p).move_down();
			}
		}
		else fall_return = (*p).move_down();
		if (fall_return == 0){
			if ((*p).cube[0].y == 0 || (*p).cube[1].y == 0 || (*p).cube[2].y == 0 || (*p).cube[3].y == 0){  //判断游戏是否结束
				delete p;
				TCHAR s2[] = _T("Game over");
				outtextxy(260, 261, s2);
				Sleep(4000);
				closegraph();
				return 0;
			}
			else {
				flag = 0;
				delete p;
			}
		}
		int last_delete = 1;
		while ((a = game.check_line()) && a >= 0 && last_delete == 1){  // 消行检测
			if (fall_return == 0){
				game.delete_line(a);
				last_delete = 1;
			}
			else last_delete = 0;
		}
		Sleep(pause_time);
	}
    closegraph();          // 关闭绘图窗口
}