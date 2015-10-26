#include "../h/player.h"
#include "DxLib_GCC.h"
#include <math.h>

#define SCORE_MULTIPLIER 114.514

c_player::c_player(){
	board = new c_board();
	control = new c_control();
	mode = 0;
	rad = 0;
	colors = 3;
	next_x = 2;
	next_y = 11;
	DelMode = 0;
	score = 0;
	r_del = 0;
}

int c_player::Process(){
	control->UpdateKeyInput();
	board->Draw();
	board->DrawPuyo();
	board->DrawScoreBoard(this->score);

	switch(mode){
	case 0:
		DrawString(10,360,"Press SPACE key to start.",GetColor(255,255,255));
		DrawString(10,380,"Change Colors <- -> Key.",GetColor(255,255,255));
		DrawFormatString(10,400,GetColor(255,255,255),"Colors:%d",colors);

		//change colors much
		if(control->GetStateKey(KEY_INPUT_LEFT) == 1) colors--;
		if(control->GetStateKey(KEY_INPUT_RIGHT) == 1)colors++;
		if(colors < 2) colors = 2;
		if(colors > 5) colors = 5;

		if(control->GetStateKey(KEY_INPUT_SPACE) == 1){
			GameInit();
			loop_count = 0;
			mode = 1;
			DelMode = 0;
		}
		break;
	case 1:
		board->DrawNextPuyo(next_puyo);

		if(DelMode == 0){
			DropControl();
			board->DrawDropPuyo(next_x,next_y,n_drop);
		}else if(DelMode == 1){
			int rr = 0;
			if(r_del > 0)DrawFormatString(250,300,GetColor(255,255,255),"%d Chains!",r_del);
			if( loop_count % 20 == 0 ){
				if(board->DownPuyo() == 0){
					int ma = 0;
					rr = board->DeletePuyo(&ma);
					if(rr > 0)r_del++;

					score += sqrt(pow(SCORE_MULTIPLIER,r_del) * sqrt(pow((SCORE_MULTIPLIER * ma),rr) * colors));

					if(rr == 0){
						if(board->CheckGameOver() != 0) mode = 2;
						else{
							DelMode = 0;
							r_del = 0;
							SetNext();
						}
					}
				}
			}
		}
		loop_count++;
		break;
	case 2:
		board->DrawGameOver();
		if(control->GetStateKey(KEY_INPUT_SPACE) == 1)
			board->Init(),mode = 0,score = 0;
		break;
	}

	if(control->GetStateKey(KEY_INPUT_ESCAPE) == 1) return 1;
	return 0;
}


void c_player::GameInit(){
	GenerateNext();
	SetNext();
}

void c_player::GenerateNext(){
	for(int i = 0;i < 2;i++)
		next_puyo[i] = rand()%colors+1;
}

void c_player::SetNext(){
	for(int i = 0;i < 2;i++)
		n_drop[i] = next_puyo[i];
	n_drop[2] = 0;
	n_drop[3] = 0;
	GenerateNext();

	next_x = 2;
	next_y = 11;
}

void c_player::DropControl(){
	if((control->GetStateKey(KEY_INPUT_LEFT) - 1) % 5  == 0)
		if(board->CheckMove(next_x - 1,next_y,n_drop) == 0)
			next_x--;

	if((control->GetStateKey(KEY_INPUT_RIGHT) - 1) % 5 == 0)
		if(board->CheckMove(next_x + 1,next_y,n_drop) == 0)
			next_x++;

	if((control->GetStateKey(KEY_INPUT_DOWN) - 1) % 5  == 0)
		if(board->CheckMove(next_x,next_y - 1,n_drop) == 0)
			next_y--;

	if(control->GetStateKey(KEY_INPUT_Z) == 1) spin(0);
	if(control->GetStateKey(KEY_INPUT_X) == 1) spin(1);

	if(loop_count % (60 - (int)(score / 5000000)) == 0 && loop_count > 0){
		if(board->CheckMove(next_x,next_y - 1,n_drop) == 0)
			next_y--;
		else{
			board->PutsPuyo(next_x,next_y,n_drop);
			DelMode = 1;
		}
	}

	if(next_x < 0) next_x = 0;
	if(next_x >= P_X) next_x = P_X - 1;
	if(next_y < 0) next_y = 0;
}

void c_player::spin(int op){
	int n_b[4];
	int s[2][2];
	int w[2][2];
	for(int i = 0;i < 2;i++)
		for(int j = 0;j < 2;j++)
			s[i][j] = n_drop[i*2 + j],n_b[i*2 + j] = n_drop[i*2 + j];

	switch(op){
		case 0:
			for(int i = 0;i < 2;i++)
				for(int j = 0;j < 2;j++)
					w[j][1-i] = s[i][j];

			break;

		case 1:
			for(int i = 0;i < 2;i++)
				for(int j = 0;j < 2;j++)
					w[1-j][i] = s[i][j];

			break;
	}
	int cnt = 0,flg = 0;
	for(int i = 0;i < 2;i++)
		for(int j = 0;j < 2;j++)
			n_drop[i*2+j] = w[i][j];

	for(int i = 0;i < 4;i++){
		if(n_drop[i] == 0 && flg == 0)cnt++;
		else if(n_drop[i] > 0) flg = 1;
		if(cnt > 0){
			int b = n_drop[i];
			n_drop[i - cnt] = b;
			n_drop[i] = 0;
		}
	}
	if(board->CheckMove(next_x,next_y,n_drop) != 0)
		for(int i = 0;i < 4;i++)
			n_drop[i] = n_b[i];
}