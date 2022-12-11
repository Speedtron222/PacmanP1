#include <iostream>
#include <conio.h>
#define MAP_VERTICAL 29
#define MAP_HORIZONTAL 120
#define PERSONAJE 'O'
enum TILES { EMPTY = ' ', WALL = '#', POINT = '.' };
TILES map[MAP_VERTICAL][MAP_HORIZONTAL];
bool run = true;
bool useColor = true; //Esta variable determina si se usan colores o no en el modulo Draw(), se modifica pulsando la tecla E y afecta significativamente al rendimiento.

enum INPUT { QUIT, UP, DOWN, LEFT, RIGHT, UNKNOWN };
INPUT currentInput = INPUT::UNKNOWN;

int personaje_x;
int personaje_y;
int puntuacion_actual = 0;
int puntuacion_total;

void Setup() {
	personaje_x = MAP_HORIZONTAL / 2;
	personaje_y = MAP_VERTICAL / 2;
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == 0 || j == 0 || i == MAP_VERTICAL - 1 || j == MAP_HORIZONTAL - 1) {
				map[i][j] = TILES::WALL;
			}
			else {
				map[i][j] = TILES::EMPTY;
			}
		}
	}

	for (int i = 2; i <= 6; i++) {
		map[MAP_VERTICAL - i][MAP_HORIZONTAL / 2 - 5] = TILES::WALL;
		map[i - 1][MAP_HORIZONTAL / 2 - 5] = TILES::WALL;
		map[MAP_VERTICAL - i][MAP_HORIZONTAL / 2 + 5] = TILES::WALL;
		map[i - 1][MAP_HORIZONTAL / 2 + 5] = TILES::WALL;
	}

	for (int i = -2; i <= 2; i++) {
		map[MAP_VERTICAL / 2 + i][MAP_HORIZONTAL / 2 - 5] = TILES::WALL;
		map[MAP_VERTICAL / 2 + i][MAP_HORIZONTAL / 2 + 5] = TILES::WALL;
		map[MAP_VERTICAL / 2 + i][0] = TILES::EMPTY;
		map[MAP_VERTICAL / 2 + i][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	}

	for (int i = -4; i <= 4; i++) {
		map[0][MAP_HORIZONTAL / 2 + i] = TILES::EMPTY;
		map[MAP_VERTICAL - 1][MAP_HORIZONTAL / 2 + i] = TILES::EMPTY;
		map[MAP_VERTICAL / 4][MAP_HORIZONTAL / 2 + i * 2] = TILES::POINT;
		map[MAP_VERTICAL - MAP_VERTICAL / 4 - 1][MAP_HORIZONTAL / 2 + i * 2] = TILES::POINT;
		map[MAP_VERTICAL / 2 + i * 2][MAP_HORIZONTAL / 2 + 4 * 2] = TILES::POINT;
		map[MAP_VERTICAL / 2 + i * 2][MAP_HORIZONTAL / 2 - 4 * 2] = TILES::POINT;
	}

	for (int i = 1; i <= 25; i++) {
		map[MAP_VERTICAL / 2][ i * 2] = TILES::POINT;
		map[MAP_VERTICAL / 2][MAP_HORIZONTAL - i * 2] = TILES::POINT;
	}

	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (map[i][j] == TILES::POINT) {
				puntuacion_total++;
			}
		}
	}
}


void Input() {
	char input = _getch();
	switch (input)
	{
	case 'w':
	case 'W':
		currentInput = INPUT::UP;
		break;
	case 's':
	case 'S':
		currentInput = INPUT::DOWN;
		break;
	case 'a':
	case 'A':
		currentInput = INPUT::LEFT;
		break;
	case 'd':
	case 'D':
		currentInput = INPUT::RIGHT;
		break;
	case 'q':
	case 'Q':
		currentInput = INPUT::QUIT;
		break;
	case 'e':
	case 'E':
		useColor = !useColor; //Input para variar el valor de useColor (decisión relativa al rendimiento)
		break;
	default:
		currentInput = INPUT::UNKNOWN;
		break;
	}
}
void Logic() {
	int personaje_y_new = personaje_y;
	int personaje_x_new = personaje_x;
	switch (currentInput)
	{
	case QUIT:
		run = false;
		break;
	case UP:
		personaje_y_new--;
		break;
	case DOWN:
		personaje_y_new++;
		break;
	case LEFT:
		personaje_x_new--;
		break;
	case RIGHT:
		personaje_x_new++;
		break;
	}

	if (personaje_x_new < 0) {
		personaje_x_new = MAP_HORIZONTAL - 1;
	}
	if (personaje_y_new < 0) {
		personaje_y_new = MAP_VERTICAL - 1;
	}
	personaje_x_new = personaje_x_new % MAP_HORIZONTAL;

	personaje_y_new = personaje_y_new % MAP_VERTICAL;

	if (puntuacion_actual == puntuacion_total) {
		run = false;
	}

	switch (map[personaje_y_new][personaje_x_new])
	{
	case TILES::WALL:
		break;
	case TILES::POINT:
		puntuacion_actual++;
		map[personaje_y_new][personaje_x_new] = TILES::EMPTY;
	default:
		personaje_y = personaje_y_new;
		personaje_x = personaje_x_new;
		break;
	}

}
void ColorPrint(char text, int fg_color, int bg_color) //Este modulo es el que se utiliza para colorear los caracteres mediante ANSI escape code, en versiones anteriores a Windows10 puede no funcionar.
{
	static const char begin_sequence[]{ 0x1B,'[','\0' };
	static const char reset[]{ 0x1B,'[','0','m','\0' };

	std::cout << begin_sequence << fg_color << ';' << bg_color << 'm' << text << reset;
}
void Draw() {
	system("CLS");
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == personaje_y && j == personaje_x) {
				if (useColor) {//Determina si el personaje se colorea o no
					ColorPrint(PERSONAJE, 33, 40);
				}
				else {
					std::cout << PERSONAJE;
				}
			}
			else {
				if (useColor) {//Determina si el escenario se colorea o no
					ColorPrint((char)map[i][j], 34, 40);
				}
				else {
					std::cout << (char)map[i][j];
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << puntuacion_actual << '/' << puntuacion_total;
}


int main()
{
	Setup();
	Draw();
	while (run) {
		Input();
		Logic();
		Draw();
	}
}




