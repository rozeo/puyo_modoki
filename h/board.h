#define P_X 6
#define P_Y 12

#define P_SIZE 40
#define DEL_OVER 4

class c_board{
public:
	c_board();
	void Draw();
	void DrawPuyo();
	void DrawDropPuyo(int,int,int*);
	int CheckGameOver();
	int PutsPuyo(int,int,int*);
	void DrawNextPuyo(int *);
	int CheckMove(int,int,int *);
	int DownPuyo();
	int DeletePuyo(int *);
	void Init();
	void DrawGameOver();
	void DrawScoreBoard(long long int score);
private:

	int del(int,int,int,int);
	int down(int,int,int);
	bool flg[P_Y][P_X];
	int g_puyo[5];
	int g_board;
	int g_nboard;

	int g_cross;

	int g_over;
	int g_score;

	int stat_board[P_Y][P_X];
};