#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"GL.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#pragma comment (lib,"glaux.lib")

//output into display
void Display(void) {
	glClearColor(1.0, 1.0, 1.0, 1);
	glColor3ub(255, 255, 255);
	glClear(GL_COLOR_BUFFER_BIT);
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3d(0, 0, -0.1);
		glTexCoord2d(0, 1); glVertex3d(0, Width, -0.1);
		glTexCoord2d(1, 1); glVertex3d(Height, Width, -0.1);
		glTexCoord2d(1, 0); glVertex3d(Height, 0, -0.1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glPointSize(6);
	glEnable(GL_POINT_SMOOTH);
	// тип примитива - незамкнутая линия
	for (int i = 0; i < v.size(); i++)
	{
		if (i == active)
		{
			glLineWidth(5.0);
		}
		else
		{
			glLineWidth(lineTypeVec[i].width);
		}
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, lineTypeVec[i].type);		
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < v[i].coordinates.size(); j++) {
			glColor3ub(v[i].coordinates[j].red, v[i].coordinates[j].green, v[i].coordinates[j].blue);
			glVertex2i(v[i].coordinates[j].x, v[i].coordinates[j].y);
		}
		glEnd();
	}
	if (fog) {
		switch (_fog) {
		case 1: {
			// Установим цвет мира таким же, как цвет тумана:
			//glClearColor(0.5, 0.5, 0.5, 1);
			glEnable(GL_FOG);
			//glFogfv(GL_FOG_COLOR, fogcolor);
			glFogi(GL_FOG_MODE, GL_EXP);
			glFogfv(GL_FOG_COLOR, fogcolor);
			glFogf(GL_FOG_DENSITY, -1.0f);
			//glHint(GL_FOG_HINT, GL_DONT_CARE);
			//glEnable(GL_FOG);
			break;
		}
		case 2: {
			// Установим цвет мира таким же, как цвет тумана:
			//glClearColor(0, 0, 1, 1);
			glEnable(GL_FOG);
			glFogi(GL_FOG_MODE, GL_EXP2);
			glFogfv(GL_FOG_COLOR, fogcolor);
			glFogf(GL_FOG_DENSITY, 0.5f);
			//glHint(GL_FOG_HINT, GL_DONT_CARE);
			glFogf(GL_FOG_START, 1.0f); // Глубина, с которой начинается туман 
			glFogf(GL_FOG_END, 5.0f); // Глубина, где туман заканчивается.
			//glEnable(GL_FOG);
			break;
		}
		case 3: {
			// Установим цвет мира таким же, как цвет тумана:
			//glClearColor(0, 0, 1, 1);
			glEnable(GL_FOG);
			glFogi(GL_FOG_MODE, GL_LINEAR);
			glFogfv(GL_FOG_COLOR, fogcolor);
			glFogf(GL_FOG_DENSITY, 1.0f);
			glFogf(GL_FOG_START, 1.0f); // Глубина, с которой начинается туман 
			glFogf(GL_FOG_END, 5.0f); // Глубина, где туман заканчивается.
			//glHint(GL_FOG_HINT, GL_DONT_CARE);
			//glEnable(GL_FOG);
			break;
		}
		}
	}
	glFinish();
}

//changing the size of window
void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

//перемещение примитива вверх
void MoveUp() {
	for (int j = 0; j < v[active].coordinates.size(); j++)
		v[active].coordinates[j].y += 5;
}

//перемещение примитива вниз
void MoveDown() {
	for (int j = 0; j < v[active].coordinates.size(); j++)
		v[active].coordinates[j].y -= 5;
}

//перемещение примитива влево
void MoveLeft() {
	for (int j = 0; j < v[active].coordinates.size(); j++)
		v[active].coordinates[j].x -= 5;
}

//перемещение примитива вправо
void MoveRight() {
	for (int j = 0; j < v[active].coordinates.size(); j++)
		v[active].coordinates[j].x += 5;
}

//уменьшаем толщну линии
void Make_Width_Less() {
	if (lineTypeVec[active].width - 0.5 > 0)
		lineTypeVec[active].width -= 0.5;
}

//увеличиваем толщину линии
void Make_Width_More() {
	if (lineTypeVec[active].width + 0.5 < 4.0)
		lineTypeVec[active].width += 0.5;
}

//сплошная линия
void Solid_Line(){
	lineTypeVec[active].type = 0xFFFF;

}

//точечная линия
void Dot_Line(){
	lineTypeVec[active].type = 0x0101;
}

//пунктирная лиииния
void Dash_Line() {
	lineTypeVec[active].type = 0x00F0;
}

