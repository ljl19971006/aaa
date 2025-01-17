// projet.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Console.h"
#include"Body.h"
#include"BodyManager.h"
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//#include<graphics.h>

using namespace std;
int main()
{
	bool state_match;

	SetConsoleOutputCP(437);
	char pix[4] = {0xda,0xbf,0xc0,0xd9};
	string pix1 = pix;
	char PX[10] = { 0xda,0xc4,0xc4,0xc4,0xbf,
					   0xc0,0xc4,0xc4,0xc4,0xd9 };
	string Pix1 = PX;
	string name1 = "aaaa";
	string name2 = "bbbb";


	Console console;//控制窗口
	console.set_title(_T("Brique!"));//程序名字
	console.set_dimensions(40, 30);//空间大小
	Box Brique(5, 2);//砖头大小
	Box box(2, 2);//设置ball大小
	Box worldbox(40, 30);//
	Box baque(10, 2);//木板大小
	char pi[20] = { 0xda,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xbf,
		0xc0,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xc4,0xd9
	};
	string pix2 = pi;
	Position position1(0, 1);//位置
	Position position2(5, 1);
	Position position3(10, 1);
	Position position4(15, 1);
	Position position5(20, 1);
	Position position6(25, 1);
	Position position7(30, 1);
	Position position8(35, 1);
	Position position9(0, 3);
	Position position10(5, 3);
	Position position11(10, 3);
	Position position12(15, 3);
	Position position13(20, 3);
	Position position14(25, 3);
	Position position15(30, 3);
	Position position16(35, 3);
	Position positionball(15, 15);
	Position positionban(15, 25);
	Body LESbriques(name2, Brique, position1, Pix1,0);//砖头类
	Body LESbriques2(name2, Brique, position2, Pix1,0);
	Body LESbriques3(name2, Brique, position3, Pix1,0);
	Body LESbriques4(name2, Brique, position4, Pix1,0);
	Body LESbriques5(name2, Brique, position5, Pix1,0);
	Body LESbriques6(name2, Brique, position6, Pix1,0);
	Body LESbriques7(name2, Brique, position7, Pix1,0);
	Body LESbriques8(name2, Brique, position8, Pix1,0);
	Body LESbriques9(name2, Brique, position9, Pix1,0);
	Body LESbriques10(name2, Brique, position10, Pix1,0);
	Body LESbriques11(name2, Brique, position11, Pix1, 0, 3, 2);
	Body LESbriques12(name2, Brique, position12, Pix1,0);
	Body LESbriques13(name2, Brique, position13, Pix1, 0, 2, 0);
	Body LESbriques14(name2, Brique, position14, Pix1, 0, 3, 2);
	Body LESbriques15(name2, Brique, position15, Pix1, 0, 3, 2);
	Body LESbriques16(name2, Brique, position16, Pix1,0);
	Body ball(name1, box, positionball, pix1,45);//球
	Body board(name1, baque, positionban, pix2,180);//木板

	BodyManager b(worldbox,console);
	console.set_hide_cursor();//隐藏光标
	//console.set_pen_color(green);//变绿
	b.addBody(LESbriques);//添加模块进manager类
	b.addBody(LESbriques2);
	b.addBody(LESbriques3);
	b.addBody(LESbriques4);
	b.addBody(LESbriques5);
	b.addBody(LESbriques6);
	b.addBody(LESbriques7);
	b.addBody(LESbriques8);
	b.addBody(LESbriques9);
	b.addBody(LESbriques10);
	b.addBody(LESbriques11);
	b.addBody(LESbriques12);
	b.addBody(LESbriques13);
	b.addBody(LESbriques14);
	b.addBody(LESbriques15);
	b.addBody(LESbriques16);
	b.addBody(ball);
	b.addBody(board);


	int game_state = 1;
	//--游戏开始
	console.set_pen_color(yellow);
	console.set_cursor_position(10, 10);
	cout << "Welcome to our game!" << endl;
	console.set_cursor_position(8, 15);
	cout << "Press enter to continue~" << endl;
	int x = _getch();
	console.clear();
	int t = 0;
	while (game_state == 1) {
		b.run();//显示出来
			//如果游戏没有结束
			//--计算下一步坐标
		Position pos_temp(0, 0);//初始化pos_temp（临时地址）
		pos_temp = b.replacePosition(ball);//计算下一步的位置
		Body *c = nullptr;//初始化指向Body的指针
		state_match = b.moveBody(ball, pos_temp, &c);//如果可以移动到临时地址，则移动球；不可以的话改变球的运动方向，并且把撞到的砖块地址赋给c
		if (state_match == 0) {
			cout << "Have been broken" << endl;
			break;
			//未找到球，游戏结束
		}
		if (ball.getPosition().y == 27) { 
			console.clear();
			console.set_cursor_position(14, 10);
			cout << "Game over!" << endl;
			console.set_cursor_position(10, 12);
		
			break;
		}
			
		if(_kbhit()) {//如果键盘有反应，则移动板
			int ch=_getch();//获取键盘事件
			Position boardPosition(0, 0);//初始化boardPosition
			boardPosition = b.moveban(board,ch);//将板将要移动的位置计算出来
			board.setPosition(boardPosition);//赋值
		}
		
	}
	
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
