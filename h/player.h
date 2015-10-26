#include "../h/board.h"
#include "../h/control.h"

class c_player{
public:
	c_player();
	int Process();
	void DropControl();
	void GameInit();
	void GenerateNext();
	void SetNext();
	void spin(int);

	int n_drop[4];
	int next_puyo[2];

private:
	int next_x,next_y;
	c_board *board;
	c_control *control;

	int loop_count;
	int colors;
	int rad;

	int DelMode;

	long long int score;
	int r_del;

	int mode;
};