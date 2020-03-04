#ifndef _BODY_MANAGER
#define _BODY_MANAGER

#include "pch.h"
#include <vector>
#include <string>
#include "Console.h"
class Body;

using namespace std;

struct Box {
	Box(unsigned short width, unsigned short height):width(width),height(height){}
	unsigned short width;
	unsigned short height;
};

struct Position {
	Position(unsigned short x, unsigned short y):x(x),y(y) {}
	unsigned short x;
	unsigned short y;
	bool operator!=(const Position &position) { return (x != position.x) || (y != position.y); }
};

class BodyManager {
public:
	Position moveban(Body&body, int ch);
	BodyManager(const Box &worldBox, Console &console) :exit(false), worldBox(worldBox), console(console) {};
	bool addBody(Body &Body);
	//move body. Return false if not possible (collision)
	bool moveBody(Body &body, const Position &position, Body **collidingBody = nullptr);
	//check if the body could fit in the given position. Return false if not (collision)
	bool fitBody(Body &body, const Position &position, Body **collidingBody = nullptr);
	void changeAngle(Body&Body, int *state);
	Position replacePosition(Body&body);
	void run();
	Position rightchange(Body&body);
	Position leftchange(Body&body);
	//Position moveban(Body&body,int ch);
	inline Console &getConsole() { return console; };
private:
	inline void quit() { exit = true; };

private:
	bool collide(const Body &body1, const Box &box, const Position &position, int*state, const Body&b_ball);
	vector<Body *> bodies;
	Box worldBox;
	Console &console;
	bool exit;
};

#endif // !_BODY_MANAGER

