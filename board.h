#ifndef BOARD_H_
#define BOARD_H_

#include "block.h"

class Board
{

public:

	void control_input();
	void save_cpy();
	void proceso_block();
	void start();

	void limpiar_screen();
	void iniciar_draw_main();
	void re_draw_main();
	int getRandom(int min, int max);
	void new_block();
	void mover_block(int x, int y);
	void rotar_block();
	void limpiar_linea();
	bool chocar(int x, int y);
	bool gameover();

	enum {
		POS_FREE, POS_LLENA, POS_BORDES
	};

private:
	bool isGameOver;
};

#endif
