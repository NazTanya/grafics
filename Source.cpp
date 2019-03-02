#include"GL.h"
#include"glaux.h"

//output into display
void Display(void) {
	glClearColor(1.0, 1.0, 1.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
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
	glFinish();
}

//changing the size of window
void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	if (key == 'x')
		if (lineTypeVec[active].width - 0.5 > 0) lineTypeVec[active].width -= 0.5;
	if (key == 'c')
		if (lineTypeVec[active].width + 0.5 < 4.0) lineTypeVec[active].width += 0.5;

	//changing the type of line
	if (key == 49)		lineTypeVec[active].type = 0xFFFF;
	if (key == 50)		lineTypeVec[active].type = 0x0101;
	if (key == 51)		lineTypeVec[active].type = 0x00F0;
	if (key == 52)		lineTypeVec[active].type = 0x1C47;

	//changing the position of points
	if (key == 'w')		MoveUp();
	if (key == 's')		MoveDown();
	if (key == 'a')		MoveLeft();
	if (key == 'd')		MoveRight();

	//deleteDelete_Group();
	if (key == 127) {
		if (active == v.size() - 1) 
			active--;
		v.pop_back();
	}

	//backspace delete last point in primitive
	if (key == 8)
		v[active].coordinates.pop_back();

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

//
void LoadTextures() {
	unsigned int  tex;
	AUX_RGBImageRec* image;
	image = auxDIBImageLoad("image.bmp");
	//int width, height; // разрешение текстуры (ширина и высота)
	unsigned char *pixels; // массив пикселей текстуры
	//if (!LoadTextureFromFile("image.bmp", width, height,pixels)) return;
	unsigned int names[10];
	glGenTextures(10, names);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3d(-5, -5, -0.1);
	glTexCoord2d(0, 1); glVertex3d(-5, 5, -0.1);
	glTexCoord2d(1, 1); glVertex3d(5, 5, -0.1);
	glTexCoord2d(1, 0); glVertex3d(5, -5, -0.1);
	glEnd();
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
		}
		if(!z && !col)
			v[active].coordinates.push_back(p);
		if (x12 == 2){
			x12 = 0;
			z = false;
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
		lineTypeVec[active].type = 0xFFFF;
		break;
	}
	case DOT: {
		lineTypeVec[active].type = 0x0101;
		break;
	}
	case DASH: {
		lineTypeVec[active].type = 0x00F0;
		break;
	}
	case DOTDASH: {
		lineTypeVec[active].type = 0x1C47;
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
	if (option == 18)
		col = true;
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

//подпрограмма созданиия меню
void createMenu()
{
	int main_menu;
	int width_menu;
	int color_menu;
	int type_menu;
	int move_menu;
	int change_point = 204;
	int change_point_color = 18;

	//подменю тип линии
	type_menu = glutCreateMenu(processTypeMenu);
	glutAddMenuEntry("Solid", SOLID);//добавить пункты подменю
	glutAddMenuEntry("Dot", DOT);
	glutAddMenuEntry("Dash", DASH);
	glutAddMenuEntry("Dotdash", DOTDASH);

	//подменю толщина линии
	width_menu = glutCreateMenu(processWidthMenu);
	glutAddMenuEntry("0.5", WIDTH_0_5);//добавить пункты подменю
	glutAddMenuEntry("1.0", WIDTH_1);
	glutAddMenuEntry("1.5", WIDTH_1_5);
	glutAddMenuEntry("2.0", WIDTH_2);
	glutAddMenuEntry("2.5", WIDTH_2_5);
	glutAddMenuEntry("3.0", WIDTH_3);
	glutAddMenuEntry("3.5", WIDTH_3_5);
	glutAddMenuEntry("4.0", WIDTH_4);

	//подменю цвет
	color_menu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Red", RED);//добавить пункты подменю
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Violet", VIOLET);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("Pink", PINK);

	//подменю перемещения
	move_menu = glutCreateMenu(processMoveMenu);
	glutAddMenuEntry("Up", MOVE_UP);//добавить пункты подменю
	glutAddMenuEntry("Down", MOVE_DOWN);
	glutAddMenuEntry("Left", MOVE_LEFT);
	glutAddMenuEntry("Right", MOVE_RIGHT);
		
	main_menu = glutCreateMenu(processMainMenu);
	if(!col){
		//главное меню
		glutAddSubMenu("Line type", type_menu);//добавить подменю
		glutAddSubMenu("Line thickness", width_menu);
		glutAddSubMenu("Line color", color_menu);
		glutAddSubMenu("Move primitive", move_menu);
		glutAddMenuEntry("Change point in primitive", change_point);
		glutAddMenuEntry("Change  color of point in primitive", change_point_color);
	}
	else
	{
		//для поточечного изменения цвета
		glutAddMenuEntry("Red", RED);//добавить пункты подменю
		glutAddMenuEntry("Blue", BLUE);
		glutAddMenuEntry("Green", GREEN);
		glutAddMenuEntry("Orange", ORANGE);
		glutAddMenuEntry("Yellow", YELLOW);
		glutAddMenuEntry("Violet", VIOLET);
		glutAddMenuEntry("Black", BLACK);
		glutAddMenuEntry("Pink", PINK);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);//прикрепить меню к правой кнопке мыши
}

//
void main(int argc, char *argv[]) {
	//уставить начальные размеры окна
	v.resize(1);
	active = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      //один буфер отрисовки окна, использование всех компонент RGB
	glutInitWindowSize(Width, Height);
	glutCreateWindow("GL_LINE_STRIP");
	LoadTextures();
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