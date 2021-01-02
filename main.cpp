#include<iostream>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <ctime>

using namespace std;
int runTime=500;
void set() {
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
	RECT rc;
	GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形

	//改变cmd窗口风格
	SetWindowLongPtr(hWnd,
	                 GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
	SetWindowPos(hWnd,
	             HWND_TOPMOST,
	             150,
	             150,
	             rc.right - rc.left, rc.bottom - rc.top,
	             SWP_NOMOVE | SWP_NOSIZE);
}
int main() {
	HWND hWnd = GetConsoleWindow();
	system("mode con cols=19 lines=2");
	system("title Clockly");
	system("color 0f");
	set();
	int cd=200;
	int nowsecond=0;
	while(1) {
		time_t tt = time(0);
		char tmp[64];
		strftime(tmp,sizeof(tmp),"%Y/%m/%d ",localtime(&tt));
		cd--;
		int nowtime=time(0);
		int seconds=nowtime;
		int minutes=seconds/60;
		int hours=minutes/60;
		int days=hours/24;
		int months=days/30;
		int year=1970+days/365;
		int second=seconds-minutes*60;
		int minute=minutes-hours*60;
		int hour=hours-days*24+8;
		int month=(months-days/365*12)/2;
		int day=days-months*30-12; 
		if(runTime==500) {
			while(year<1970) {
				int q=MessageBox(hWnd,"Your computer time is incorrect. Continue?","Cot Clockly",MB_ABORTRETRYIGNORE);
				if(q==3) {
					return 0;
				} else if(q==4) {
					continue;
				} else if(q==5) {
					runTime--;
					break;
				}
			}
		}
		if(year<1970) runTime--;
		if(nowsecond!=time(0)) {
			system("cls");
			cout<<"   Computer Time"<<endl;
			cout<<tmp;
			if(hour<10) {
				cout<<"0"<<hour<<":";
			} else {
				cout<<hour<<":";
			}
			if(minute<10) {
				cout<<"0"<<minute<<":";
			} else {
				cout<<minute<<":";
			}
			if(second<10) {
				cout<<"0"<<second;
			} else {
				cout<<second;
			}
			nowsecond=time(0);
		}
		if(runTime<10) {
			system("cls");
			cout<<"   ???????? Time"<<endl<<"????/??/??/ ??:??:??";
			MessageBox(hWnd,"Unknown error!","Cot Clockly",MB_ICONERROR);
			return 0;
		}
		system("title Clockly");
		Sleep(20);

	}
	return 0;
}
