#include "essential_graph.h"
void ui();
void menu();
void start_game();
void achievement();
void cut_background();
int unlock_achievement(int);
void help();
void about();
MOUSEMSG mouse;
int ach[18] = {0};
bool flag[10] = {true, true, true, true, true, true, true, true, true, true};
int rainbow;
fstream ach_file;
int play_times = 0;
TCHAR num;
int main(){
	srand(time(0));
	num = (TCHAR)(rand() % 7) + '0';
	ach_file.open("resource\\achievement.txt", ios::app);
	ach_file.close();
	ui();
	return 0;
}
void ui(){
	menu();
	bool flag = true;
	while(flag == true){
		//获取鼠标点击信息
		mouse = GetMouseMsg();
		int x = mouse.x;
		int y = mouse.y;
		if (x >= 150 && x <= 250 && y >= 100 && y <= 140){
			if(mouse.uMsg == WM_LBUTTONDOWN){
				play_times++;
				closegraph();
				start_game();
				ui();
				return;
			}
		}
		if (x >= 150 && x <= 250 && y >= 170 && y <= 210){
			if(mouse.uMsg == WM_LBUTTONDOWN){
				closegraph();				
				help();
				_getch();
				closegraph();	
				ui();
				return;
			}
		}
		if (x >= 150 && x <= 250 && y >= 240 && y <= 280){
			if(mouse.uMsg == WM_LBUTTONDOWN){		
				closegraph();				
				achievement();
				_getch();
				closegraph();	
				ui();
				return;
			}
		}
		if (x >= 150 && x <= 250 && y >= 310 && y <= 350){
			if(mouse.uMsg == WM_LBUTTONDOWN){		
				closegraph();				
				about();
				closegraph();	
				ui();
				return;
			}
		}
		if (x >= 150 && x <= 250 && y >= 380 && y <= 420){
			if(mouse.uMsg == WM_LBUTTONDOWN){	
				closegraph();
				flag = false;
				return;
			}
		}
	}
}
void cut_background(){
	for (int i = 0; i <= 21; i++){
		for (int j = 0; j <= 39; j++){
			getimage(&bg[i][j], 2+12*i, 2+12*j, 11, 11);
		}
	}
	getimage(&ach_shelter, 260, 350, 140, 150);
	getimage(&score_shelter, 315, 236, 20, 20);
}
void menu(){
	initgraph(400, 482);
	TCHAR path[16];
	path[0] = 'r'; path[1] = 'e'; path[2] = 's'; path[3] = 'o'; path[4] = 'u'; path[5] = 'r'; path[6] = 'c'; path[7] = 'e'; 
	path[8] = '\\'; path[9] = '\\';
	path[10] = num;
	path[11] = '.';
	path[12] = 'j';
	path[13] = 'p';
	path[14] = 'g';
	path[15] = '\0';
	loadimage(&img, path);
	loadimage(&surprise, "resource\\hhh.jpg");
	putimage(0,0,&img);
	cut_background();
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(25, 12, _T("华文彩云"));
	TCHAR str0[] = _T("俄罗斯方块");
	TCHAR str1[] = _T("开始游戏");
	TCHAR str2[] = _T("帮助");
	TCHAR str3[] = _T("成就");
	TCHAR str4[] = _T("关于");
	TCHAR str5[] = _T("结束游戏");
	outtextxy(150, 120, str1);
	outtextxy(150, 190, str2);
	outtextxy(150, 260, str3);
	outtextxy(150, 330, str4);
	outtextxy(150, 400, str5);
	settextstyle(25, 12.5, 0);
	outtextxy(140, 40, str0);
}
void start_game(){
	int start_time = clock();
    initgraph(400, 482);   // 创建绘图窗口，大小为 242*482 像素，横向20个方格，纵向40个方格
/*	HWND hwnd = GetHWnd(); // 全屏代码
	SetWindowLong(hwnd , GWL_STYLE , GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hwnd , HWND_TOP , 0 , 0 , GetSystemMetrics(SM_CXSCREEN) , GetSystemMetrics(SM_CXSCREEN) , SWP_SHOWWINDOW);*/
	putimage(0,0,&img);
	line(243, 0, 243, 481);
	setbkmode(TRANSPARENT);
	game.initialize();
	ach_file.open("resource\\achievement.txt", ios::in|ios::out);
	srand(time(0));
	Graph *p;
	int graph_flag = 0;
	settextcolor(WHITE);
	settextstyle(5, 7, 0);
	TCHAR s1[] = _T("Score : ");
	outtextxy(260, 241, s1);
	int timer[10];
	bool flag_ach5 = false;
	int timer_ach5 = 0;
	int bubble = 0;
	int ach3 = 0;
	int clear = 1;
	int ach_show = 0;
	int a;
	int fall_return;
	int limit = 0;
	score_plus(0);
	while(true){
		red = 0, yellow = 0, green = 0, blue = 0;
		ach3 = 0;
		pause_time = 260 - (clock()-start_time)/2000 + time_bonus * 60;
		if (pause_time > 400){ 
			pause_time = 400;
			if (unlock_achievement(4)){
				TCHAR achievement[] = _T("时间锁定  已解锁");
				outtextxy(260, 350+20*ach_show, achievement);
				timer[4] = clock();
				ach_show++;
			}
			if (ach[4] && flag[4]){
				if (clock() - timer[4] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[4] = false;
					ach_show--;
				}
			}
		}
		if (play_times >= 5){ 
			if (unlock_achievement(8)){
				TCHAR achievement[] = _T("隐藏成就 真香");
				TCHAR achievement1[] = _T("已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				outtextxy(260, 370+20*ach_show, achievement1);
				timer[8] = clock();
				ach_show++;
			}
			if (ach[8] && flag[8]){
				if (clock() - timer[8] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[8] = false;
					ach_show--;
				}
			}
		}
		if (pause_time < 120) {
			pause_time = 120;
			if (!flag_ach5) {
				timer_ach5 = clock();
				flag_ach5 = true;
			}
			if (clock() - timer_ach5 >= 600000){
				if (unlock_achievement(5)){
					TCHAR achievement[] = _T("临危不乱  已解锁");
					outtextxy(260, 350+20*ach_show, achievement);
					timer[5] = clock();
					ach_show++;
				}
				if (ach[5] && flag[5]){
					if (clock() - timer[5] >= 5000){
						putimage(260, 350, &ach_shelter);
						flag[5] = false;
						ach_show--;
					}
				}
			}
		}
		for (int i = 0; i <= 9; i++){
			ach_file >> ach[i];
		}
		ach_file.close();
		if (graph_flag == 0){                   // 生成图形
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
			graph_flag = 1;
		}
		if (kbhit()){
			switch (_getch()){              // 输入控制
				case 'w':
					fall_return = (*p).move_down();
					(*p).clockwise_rotate();
					break;
				case 'W':
					fall_return = (*p).move_down();
					(*p).clockwise_rotate();
					break;
				case 's':
					fall_return = (*p).move_down();
					(*p).counterclockwise_rotate();
					break;
				case 'S':
					fall_return = (*p).move_down();
					(*p).counterclockwise_rotate();
					break;
				case 'a':
					fall_return = (*p).move_down();
					(*p).move_left();
					limit = 0;
					break;
				case 'A':
					fall_return = (*p).move_down();
					(*p).move_left();
					limit = 0;
					break;
				case 'd':
					fall_return = (*p).move_down();
					(*p).move_right();
					limit = 0;
					break;
				case 'D':
					fall_return = (*p).move_down();
					(*p).move_right();
					limit = 0;
					break;
				case ' ':
					(*p).move_down();
					fall_return = (*p).move_down();
					break;
				case 'b':
					while((*p).move_down() != 0){Sleep(5);}
					fall_return = (*p).move_down();
					break;
				case 'B':
					while((*p).move_down() != 0){Sleep(5);}
					fall_return = (*p).move_down();
					break;
             	case 'p':                        
					_getch();
					fall_return = (*p).move_down();
					break;
				case 'P':
					_getch();
					fall_return = (*p).move_down();
					break;
				case 'c':
					if (clear == 1){
						for (int i = 39; i >= 0; i--){
							game.delete_line(39);
							score_plus(-10);
						}
						graph_flag = 0;
						fall_return = 1;
						clear = 0;
						delete p;
					}
					else{
						fall_return = (*p).move_down();
					}
					break;
				case 'C':
					if (clear == 1){
						for (int i = 39; i >= 0; i--){
							game.delete_line(39);
							score_plus(-10);
						}
						graph_flag = 0;
						fall_return = 1;
						clear = 0;
						delete p;
					}
					else{
						fall_return = (*p).move_down();
					}
					break;
				default:
					fall_return = (*p).move_down();
			}
		}
		else fall_return = (*p).move_down();
		if (fall_return == 0){
			if ((*p).cube[0].y == 0 || (*p).cube[1].y == 0 || (*p).cube[2].y == 0 || (*p).cube[3].y == 0){  //判断游戏是否结束
				delete p;
				TCHAR s2[] = _T("Game over");
				outtextxy(260, 271, s2);
				TCHAR s3[] = _T("按回车键返回主菜单");
				outtextxy(260, 291, s3);
				graph_flag = 0;
				fall_return = 1;
				score = 0;
				cin.ignore(1024,'\n');
				closegraph();
				ach_file.close();
				break;
			}
			else {
				if (limit == 0){
					limit = 1;
				}
				else {
					limit = 0;
					graph_flag = 0;
					delete p;
				}
			}
		}
		int last_delete = 1;
		while ((a = game.check_line()) && a >= 0 && last_delete == 1){  // 消行检测
			if (fall_return == 0){
				rainbow = game.delete_line(a);
				if (a != 39){
					bubble = game.count_bubble(a+1);
				}
				last_delete = 1;
				ach3++;
			}
			else last_delete = 0;
		}
		if (bubble >= 1){
			if (unlock_achievement(2)){
				TCHAR achievement[] = _T("气泡  已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				timer[2] = clock();
				ach_show++;
			}
			if (ach[2] && flag[2]){
				if (clock() - timer[2] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[2] = false;
					ach_show--;
				}
			}
		}
		if (rainbow){
			if (unlock_achievement(1)){
				TCHAR achievement[] = _T("彩虹  已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				timer[1] = clock();
				ach_show++;
			}
			if (ach[1] && flag[1]){
				if (clock() - timer[1] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[1] = false;
					ach_show--;
				}
			}
		}
		if (score >= 200){
			if (unlock_achievement(0)){
				TCHAR achievement[] = _T("大师  已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				timer[0] = clock();
				ach_show++;
			}
			if (ach[0] && flag[0]){
				if (clock() - timer[0] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[0] = false;
					ach_show--;
				}
			}
		}
		if (ach3 >= 3){
			if (unlock_achievement(3)){
				TCHAR achievement[] = _T("势如破竹  已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				timer[3] = clock();
				ach_show++;
			}
			if (ach[3] && flag[3]){
				if (clock() - timer[3] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[3] = false;
					ach_show--;
				}
			}
		}
		if (clear == 0){
			if (unlock_achievement(6)){
				TCHAR achievement[] = _T("隐藏成就 一键清空");
				TCHAR achievement1[] = _T("已解锁");
				settextcolor(WHITE);
				outtextxy(260, 350+20*ach_show, achievement);
				outtextxy(260, 370+20*ach_show, achievement1);
				timer[6] = clock();
				ach_show++;
			}
			if (ach[6] && flag[6]){
				if (clock() - timer[6] >= 5000){
					putimage(260, 350, &ach_shelter);
					flag[6] = false;
					ach_show--;
				}
			}
		}
		Sleep(pause_time);
	}
}
void achievement(){
	initgraph(700, 482);
	putimage(0,0,&img);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 10, _T("楷体"));
	ach_file.open("resource\\achievement.txt", ios::in);
	for (int i = 0; i <= 17; i++){
		ach_file >> ach[i];
	}
	ach_file.close();
	TCHAR str0[] = _T("大师：单次游戏积分达到200以上");    // 单次游戏积分达到150以上			  
	TCHAR str1[] = _T("彩虹：消去某行时带有10个以上颜色块");      // 消去某行时带有10个以上颜色块 
	TCHAR str2[] = _T("气泡：消去某行时下一行带有5个以上空格");    // 消去某行时下一行带有5个以上空格
	TCHAR str3[] = _T("势如破竹：连续消去三行");  // 连续消去三行
	TCHAR str4[] = _T("时间锁定：方块下落速度降到最慢");   // 方块下落速度降到最慢
	TCHAR str5[] = _T("临危不乱：在最高速度下坚持1分钟");   // 在最高速度下坚持1分钟
	TCHAR str61[] = _T("隐藏成就"); // 隐藏按键C（消光）
	TCHAR str62[] = _T("隐藏成就 一键清空：使用一次c键（每次游戏仅能使用一次）");
	TCHAR str71[] = _T("隐藏成就"); // 隐藏界面
	TCHAR str72[] = _T("隐藏成就 0 error(s),0 warning(s)：发现隐藏图片"); 
	TCHAR str81[] = _T("隐藏成就"); // 真香（连续玩5局游戏)
	TCHAR str82[] = _T("隐藏成就 真香：连续进行5回合游戏");
	TCHAR str11[] = _T("按任意键返回");
	outtextxy(50, 20, str0);
	outtextxy(50, 70, str1);
	outtextxy(50, 120, str2);
	outtextxy(50, 170, str3);
	outtextxy(50, 220, str4);
	outtextxy(50, 270, str5);
	if (ach[6] == 0 || ach[15] != ((6 * 6 - 5) * 6 + 18) * 3){
		outtextxy(50, 320, str61);
	}
	else{
		outtextxy(50, 320, str62);
	}
	if (ach[7] == 0 || ach[16] != ((7 * 7 - 5) * 7 + 18) * 3){
		outtextxy(50, 370, str71);
	}
	else{
		outtextxy(50, 370, str72);
	}
	if (ach[8] == 0 || ach[17] != ((8 * 8 - 5) * 8 + 18) * 3){
		outtextxy(50, 420, str81);
	}
	else{
		outtextxy(50, 420, str82);
	}
//	outtextxy(300, 400, str11);
	TCHAR stra[] = _T("已解锁");
	TCHAR strb[] = _T("未解锁");
	for (int i = 0; i <= 8; i++){
		if (ach[i] == 1 && ach[i+9] == ((i * i -5) * i + 18) * 3) outtextxy(600, 20+50*i, stra);
		else outtextxy(600, 20+50*i, strb);
	}
}
int unlock_achievement(int num){
	ach_file.open("resource\\achievement.txt", ios::in);
	if (ach_file.eof()){
		ach_file.close();
		ach_file.open("resource\\achievement.txt", ios::out|ios::app);
		for (int i = 0; i <= 17; i++){
			ach_file << " " << 0;
		}
		ach_file.close();
		ach_file.open("resource\\achievement.txt", ios::in);
	}
	for (int i = 0; i <= 17; i++){
		ach_file >> ach[i];
	}
	ach_file.close();
	if (ach[num] == 0){
		ach[num] = 1;
		ach[num+9] = ((num * num -5) * num + 18) * 3; //简单加密
		ach_file.open("resource\\achievement.txt", ios::out|ios::binary);
		for (int i = 0; i <= 17; i++){
			ach_file << " " << ach[i];
		}
		ach_file.close();
		return 1;
	}
	else return 0;
}
void help(){
	initgraph(700, 482);
	putimage(0,0,&img);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(20, 10, _T("楷体"));
	TCHAR str0[] = _T("操控方式：");
	TCHAR str1[] = _T("ad键左右平移");
	TCHAR str2[] = _T("ws键顺逆时针旋转");
	TCHAR str3[] = _T("空格键加速下落");
	TCHAR str4[] = _T("b键直接落到底");
	TCHAR str5[] = _T("p键暂停");
	TCHAR str6[] = _T("奖励方块：当三个非白色的同色块被同时消去时，触发对应的奖励效果");
	TCHAR str7[] = _T("红色：额外+30分");
	TCHAR str8[] = _T("黄色：额外消去此行上方的一行，无论那行是否填满");
	TCHAR str9[] = _T("绿色：方块下落速度减缓");
	TCHAR str10[] = _T("蓝色：有色块出现概率增大");
	TCHAR str11[] = _T("按任意键返回");
	outtextxy(10, 10, str0);
	outtextxy(50, 40, str1);
	outtextxy(50, 70, str2);
	outtextxy(50, 100, str3);
	outtextxy(50, 130, str4);
	outtextxy(50, 160, str5);
	outtextxy(10, 190, str6);
	outtextxy(50, 220, str7);
	outtextxy(50, 250, str8);
	outtextxy(50, 280, str9);
	outtextxy(50, 310, str10);
	outtextxy(300, 400, str11);
}
void about(){
	initgraph(700, 482);
	putimage(0,0,&img);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(20, 10, _T("楷体"));
	TCHAR str11[] = _T("按任意键返回");
	TCHAR str0[] = _T("developed by forangel");
	TCHAR str1[] = _T("sincerely thank LX for his help");
	TCHAR str2[] = _T("source:https://github.com/codeReaderr/origin");
	outtextxy(50, 100, str0);
	outtextxy(50, 150, str1);
	outtextxy(50, 200, str2);
	outtextxy(300, 400, str11);
	line(680,462,680,482);
	line(680,462,700,462);
	MOUSEMSG mouse1;
	ach_file.open("resource\\achievement.txt", ios::in);
	for (int i = 0; i <= 8; i++){
		ach_file >> ach[i];
	}
	ach_file.close();
	while(true){
		mouse1 = GetMouseMsg();
		int x = mouse1.x;
		int y = mouse1.y;
		if (x >= 680 && x <= 700 && y >= 462 && y <= 482){
			if(mouse1.uMsg == WM_LBUTTONDOWN){
				closegraph();
				initgraph(512,451);
				putimage(0,0,&surprise);
				Sleep(2000);
				unlock_achievement(7);
				closegraph();
				ui();
				return;
			}
		}
		if (_kbhit()){
			break;
		}
	}
}