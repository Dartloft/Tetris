#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Comun.h"
#include "board.h"

using namespace std;

void Board::control_input() {
	char key;
	key = getch();

	switch (key) {
	case 'd': //Derecha
		if (!chocar(x + 1, y)) {
			mover_block(x + 1, y);
		}
		break;
	case 'a': //Izquierda
		if (!chocar(x - 1, y)) {
			mover_block(x - 1, y);
		}
		break;
	case 's': //Abajo
		if (!chocar(x, y + 1)) {
			mover_block(x, y + 1);
		}
		break;
	case 'w': //Rotar
		rotar_block();
	}
}

void Board::save_cpy() {
	for (size_t i = 0; i < ALTURA - 1; i++) {
		for (size_t j = 0; j < ALTURA - 1; j++) {
			main_cpy[i][j] = main_tabla[i][j];
		}
	}
}

void Board::start() {
	size_t tiempo = 0;
	size_t TIEMPO_MAX = 20000;

	while (gameover() == false) {
		if (kbhit()) {
			control_input();
		}


		if (tiempo < TIEMPO_MAX) {
			tiempo++;
		} else {
			proceso_block();
		}
	}

	cout << "===============\n"
            "~~~Game Over~~~\n"
            "===============\n";

	exit(0);
}

void Board::limpiar_screen() {
	system("cls");
}

void Board::iniciar_draw_main() {

	for (size_t i = 0; i <= ALTURA - 2; i++) {
		for (size_t j = 0; j <= ANCHO - 2; j++) {

			if ((j == 0) || (j == ANCHO - 2) || (i == ALTURA - 2)) {
				main_tabla[i][j] = POS_BORDES;
				main_cpy[i][j] = POS_BORDES;
			} else {
				main_tabla[i][j] = POS_FREE;
				main_cpy[i][j] = POS_FREE;
			}
		}
	}

	limpiar_linea();
	new_block();
	re_draw_main();
}

void Board::re_draw_main() {
	limpiar_screen();

	for (size_t i = 0; i < ALTURA - 1; i++) {
		for (size_t j = 0; j < ANCHO - 1; j++) {
			switch (main_tabla[i][j]) {
			case POS_FREE: //Vacio
				cout << " " ;
				cout.flush();
				break;
			case POS_LLENA: //Block
				cout << "0";
				cout.flush();
				break;
			case POS_BORDES: //Bordes
				cout << "@";
				cout.flush();
				break;
			}
		}
		cout<<endl;
	}
}

int Board::getRandom(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void Board::new_block() {
	//inicializar las coordenadas.
	x = 4;
	y = 0;

	Block m;
	int blockType = getRandom(0, 6);
	int rotation = getRandom(0, 3);

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = POS_FREE;
			mblock[i][j] = m.GetBlockType(blockType, rotation, i, j);
		}
	}

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_tabla[i][x + j] = main_cpy[i][x + j] + mblock[i][j];

			if (main_tabla[i][x + j] > 1) {
				isGameOver = true;
			}
		}
	}
}

void Board::mover_block(int x2, int y2) {
	//Remueve block
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_tabla[y + i][x + j] -= mblock[i][j];
		}
	}
	//recarga las coordenadas
	x = x2;
	y = y2;

	//Asigna al block una recarga de coordenadas
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_tabla[y + i][x + j] += mblock[i][j];
		}
	}

	re_draw_main();
}
void Board::rotar_block() {

	int tmp[4][4];

	for (size_t i = 0; i < 4; i++) { //Guarda temporalmente block
		for (size_t j = 0; j < 4; j++) {
			tmp[i][j] = mblock[i][j];
		}
	}

	for (size_t i = 0; i < 4; i++) { //Rotar
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = tmp[3 - j][i];
		}
	}

	if (chocar(x, y)) {
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				mblock[i][j] = tmp[i][j];
			}
		}
	}

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_tabla[y + i][x + j] -= tmp[i][j]; //remueve despues de que cambie
			main_tabla[y + i][x + j] += mblock[i][j]; //Añade un bloque despues de la rotacion
		}
	}

	re_draw_main();
}

void Board::limpiar_linea() {

	for (int j = 0; j <= ALTURA - 3; j++) {
		int i = 1;
		while (i <= ANCHO - 3) {
			if (main_tabla[j][i] == POS_FREE) {
				break;
			}
			i++;
		}

		if (i == ANCHO - 2) {

			for (int k = j; k > 0; k--) {
				for (int idx = 1; idx <= ALTURA - 3; idx++) {
					main_tabla[k][idx] = main_tabla[k - 1][idx];
				}
			}
		}
	}
}

bool Board::chocar(int x2, int y2) {

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			if (mblock[i][j] && main_cpy[y2 + i][x2 + j] != 0) {
				return true;
			}
		}
	}
	return false;
}

bool Board::gameover() {
	return isGameOver;
}

void Board::proceso_block() {
	if (!chocar(x, y + 1)) {
		mover_block(x, y + 1);
	} else {
		limpiar_linea();
		save_cpy();
		new_block();
		re_draw_main();
	}
}