//точечно-пунктирная линия
void Dotdash_Line() {
	lineTypeVec[active].type = 0x1C47;
}

//удаление примитива
void Delete_Last_Primitive() {
	if (active == v.size() - 1)
		active--;
	v.pop_back();
}

//удаление последней точки в примитиве
void Delete_Last_Point() {
	v[active].coordinates.pop_back();
}

//вычисление центра масс
void Calc_Center_Mass() {
	int i = 0;
	for (; i < v[active].coordinates.size(); i++) {
		center_mass.x += v[active].coordinates[i].x;
		center_mass.y += v[active].coordinates[i].y;
	}
	center_mass.x /= i;
	center_mass.y /= i;
}

//вращение фигуры вокруг центра масс
void Rotation_of_figure(float angle) {
	Calc_Center_Mass();
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	double x_, y_;
	double dist = sqrt(pow(center_mass.x, 2) + pow(center_mass.y, 2));
	for (int i = 0; i < v[active].coordinates.size(); i++) {
		x_ = v[active].coordinates[i].x;
		y_ = v[active].coordinates[i].y;

		v[active].coordinates[i].x = center_mass.x + (x_ - center_mass.x) * cos_ - (y_ - center_mass.y) * sin_;
		v[active].coordinates[i].y = center_mass.y + (x_ - center_mass.x) * sin_ + (y_ - center_mass.y) * cos_;
	}
}

//processing the message from keyboard
void Keyboard_normal(unsigned char key, int x, int y) {
	GLint max = 0, min = 255;

	//changing color of points
	if (key == 'r') 
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (max < v[active].coordinates[i].red)
				max = v[active].coordinates[i].red;
		}
		if (max + 5 < 255)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].red += 5;
	}
	if (key == 'g')
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (max < v[active].coordinates[i].green)
				max = v[active].coordinates[i].green;
		}
		if (max + 5 < 255)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].green += 5;
	} 
	if (key == 'b') 
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (max < v[active].coordinates[i].blue)
				max = v[active].coordinates[i].blue;
		}
		if (max + 5 < 255)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].blue += 5;
	}
	if (key == 't')
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (min > v[active].coordinates[i].red)
				min = v[active].coordinates[i].red;
		}
		if (min - 5 > 0)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].red -= 5;
	}
	if (key == 'h') 
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (min > v[active].coordinates[i].green)
				min = v[active].coordinates[i].green;
		}
		if (min - 5 > 0)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].green -= 5;
	}
	if (key == 'n') 
	{
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			if (min > v[active].coordinates[i].blue)
				min = v[active].coordinates[i].blue;
		}
		if (min - 5 > 0)
			for (int i = 0; i < v[active].coordinates.size(); i++)
				v[active].coordinates[i].blue -= 5;
	}

	//changing the width of line
	if (key == 'x')		Make_Width_Less();
	if (key == 'c')		Make_Width_More();

	//changing the type of line
	if (key == 49)		Solid_Line();
	if (key == 50)		Dot_Line();
	if (key == 51)		Dash_Line();
	if (key == 52)		Dotdash_Line();

	//changing the position of points
	if (key == 'w')		MoveUp();
	if (key == 's')		MoveDown();
	if (key == 'a')		MoveLeft();
	if (key == 'd')		MoveRight();

	//rotation the figure
	if (key == 'o') 	Rotation_of_figure(10);
	if (key == 'p') 	Rotation_of_figure(-10);
		
	//Delete Group
	if (key == 127)		Delete_Last_Primitive();

	//backspace delete last point in primitive
	if (key == 8)		Delete_Last_Point();
		

	//finish primitive
	if (key == 'z')
		k = true;

	glutPostRedisplay();
}

//клавиша стрелка вверх
void On_Up_Key() {
	//if it's not last primitive
	if (v.size() - 1 > active)		active++;
	//last primitive
	else 							active = 0;
}

//клавиша стрелка вниз
void On_Down_Key() {
	//if it's nor first primitive
	if (active != 0)		active--;
	//first primitive
	else					active = v.size() - 1;
}

//special keys for changing primitives
void Keyboard_special(int key, int x, int y)
{
		if (key == GLUT_KEY_UP)		On_Up_Key();

		if (key == GLUT_KEY_DOWN)	On_Down_Key();
	glutPostRedisplay();
}

//поиск ближайшей точки
void processChangePointMenu(point p) {
	int min_distance = 500000, distance;
	for (int j = 0; j < v[active].coordinates.size(); j++)
	{
		distance = sqrt((p.x - v[active].coordinates[j].x) * (p.x - v[active].coordinates[j].x)
			+ (p.y - v[active].coordinates[j].y) * (p.y - v[active].coordinates[j].y));
		if (distance < min_distance) {
			min_distance = distance;
			ch_point = j;
		}
	}
}

