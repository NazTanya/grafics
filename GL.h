#include<GL\glut.h>
#include <vector>
using namespace std;

// ��������� ��� ������� ��� �����
#define SOLID           1
#define DOT             2
#define DASH            3
#define DOTDASH         4

// ��������� ��� ������� ������� �����
#define WIDTH_0_5       1
#define WIDTH_1         2
#define WIDTH_1_5       3
#define WIDTH_2         4
#define WIDTH_2_5       5
#define WIDTH_3         6
#define WIDTH_3_5       7
#define WIDTH_4         8

// ��������� ��� ������� ���� �����
#define RED     1
#define BLUE    2
#define GREEN   3
#define ORANGE  4
#define YELLOW  5
#define VIOLET  6
#define BLACK   7
#define PINK   8

//��������� ��� �����������
#define MOVE_UP		1
#define MOVE_DOWN	2
#define MOVE_LEFT	3
#define MOVE_RIGHT	4

//��������� ��� ����
#define NO		0
#define SEA		1
#define SKY		2
#define SPACE	3

//��������� ��� ����
#define NO		0
#define EXP		1
#define EXP2	2
#define LINEAR	3

//��������� ��� ��������
#define WISE		1
#define ANTIWISE	2

GLint Width = 512, Height = 512;

struct point {
	GLfloat x, y;
	GLint red, blue, green;
	point(GLint _x, GLint _y,GLint r, GLint b, GLint g) { red = r; blue = b; green = g; x = _x, y = _y;};
	point() { };
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

point center_mass;
int active;							//������� ��������
vector <line> v;					//������ �������
vector <linetype> lineTypeVec;		//������ ����� ����� ��� ��������
bool k = false;						//��� ����� �������
bool z = false;						//��� ��������� ����� � ���������
int x12 = 0;						//������� ��� ��������� �����
int ch_point;						//����� ����������
bool col = false;					//��� �������������� �����
int change_color;					//���������� ���� �� ������� ��������
unsigned int names[10];				//������ �������
bool fog;
int _fog;
float fogcolor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };