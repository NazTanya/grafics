#include<GL\glut.h>
#include"glaux.h"
#include <vector>
using namespace std;

// константы дл€ подменю тип линии
#define SOLID           1
#define DOT             2
#define DASH            3
#define DOTDASH         4

// константы дл€ подменю толщина линии
#define WIDTH_0_5       1
#define WIDTH_1         2
#define WIDTH_1_5       3
#define WIDTH_2         4
#define WIDTH_2_5       5
#define WIDTH_3         6
#define WIDTH_3_5       7
#define WIDTH_4         8

// константы дл€ подменю цвет линии
#define RED     1
#define BLUE    2
#define GREEN   3
#define ORANGE  4
#define YELLOW  5
#define VIOLET  6
#define BLACK   7
#define PINK   8


int max_group;                  //максимальный пор€дковый номер набора (число наборов-1)

GLint Width = 512, Height = 512;

//class color
//{
//public:
//	GLint red, blue, green;
//	color(GLint r, GLint b, GLint g) { red = r; blue = b; green = g; };
//};

struct point {
	GLint x, y;
	GLint red, blue, green;
	point(GLint _x, GLint _y,GLint r, GLint b, GLint g) { red = r; blue = b; green = g; x = _x, y = _y;};
};


struct line
{
public:
	vector <point> coordinates;
};





class linetype
{
public:
	float width;
	unsigned short type;
	linetype(float _width, unsigned short _type, int _gr) { width = _width; type = _type; }; 
};

int active;							//текуща€ ломанна€
vector <line> v;					//вектор ломаных
//vector <color> colors;			//вектор цветов дл€ ломанных
vector <linetype> lineTypeVec;		//вектор типов линий дл€ ломанных
bool k = false;						//дл€ новой ломаной
bool z = false;						//дл€ изменени€ точки в примитиве
int x12 = 0;						//счетчик дл€ изменени€ точки
int ch_point;						//новые координаты
bool col = false;					//дл€ изменени€цвета точки