//загрузка текстур 
void LoadTextures() {
	unsigned int  sea_tex, sky_tex, space_tex;
	int w1;
	int h1;
	int comp1;
	glGenTextures(10, names);
	unsigned char* image1 = stbi_load("sea.bmp", &w1, &h1, &comp1, STBI_rgb);
	glBindTexture(GL_TEXTURE_2D, names[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w1, h1, GL_RGB, GL_UNSIGNED_BYTE, image1);

	
	unsigned char* image2 = stbi_load("sky.jpg", &w1, &h1, &comp1, STBI_rgb);
	glBindTexture(GL_TEXTURE_2D, names[1]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w1, h1, GL_RGB, GL_UNSIGNED_BYTE, image2);

	unsigned char* image3 = stbi_load("space.jpg", &w1, &h1, &comp1, STBI_rgb);
	glBindTexture(GL_TEXTURE_2D, names[2]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w1, h1, GL_RGB, GL_UNSIGNED_BYTE, image3);
}

//меню для цета точки
void Point_Color() {
	switch (change_color) {
	case RED: {
		v[active].coordinates[ch_point].red = 193;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 32;
		break; }
	case BLUE: {
		v[active].coordinates[ch_point].red = 66;
		v[active].coordinates[ch_point].green = 170;
		v[active].coordinates[ch_point].blue = 255;
		break; }
	case GREEN: {
		v[active].coordinates[ch_point].red = 0;
		v[active].coordinates[ch_point].green = 128;
		v[active].coordinates[ch_point].blue = 0;
		break;
	}
	case ORANGE: {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 165;
		v[active].coordinates[ch_point].blue = 0;
		break;
	}
	case YELLOW: {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 255;
		v[active].coordinates[ch_point].blue = 0;
		break;
	}
	case VIOLET: {
		v[active].coordinates[ch_point].red = 139;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 255;
		break;
	}
	case BLACK: {
		v[active].coordinates[ch_point].red = 0;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 0;
		break;
	}
	case PINK: {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 192;
		v[active].coordinates[ch_point].blue = 203;
		break;
	}
	}
	//glutPostRedisplay();
}

//processing the message from mouse
void Mouse(int button, int state, int x, int y) {
	//long push
	if (state != GLUT_DOWN) return;
	 
	//new point(left key)
	if (button == GLUT_LEFT_BUTTON) {
		//получить координаты точки
		point p = point((GLint)x, Height - (GLint)y,150,150,150);
		//если изменяем точку в примитиве
		if (z)
		{
			if (x12 == 0)
			{
				processChangePointMenu(p);
				x12++;
			}
			else
			{
				v[active].coordinates[ch_point].x = p.x;
				v[active].coordinates[ch_point].y = p.y;
				x12++;
			}
		}
		//добавить их в ломаную
		if (k)
		{
			active++;
			k = false;
			v.resize(v.size() + 1);
			//добавить "цвет по умолчанию" для нулевого набора
			//colors.push_back(color(150, 150, 150, active));
			//добавить "тип линии и толщину по умолчанию" для нулевого набора
			lineTypeVec.push_back(linetype(1.0, 0xFFFF, active));
		}
		if (col)
		{
			processChangePointMenu(p);
			Point_Color();
		}
		if(!z && !col)
			v[active].coordinates.push_back(p);
		if (x12 == 2 || col){
			x12 = 0;
			z = false;
			col = false;
		}
	}
	glutPostRedisplay();
}

//подменю для цветов
void processColorMenu(int option) {
	switch (option) {
	case RED: {
		for (int i = 0; i < v[active].coordinates.size(); i++){
			v[active].coordinates[i].red = 193;
			v[active].coordinates[i].green = 0;
			v[active].coordinates[i].blue = 32;
		}
		break;}
	case BLUE: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 66;
			v[active].coordinates[i].green = 170;
			v[active].coordinates[i].blue = 255;
		}
		break;}
	case GREEN: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 0;
			v[active].coordinates[i].green = 128;
			v[active].coordinates[i].blue = 0;
		}
		break;
	}
	case ORANGE: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 255;
			v[active].coordinates[i].green = 165;
			v[active].coordinates[i].blue = 0;
		}
		break;
	}
	case YELLOW: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 255;
			v[active].coordinates[i].green = 255;
			v[active].coordinates[i].blue = 0;
		}
		break;
	}
	case VIOLET: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 139;
			v[active].coordinates[i].green = 0;
			v[active].coordinates[i].blue = 255;
		}
		break;
	}
	case BLACK: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 0;
			v[active].coordinates[i].green = 0;
			v[active].coordinates[i].blue = 0;
		}
		break;
	}
	case PINK: {
		for (int i = 0; i < v[active].coordinates.size(); i++) {
			v[active].coordinates[i].red = 255;
			v[active].coordinates[i].green = 192;
			v[active].coordinates[i].blue = 203;
		}
		break;
	}
	}
	glutPostRedisplay();
}

