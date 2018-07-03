#include <graphics.h>
#include <ctime>
#include <iostream>
using namespace std;
void main(){
	srand(clock());
	while (true){
	cout << rand() %5 << endl;
	Sleep(1000);
	}
}