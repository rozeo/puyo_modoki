#include "../h/board.h"
#include <DxLib_GCC.h>

c_board::c_board(){
	g_puyo[0] = LoadGraph("data/rp.png");
	g_puyo[1] = LoadGraph("data/yp.png");
	g_puyo[2] = LoadGraph("data/gp.png");
	g_puyo[3] = LoadGraph("data/pp.png");
	g_puyo[4] = LoadGraph("data/bp.png");

	g_board = LoadGraph("data/board.png");

	g_nboard = LoadGraph("data/Next_board.png");

	g_cross = LoadGraph("data/cross.png");

	g_over = LoadGraph("data/over.png");
	g_score = LoadGraph("data/score_board.png");

	Init();
}

void c_board::Init(){
	for(int i = 0;i < P_Y;i++)
		for(int j = 0;j < P_X;j++){
			stat_board[i][j] = 0;
			flg[i][j] = false;
		}
}

void c_board::Draw(){
	DrawGraph(0,0,g_board,TRUE);
	DrawGraph(255,50,g_nboard,TRUE);
	DrawGraph(2*40,0,g_cross,TRUE);
	DrawGraph(3*40,0,g_cross,TRUE);
}

void c_board::DrawPuyo(){
	for(int i = 0;i < P_Y;i++)
		for(int j = 0;j < P_X;j++)
			if(stat_board[i][j] > 0)
				DrawGraph(40 * j,480 - (i + 1) * 40,g_puyo[stat_board[i][j] - 1],TRUE);
}

int c_board::CheckGameOver(){
	if( stat_board[P_Y - 1][2] > 0 || stat_board[P_Y - 1][3] > 0 ) return 1;
	return 0;
}

void c_board::DrawDropPuyo(int x,int y,int *puyo){
	for(int i = 0;i < 4;i++){
		if(puyo[i] > 0)
			DrawGraph((x + (i % 2)) * 40,(11-y) * 40 + (int)(i/2)*40,g_puyo[puyo[i]-1],TRUE);
	}
}

void c_board::DrawNextPuyo(int *puyo){
	for(int i = 0;i < 2;i++)
		DrawGraph(285 + i * 40,105,g_puyo[puyo[i] - 1],TRUE);
}

int c_board::DeletePuyo(int *ma){
	int cnt = 0;
	for(int i = 0;i < P_Y;i++){
		for(int j = 0;j < P_X;j++){
			if(stat_board[i][j] > 0){
				int m = del(j,i,0,stat_board[i][j]);
				if(m >= DEL_OVER){
					cnt++;
					for(int k = 0;k < P_Y;k++)
						for(int h = 0;h < P_X;h++)
							if(flg[k][h])
								stat_board[k][h]=0,*ma = *ma+1;

				}
				for(int h = 0;h < P_Y;h++)
					for(int k = 0;k < P_X;k++)
						flg[h][k]=false;
			}

		}
	}
	return cnt;
}

int c_board::del(int x,int y,int cnt,int color){
	if(flg[y][x]) return cnt;
	if(stat_board[y][x] == 0 || stat_board[y][x] != color){
		flg[y][x] = false;
		return cnt;
	}else{
		flg[y][x] = true;
		cnt++;
	}

	if(x + 1 < P_X) cnt = del(x + 1,y,cnt,stat_board[y][x]);
	if(x - 1 >= 0)  cnt = del(x - 1,y,cnt,stat_board[y][x]);
	if(y + 1 < P_Y) cnt = del(x,y + 1,cnt,stat_board[y][x]);
	if(y - 1 >= 0)  cnt = del(x,y - 1,cnt,stat_board[y][x]);

	return cnt;
}

int c_board::DownPuyo(){
	int cnt = 0;
	for(int i = 0;i < P_Y;i++){
		for(int j = 0;j < P_X;j++){
			if( down(j,i,0) > 0 )cnt++;
		}
	}
	return cnt;
}

int c_board::down(int x,int y,int cnt){
	if(y >= P_Y) return 0;
	if(stat_board[y][x] == 0) cnt = down(x,y+1,cnt+1);
	else{
		if(cnt == 0) return 0;
		stat_board[y - cnt][x] = stat_board[y][x];
		stat_board[y][x] = 0;
	}
	return cnt;
}

//移動先の判定
int c_board::CheckMove(int x,int y,int *puyo){
	if(y < 0) return 1;
	for(int i = 0;i < 4;i++){
		if(puyo[i] > 0){
			if(y - (i / 2) < 0)					 return 2;
			if(x + (i % 2) < 0)					 return 3;
			if(x + (i % 2) >= P_X)				 return 4;
			if(stat_board[y-(i/2)][x+(i%2)] > 0) return 5;
		}
	}
	return 0;
}

int c_board::PutsPuyo(int x,int y,int *puyo){
	for(int i = 0;i < 4;i++)
		if(puyo[i] > 0)
			stat_board[y-(i/2)][x+(i%2)] = puyo[i];
}

void c_board::DrawGameOver(){
	DrawGraph(20,70,g_over,TRUE);
	DrawString(80,300,"Press SPACE key, back to start.",GetColor(255,255,255));
}

void c_board::DrawScoreBoard(long long int score){
	DrawGraph(240,200,g_score,TRUE);
	DrawFormatString(250,265,GetColor(255,255,255),"%lld",score);
}