// подменю для типов линий
void processTypeMenu(int option) {
	switch (option) {
	case SOLID: {
		Solid_Line();
		break;
	}
	case DOT: {
		Dot_Line();
		break;
	}
	case DASH: {
		Dash_Line();
		break;
	}
	case DOTDASH: {
		Dotdash_Line();
		break;
	}
	}
	glutPostRedisplay();
}

// подменю для тумана
void processFog(int option) {
	switch (option) {
	case EXP: {
		fog = true;
		_fog = 1;
		break;
	}
	case EXP2: {
		fog = true;
		_fog = 2;
		break;
	}
	case LINEAR: {
		fog = true;
		_fog = 3;
		break;
	}
	case NO: {
		fog = false;
		break;
	}
	}
	glutPostRedisplay();
}

//подменю перемещений
void processMoveMenu(int option) {
	switch (option) {
	case MOVE_UP: {
		MoveUp();
		break;
	}
	case MOVE_DOWN: {
		MoveDown();
		break;
	}
	case MOVE_LEFT: {
		MoveLeft();
		break;
	}
	case MOVE_RIGHT: {
		MoveRight();
		break;
	}
	}
	glutPostRedisplay();
}

//главное меню
void processMainMenu(int option) {
	if (option == 204)
		z = true;
	//if (option == 18)
	//	col = true;
	if (option == 1){
		v[active].coordinates[ch_point].red = 193;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 32;
		col = false;
	}
	if (option == 2){
		v[active].coordinates[ch_point].red = 66;
		v[active].coordinates[ch_point].green = 170;
		v[active].coordinates[ch_point].blue = 255;
		col = false;
	}
	if (option == 3) {
		v[active].coordinates[ch_point].red = 0;
		v[active].coordinates[ch_point].green = 128;
		v[active].coordinates[ch_point].blue = 0;
		col = false;
	}
	if (option == 4) {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 165;
		v[active].coordinates[ch_point].blue = 0;
		col = false;
	}
	if (option == 5) {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 255;
		v[active].coordinates[ch_point].blue = 0;
		col = false;
	}
	if (option == 6) {
		v[active].coordinates[ch_point].red = 139;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 255;
		col = false;
	}
	if (option == 7) {
		v[active].coordinates[ch_point].red = 0;
		v[active].coordinates[ch_point].green = 0;
		v[active].coordinates[ch_point].blue = 0;
		col = false;
	}
	if (option == 8) {
		v[active].coordinates[ch_point].red = 255;
		v[active].coordinates[ch_point].green = 192;
		v[active].coordinates[ch_point].blue = 203;
		col = false;
	}
	if (option == 84)	Delete_Last_Point();
	if (option == 56)	Delete_Last_Primitive();
	glutPostRedisplay();
}

//подменю для толщины линий
void processWidthMenu(int option) {
	switch (option) {
	case WIDTH_0_5: {
		lineTypeVec[active].width = 0.5;
		break;
	}
	case WIDTH_1: {
		lineTypeVec[active].width = 1;
		break;
	}
	case WIDTH_1_5: {
		lineTypeVec[active].width = 1.5;
		break;
	}
	case WIDTH_2: {
		lineTypeVec[active].width = 2;
		break;
	}
	case WIDTH_2_5: {
		lineTypeVec[active].width = 2.5;
		break;
	}
	case WIDTH_3: {
		lineTypeVec[active].width = 3;
		break;
	}
	case WIDTH_3_5: {
		lineTypeVec[active].width = 3.5;
		break;
	}
	case WIDTH_4: {
		lineTypeVec[active].width = 4;
		break;
	}
	}
	glutPostRedisplay();
}

//подменю для изменения цветта точки
void processChangeColorMenu(int option) {
	col = true;
	change_color = option;
}

// подменю для фона
void processBackMenu(int option) {
	switch (option) {
	case NO: {
		glBindTexture(GL_TEXTURE_2D, NULL);
		break;
	}
	case SEA: {
		glBindTexture(GL_TEXTURE_2D, names[0]);
		break;
	}
	case SKY: {
		glBindTexture(GL_TEXTURE_2D, names[1]);
		break;
	}
	case SPACE: {
		glBindTexture(GL_TEXTURE_2D, names[2]);
		break;
	}
	}
	glutPostRedisplay();
}

