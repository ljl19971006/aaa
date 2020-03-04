#include "pch.h"
#include "BodyManager.h"
#include "Body.h"
#include <algorithm>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
bool BodyManager::addBody(Body &body) {
	if (fitBody(body, body.position)) {
		bodies.push_back(&body);
		body.bodyManager = this;
		return true;
	} else return false;
}

bool BodyManager::moveBody(Body &body, const Position &position, Body **collidingBody) {
	//if (find(bodies.begin(), bodies.end(), &body) == bodies.end())
	//{
	//	return false;
	//} //body not found
	if (fitBody(body, position, collidingBody)) {
		body.position = position;
		return true;
	}
	else {
		//return false;
		return true;
	}
}

bool BodyManager::fitBody(Body &body, const Position &position, Body **collidingBody) {
	int i_coll=0;
	if ((position.x + body.box.width > worldBox.width) || (position.y + body.box.height > worldBox.height)) {
		return false; //doesn't fit in the world
	}
	//for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		//if ((*it) == &body) continue; //do not check with itself
		//if (collide(**it, body.box, position)) {
			//cerr << "collision between body " << (*it)->name << " and body " << body.name;
			//if (collidingBody) *collidingBody = *it;
	int *s=new int;
	if (position.x==0 || position.x + body.box.width == worldBox.width) { *s = 1; changeAngle(body, s); }
	//判断是否与左右两边的墙壁碰撞
	if (position.y==0 ) { *s = 2; changeAngle(body, s); }
	//判断是否与上边的墙壁碰撞
	for (auto it : bodies) {
		if ((it) == &body) continue; //do not check with itself
		
		if (collide(*it, body.box, position,s,body)) {//主要为球与砖块的碰撞
			//cerr << "collision between body " << (*it)->name << " and body " << body.name;
			//console.set_pen_color(yellow);
			if (it->getName() == "aaaa") {
				if (position.x <= it->getPosition().x + 3) {
					body.setAngle(135);
				}
				else if (position.x < it->getPosition().x + 7) {
					body.setAngle(90);
				}
				else {
					body.setAngle(45);
				}

			}
			if (collidingBody) { *collidingBody = it; }
			//int p = 0;
			if (it->getName() == "bbbb"&&it->getKind() != 3) {
				//if (p == 1)
				//{
				//	system("cls");
				//}
				bodies.erase(bodies.begin() + i_coll);
				//bodies.erase(it);
				//p = 1;
				//console.set_pen_color(dark_yellow);
				//
				changeAngle(body, s);
				system("cls");
			}
			if (it->getKind() == 3) {
				int p = it->getPara();
				it->setPara(p - 1);
				if (p==0){ bodies.erase(bodies.begin() + i_coll); }
				changeAngle(body, s);
				system("cls");
			}
			

			return false;
		}
		i_coll = i_coll + 1;
	}
	
	if (collidingBody) *collidingBody = nullptr;
	
	return true;
}

bool BodyManager::collide(const Body & body, const Box &box, const Position &position, int*state,const Body&b_ball) { //collision
	*state = 0;
	int st_1 = 0;
	int st_2 = 0;
	if (body.disabled) return false;
	if ((position.x + box.width <= body.position.x) || (body.position.x + body.box.width <= position.x))
	{
		return false;
	}
	else {
		if ((position.y + box.height <= body.position.y) || (body.position.y + body.box.height <= position.y))
		{
			return false;
		}
	}
	//用前一次位置的两边重合判断碰撞性质
	if ((b_ball.prevPosition.x + box.width == body.position.x) || (body.position.x + body.box.width == b_ball.prevPosition.x))
	{
		st_1 = 1;

	}
	if ((b_ball.prevPosition.y + box.height == body.position.y) || (body.position.y + body.box.height == b_ball.prevPosition.y))
	{
		st_2 = 1;

	}



	if ((st_1 == 1) && (st_2) == 0) {
		*state = 1; return true;//碰撞发生在左右侧
		
	}
	if ((st_1 == 0) && (st_2) == 1) {
		*state = 2; return true;//碰撞发生在上下侧
		
	}
	if ((st_1 == 1) && (st_2) == 1) {
		*state = 3; return true;//碰撞发生在角上
		
	}
}

void BodyManager::run() {
	//int i_color = 0;
	for (auto it = bodies.begin(); it != bodies.end(); ++it) {


		if ((*it)->getKind() == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//cyan
		}
		else if ((*it)->getKind() == 3) {
			if ((*it)->getPara() == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//grey
			}
			else if ((*it)->getPara() == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//blue
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
			}
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
		}
		(*it)->draw();
			//i_color = i_color + 1;
		getConsole().set_hide_cursor();
		//std::cout << "hhhhh" << endl;
		//while (!exit) {
		//	//getConsole().set_pen_color(white);
		//	for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		//		(*it)->update();
		//		if ((*it)->requestDraw || ((*it)->prevPosition != (*it)->position)) {
		//			(*it)->draw();
		//		}
		//	}
		//	getConsole().set_hide_cursor();
		//	Sleep(10); //relax cpu (should use a periodic timer set with CreateTimerQueueTimer instead, but too complex for this project)
		//}
		//void moveban(Body&body, BodyManager&b, Console&console);
		if ((*it)->getKind() == 2) {
			Sleep(1);
		}
		else { Sleep(2); }
	}
}

void BodyManager::changeAngle(Body&Body,int *state) {//球的运动方向的改变
	float atemp;
	if (*state == 1) {
		atemp = Body.getAngle();
		if (atemp < 0){Body.setAngle(-180-atemp);}
		else{ Body.setAngle(180 - atemp); }
	}
	if (*state == 2) {
		atemp = Body.getAngle();
		Body.setAngle(-atemp);
	}
	if (*state == 3) {
		atemp = Body.getAngle();
		if (atemp < 0){Body.setAngle(180 + atemp);}
		else{ Body.setAngle(atemp-180); }
	}
	
}

Position BodyManager::replacePosition(Body&body) {
	int x, y;
	x = unsigned short(body.position.x + 1*cos(body.angle * 3.1416 / 180)+0.5);
	y = unsigned short(body.position.y - 1*sin(body.angle * 3.1416 / 180)+0.5);//坐标相反
	body.prevPosition = body.position;
	Position posi(x, y);
	return posi;
}

Position BodyManager::rightchange(Body& body) {
	int x, y;
	x = unsigned short(body.position.x + 3);
	y = unsigned short(body.position.y);
	body.prevPosition = body.position;
	Position Pos(x, y);
	return Pos;
}

Position BodyManager::leftchange(Body&body) {
	int x, y;
	x = unsigned short(body.position.x - 3);
	y = unsigned short(body.position.y);
	body.prevPosition = body.position;
	Position Pos(x, y);
	return Pos;
}

Position BodyManager::moveban(Body&body, int ch)
{
	Position npos = body.getPosition();
	//if (!_kbhit()) return npos;
	//if (_kbhit())       //用该函数判断你是否按下某个键，按下返回1，否则返回0
	//{
	//int c = _getch();
	switch (ch)
	{
	case 75:
	case 'A':
	case 'a':
		npos.x = npos.x - 5;
		//console.clear();
		break;
	case 77:
	case 'D':
	case 'd':
		npos.x = npos.x + 5;

		break;
	}
	//}
	if (npos.x >= 60000)
	{
		npos.x = 0;
	}

	if (npos.x >= 30)
	{
		npos.x = 30;
	}

	return npos;
}


