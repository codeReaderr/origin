#include <easyx.h>
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include <ctime>
//类声明开始
class Cube{
public:
	int x,y;
	int num;
	int color;
	static int total_num; //图形数编号
	Cube():color(0){};    //内存垃圾导致的bug（new Graph继承了前一个Graph的内存）
	Cube(int m, int n):x(m), y(n), color(0){num = total_num;}
	Cube(int m, int n, int color):x(m), y(n), color(color){num = total_num;}
	void setxy(int m, int n){x = m, y = n;}
	void set_color(int color1){color = color1;}
	~Cube(){
		x = 0;
		y = 0;
		color = 0;
	}
};
int Cube::total_num = 0;
int score = 0;
int pause_time;
int time_bonus = 0;
int n = 5;  // 颜色出现概率分母
int red = 0, yellow = 0, green = 0, blue = 0;  // 颜色块计数
class Game{            // 所有cube的集合
private:
	int cube_exist[20][40];
	int cube_color[20][40];  //方块颜色：0=白色，1=红色，2=黄色，3=绿色，4=蓝色
public:
	Game();
	friend void draw_cube(int x, int y);
	friend void draw_cube(int x, int y, int color);
	friend void delete_cube(int x, int y);
	friend class L1;
	friend class L2;
	friend class Solid;
	friend class Rope;
	friend class Tu;
	friend class Zhe1;
	friend class Zhe2;
	void create_cube(int x, int y);
	void delete_line(int y);
	int check_line();
	void check_color(int y);
};	
Game game;
//图形类
class Graph{
public:
	virtual int move_down() = 0;
	virtual int move_left() = 0;
	virtual int move_right() = 0;
	virtual int clockwise_rotate() = 0;
	virtual int counterclockwise_rotate() = 0;
	friend void judge_beyond(Graph *p);
	Cube cube[4];
	int have_color;             // 该图形是否有带颜色
	Graph(){
		if (rand() %n > 0) have_color = 1;
		else have_color = 0;
	}
};
class L1:public Graph{
private:
	int num;
	int rotate_state;
	static int total_num;
public:
	L1(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m, n+1);
		cube[2].setxy(m, n+2);
		cube[3].setxy(m+1, n+2);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Cube::total_num++;
		draw_L1();
	}
	void draw_L1();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
class L2:public Graph{
private:
	int num;
	int rotate_state;
	static int total_num;
public:
	L2(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m, n+1);
		cube[2].setxy(m, n+2);
		cube[3].setxy(m-1, n+2);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Cube::total_num++;
		draw_L2();
	}
	void draw_L2();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
class Solid:public Graph{
private:
	int num;
	static int total_num;
public:
	Solid(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m, n+1);
		cube[2].setxy(m+1, n);
		cube[3].setxy(m+1, n+1);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		num = ++total_num;
		Solid::total_num++;
		draw_solid();
	}
	void draw_solid();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate(){return 0;}
	int counterclockwise_rotate(){return 0;}
};
class Rope:public Graph{
private:
	int num;
	int rotate_state;
	static int total_num;
public:
	Rope(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m, n+1);
		cube[2].setxy(m, n+2);
		cube[3].setxy(m, n+3);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Rope::total_num++;
		draw_rope();
	}
	void draw_rope();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
class Tu:public Graph{
private:
	int num;
	int rotate_state;
	static int total_num;
public:
	Tu(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m, n+1);
		cube[2].setxy(m-1, n+1);
		cube[3].setxy(m+1, n+1);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Tu::total_num++;
		void draw_tu();
	}
	void draw_tu();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
class Zhe1:public Graph{
private:
	int rotate_state;
	int num;
	static int total_num;
public:
	Zhe1(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m+1, n);
		cube[2].setxy(m+1, n+1);
		cube[3].setxy(m+2, n+1);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Zhe1::total_num++;
		draw_zhe1();
	}
	void draw_zhe1();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