// подменю для фона
void processRotMenu(int option) {
	switch (option) {
	case WISE: {
		Rotation_of_figure(10);
		break;
	}
	case ANTIWISE: {
		Rotation_of_figure(-10);
		break;
	}
	}
	glutPostRedisplay();
}

//подпрограмма созданиия меню
void createMenu()
{
	int main_menu, width_menu, color_menu, type_menu, move_menu, change_back_ground, fog_menu, rot_menu;
	int change_point = 204, change_point_color = 18, delete_point = 84, delete_primitive = 56;

	//подменю фон
	change_back_ground = glutCreateMenu(processBackMenu);
	glutAddMenuEntry("No back", NO);
	glutAddMenuEntry("Sea", SEA);
	glutAddMenuEntry("Sky", SKY);
	glutAddMenuEntry("Space", SPACE);
	
	//подменю туман
	fog_menu = glutCreateMenu(processFog);
	glutAddMenuEntry("No fog", NO);
	glutAddMenuEntry("Mist", EXP);
	glutAddMenuEntry("Fog", EXP2);
	glutAddMenuEntry("Smoge", LINEAR);

	//подменю тип линии
	type_menu = glutCreateMenu(processTypeMenu);
	glutAddMenuEntry("Solid", SOLID);
	glutAddMenuEntry("Dot", DOT);
	glutAddMenuEntry("Dash", DASH);
	glutAddMenuEntry("Dotdash", DOTDASH);

	//подменю толщина линии
	width_menu = glutCreateMenu(processWidthMenu);
	glutAddMenuEntry("0.5", WIDTH_0_5);
	glutAddMenuEntry("1.0", WIDTH_1);
	glutAddMenuEntry("1.5", WIDTH_1_5);
	glutAddMenuEntry("2.0", WIDTH_2);
	glutAddMenuEntry("2.5", WIDTH_2_5);
	glutAddMenuEntry("3.0", WIDTH_3);
	glutAddMenuEntry("3.5", WIDTH_3_5);
	glutAddMenuEntry("4.0", WIDTH_4);

	//подменю цвет
	color_menu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Violet", VIOLET);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("Pink", PINK);

	//подменю перемещения
	move_menu = glutCreateMenu(processMoveMenu);
	glutAddMenuEntry("Up", MOVE_UP);
	glutAddMenuEntry("Down", MOVE_DOWN);
	glutAddMenuEntry("Left", MOVE_LEFT);
	glutAddMenuEntry("Right", MOVE_RIGHT);
		
	//подменю для вращения 
	rot_menu = glutCreateMenu(processRotMenu);
	glutAddMenuEntry("Clockwise", WISE);
	glutAddMenuEntry("Anticlockwise", ANTIWISE);

	//подменю изменения цвета точки
	change_point_color = glutCreateMenu(processChangeColorMenu);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Violet", VIOLET);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("Pink", PINK);

	//главное меню
	main_menu = glutCreateMenu(processMainMenu);
	glutAddSubMenu("Line type", type_menu);
	glutAddSubMenu("Line thickness", width_menu);
	glutAddSubMenu("Line color", color_menu);
	glutAddSubMenu("Move primitive", move_menu);
	glutAddMenuEntry("Change point in primitive", change_point);
	glutAddMenuEntry("Delete last point in primitive", delete_point);
	glutAddMenuEntry("Delete last primitive", delete_primitive);
	glutAddSubMenu("Change  color of point in primitive", change_point_color);
	glutAddSubMenu("Change  back_ground", change_back_ground);
	glutAddSubMenu("Rotation of figure", rot_menu);
	glutAddSubMenu("Add fog", fog_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//прикрепить меню к правой кнопке мыши
}

//главное меню
void main(int argc, char *argv[]) {
	//уставить начальные размеры окна
	v.resize(1);
	active = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      //один буфер отрисовки окна, использование всех компонент RGB
	glutInitWindowSize(Width, Height);

	glutCreateWindow("GL_LINE_STRIP");
	LoadTextures();
	glBindTexture(GL_TEXTURE_2D, NULL);
	//добавить "тип линии и толщину по умолчанию" для нулевого набора
	lineTypeVec.push_back(linetype(1.0, 0xFFFF, active));
	createMenu();									//создание меню
	glutKeyboardFunc(Keyboard_normal);				//обработка клавиш с кодами ascii
	glutSpecialFunc(Keyboard_special);				//обработка не-ascii клавиш
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMainLoop();
}