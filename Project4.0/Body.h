#ifndef _BODY
#define _BODY

#include "BodyManager.h"  // car utilisation de Box
#include <string>
using namespace std;

//class BodyManager;
struct Box;
struct Position;

class Body {
	friend class BodyManager;
public:
	Body(const string &name, const Box &box, const Position &position, const string &pix,const float angle) :name(name), box(box), prevPosition(position), position(position),
		pix(pix), disabled(false), requestDraw(false), bodyManager(nullptr) ,angle(angle){
		//if (pix.size() != box.height*box.width) throw runtime_error("pix string size must fit box size");
	}
	Body(const string &name, const Box &box, const Position &position, const string &pix, const float angle, unsigned int k, unsigned int p) :name(name), box(box), prevPosition(position), position(position),
		pix(pix), disabled(false), requestDraw(false), bodyManager(nullptr), angle(angle), kind(k), para(p) {}
	virtual void update() {};
	void draw();
	bool disabled; //disabled bodies are not checked for collisions
	bool requestDraw; //force drawing at next tick
	inline const string &getName() const { return name; };
	inline const Position &getPosition() const { return position; };
	inline Position &getPosition() { return position; };
	/////Position &replacePosition(float angle, Position &position);
	void setAngle(float a) { angle = a; }
	void setPosition(Position p) { position = p; }
	float getAngle() { return angle; }
	const Box &getBox() const { return box; };
	unsigned int getKind() { return kind; }
	unsigned int getPara() { return para; }
	void setPara(unsigned int p) { para = p; }
protected:
	float angle;
	const string name;
	Box box;
	Position prevPosition;
	Position position;
	string pix;
	unsigned int kind;
	unsigned int para;

	BodyManager *bodyManager; //set when the body is added by a bodyManager
};



#endif //_BODY
