#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "comun.h"
#include "board.h"

using namespace std;

//variables externas
int y;
int x;
int main_tabla[ALTURA][ANCHO]; //X, Y
int main_cpy[ALTURA][ANCHO];
int mblock[4][4];

int main() {

	Board m;

	//inicia las coordendas
	x = 4;
	y = 0;

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = m.POS_FREE;
		}
	}

	//Start
	cout << "==================\n"
                "Press 1: Start Game\n"
                "==================\n";

	int select_num = 0;
	cin >> select_num;

	switch (select_num) {
	case 1:
		m.limpiar_screen();
		m.iniciar_draw_main();


		m.start();
		break;
	default:
		exit(0);
		break;
	}
}