class Zhe2:public Graph{
private:
	int rotate_state;
	int num;
	static int total_num;
public:
	Zhe2(int m, int n){
		cube[0].setxy(m, n);
		cube[1].setxy(m-1, n);
		cube[2].setxy(m-1, n+1);
		cube[3].setxy(m-2, n+1);
		if (have_color == 1){
			cube[rand() %4].set_color(rand() %5);
		}
		rotate_state = 0;
		num = ++total_num;
		Zhe2::total_num++;
		draw_zhe2();
	}
	void draw_zhe2();
	int move_down();
	int move_left();
	int move_right();
	int clockwise_rotate();
	int counterclockwise_rotate();
};
//类声明完毕
void draw_cube(int x, int y){   
	fillrectangle(2+12*x, 2+12*y, 2+12*x+10, 2+12*y+10);
	game.cube_exist[x][y] = 1;
	game.cube_color[x][y] = 0;
}
void draw_cube(int x, int y, int color){
	switch (color){
	case 1: 
		setfillcolor(RED);
		setcolor(RED);
		break;
	case 2: 
		setfillcolor(YELLOW);
		setcolor(YELLOW);
		break;
	case 3:
		setfillcolor(GREEN);
		setcolor(GREEN);
		break;
	case 4:
		setfillcolor(BLUE);
		setcolor(BLUE);
		break;
	}
	fillrectangle(2+12*x, 2+12*y, 2+12*x+10, 2+12*y+10);
	game.cube_exist[x][y] = 1;
	game.cube_color[x][y] = color;
	setfillcolor(WHITE);
	setcolor(WHITE);
}
void delete_cube(int x, int y){
	clearrectangle(2+x*12, 2+y*12, 12+x*12, 12+y*12);
	game.cube_exist[x][y] = 0;
	game.cube_color[x][y] = 0;
}
Game::Game(){
	for (int i = 0; i <= 19; i++){
		for (int j = 0; j <= 39; j++){
			cube_exist[i][j] = 0;
			cube_color[i][j] = 0;
		}
	}
}
void Game::create_cube(int x, int y){
	draw_cube(x, y);
	cube_exist[x][y] = 1;
}
void Game::delete_line(int y){    // 清除第y行
	for (int i = 0; i <= 19; i++){
		delete_cube(i, y);
	}
	Sleep(300);
	for (int i = 0; i <= 19; i++){
		for (int j = y; j >= 0; j--){
			if (cube_exist[i][j] == 1){
				if (cube_color[i][j] != 0){
				   draw_cube(i, j+1, cube_color[i][j]);
				}
				else draw_cube(i, j+1);
				delete_cube(i, j);
			}
		}
	}                                 // 颜色奖励部分
	if (red >= 3){					  // 加三十分
		score += 30;
		red = 0;
	}
	if (yellow >= 3){				  // 额外消去一行
		yellow = 0;
		game.delete_line(y);
	}
	if (green >= 3){				  // 下落速度减缓
		time_bonus++;           
		green = 0;
	}
	if (blue >= 3){					  // 颜色出现概率增加
		n += 2;
		blue = 0;
	}
	score += 10;
}
int Game::check_line(){
	for (int i = 39; i >= 0; i--){
		int flag = 1;
		for (int j = 0; j <= 19; j++){
			flag *= cube_exist[j][i];
		}
		if (flag != 0){ 
			check_color(i);
			return i;
		}
	}
	return -1;
}
void Game::check_color(int y){
	for (int i = 0; i <= 19; i++){
		switch (cube_color[i][y]){
		case 1:
			red++;
			break;
		case 2:
			yellow++;
			break;
		case 3:
			green++;
			break;
		case 4:
			blue++;
			break;
		}
	}
}
void L1::draw_L1(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int L1::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int L1::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int L1::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int L1::clockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2;
		cube[1].x += 1, cube[1].y -= 1;
		cube[2].y -= 2;
		cube[3].x -= 1; cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1; cube[0].y += 2;
		cube[1].y += 1;
		cube[2].x += 1;
		cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2, cube[0].y -= 1;
		cube[1].x -= 1;
		cube[2].y += 1;
		cube[3].x += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 4) rotate_state = 0;
	return 1;
}
int L1::counterclockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2;
		cube[1].x -= 1, cube[1].y += 1;
		cube[2].y += 2;
		cube[3].x += 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1; cube[0].y -= 2;
		cube[1].y -= 1;
		cube[2].x -= 1;
		cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2, cube[0].y += 1;
		cube[1].x += 1;
		cube[2].y -= 1;
		cube[3].x -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state--;
	if (rotate_state == -1) rotate_state = 3;
	return 1;
}
void L2::draw_L2(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int L2::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int L2::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int L2::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int L2::clockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2;
		cube[1].x += 1, cube[1].y -= 1;
		cube[2].y -= 2;
		cube[3].x += 1; cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1; cube[0].y += 2;
		cube[1].y += 1;
		cube[2].x += 1;
		cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2, cube[0].y -= 1;
		cube[1].x -= 1;
		cube[2].y += 1;
		cube[3].x -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 4) rotate_state = 0;
	return 1;
}
int L2::counterclockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2;
		cube[1].x -= 1, cube[1].y += 1;
		cube[2].y += 2;
		cube[3].x -= 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1; cube[0].y -= 2;
		cube[1].y -= 1;
		cube[2].x -= 1;
		cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2, cube[0].y += 1;
		cube[1].x += 1;
		cube[2].y -= 1;
		cube[3].x += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state--;
	if (rotate_state == -1) rotate_state = 3;
	return 1;
}
void Solid::draw_solid(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int Solid::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int Solid::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int Solid::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
void Rope::draw_rope(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int Rope::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int Rope::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int Rope::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int Rope::clockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].x += 2, cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].x -= 2, cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
int Rope::counterclockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].x += 2, cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].x -= 2, cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
void Tu::draw_tu(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int Tu::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int Tu::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int Tu::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int Tu::clockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1; cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].x -= 1; cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1; cube[0].y += 1;
		cube[2].x += 1, cube[2].y += 1;
		cube[3].x -= 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].x += 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y -= 1;
		cube[3].x += 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 4) rotate_state = 0;
	return 1;
}
int Tu::counterclockwise_rotate(){
	switch (rotate_state){
	case 0:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1; cube[0].y += 1;
		cube[2].x += 1, cube[2].y += 1;
		cube[3].x -= 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 1, cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y += 1;
		cube[3].x += 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 2:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1; cube[0].y -= 1;
		cube[2].x -= 1, cube[2].y -= 1;
		cube[3].x += 1; cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 3:
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 1, cube[0].y += 1;
		cube[2].x += 1, cube[2].y -= 1;
		cube[3].x -= 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state--;
	if (rotate_state == -1) rotate_state = 3;
	return 1;
}
void Zhe1::draw_zhe1(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int Zhe1::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int Zhe1::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int Zhe1::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int Zhe1::clockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2;
		cube[1].x += 1, cube[1].y += 1;
		cube[3].x -= 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2;
		cube[1].x -= 1, cube[1].y -= 1;
		cube[3].x += 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
int Zhe1::counterclockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x += 2;
		cube[1].x += 1, cube[1].y += 1;
		cube[3].x -= 1, cube[3].y += 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].x -= 2;
		cube[1].x -= 1, cube[1].y -= 1;
		cube[3].x += 1, cube[3].y -= 1;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
void Zhe2::draw_zhe2(){
	draw_cube(cube[0].x, cube[0].y);
	draw_cube(cube[1].x, cube[1].y);
	draw_cube(cube[2].x, cube[2].y);
	draw_cube(cube[3].x, cube[3].y);
}
int Zhe2::move_down(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x == cube[j].x && cube[i].y+1 == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x][cube[i].y+1] == 1 && flag != 0) || cube[i].y+1 > 39){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		if (cube[i].color != 0){
			draw_cube(cube[i].x, cube[i].y+1, cube[i].color);
		}
		else draw_cube(cube[i].x, cube[i].y+1);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].y++;
	}
	return 1;
}
int Zhe2::move_left(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x-1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x-1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x-1 < 0){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x-1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x--;
	}
	return 1;
}
int Zhe2::move_right(){
	for (int i = 0; i <= 3; i++){
		int flag = 1;
		for (int j = 0; j <= 3; j++){
			flag *= !(cube[i].x+1 == cube[j].x && cube[i].y == cube[j].y && j != i);
		}
		if ((game.cube_exist[cube[i].x+1][cube[i].y] == 1 && flag != 0) || cube[i].y+1 > 39 || cube[i].x+1 > 19){
			return 0;
		}
	}
	for (int i = 0; i <= 3; i++){
		delete_cube(cube[i].x, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		draw_cube(cube[i].x+1, cube[i].y);
	}
	for (int i = 0; i <= 3; i++){
		cube[i].x++;
	}
	return 1;
}
int Zhe2::clockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].y += 1;
		cube[1].x += 1;
		cube[2].y -= 1;
		cube[3].x += 1, cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].y -= 1;
		cube[1].x -= 1;
		cube[2].y += 1;
		cube[3].x -= 1, cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
int Zhe2::counterclockwise_rotate(){
	switch (rotate_state){
	case 0: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].y += 1;
		cube[1].x += 1;
		cube[2].y -= 1;
		cube[3].x += 1, cube[3].y -= 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	case 1: 
		for (int i = 0; i <= 3; i++){
			delete_cube(cube[i].x,cube[i].y);
		}
		cube[0].y -= 1;
		cube[1].x -= 1;
		cube[2].y += 1;
		cube[3].x -= 1, cube[3].y += 2;
		for (int i = 0; i <= 3; i++){
			draw_cube(cube[i].x,cube[i].y);
		}
		judge_beyond(this);
		break;
	}
	rotate_state++;
	if (rotate_state == 2) rotate_state = 0;
	return 1;
}
int L1::total_num = 0;
int L2::total_num = 0;
int Solid::total_num = 0;
int Rope::total_num = 0;
int Tu::total_num = 0;
int Zhe1::total_num = 0;
int Zhe2::total_num = 0;
void judge_beyond(Graph *p){
	int beyond = 0;
	while (beyond == 0){
		int beyond_left = 1, beyond_right = 1;
		for (int i = 0; i <= 3; i++){
			beyond_right *= !(p->cube[i].x-19 > 0);
			beyond_left *= !(p->cube[i].x < 0);
		}
		if (beyond_right == 0) {p->move_left(), beyond = 0;}
		else if (beyond_left == 0) {p->move_right(), beyond = 0;}
		else beyond = 1;
	}
	line(243, 0, 243, 481);
}