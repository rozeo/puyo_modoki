#include "../h/dxApp.h"
#include <DxLib_GCC.h>

//クラスのインスタンス化と初期化
dxApp::dxApp(int ws,int hs,int op_draw,int fullFlg){
	e_Stat = 0;
	ChangeWindowMode(fullFlg);
	SetGraphMode(ws,hs,32);
	if(DxLib_Init() != 0 && SetDrawScreen(op_draw) != 0){
		e_Stat = -1;
		return;
	}

	player = new c_player();
}

dxApp::~dxApp(){
	DxLib_End();
}

//ws,hs ウィンドウのサイズ
//op_draw 描画先
//fullFlg フルスクリーンフラグ
int dxApp::Init(){

	if( e_Stat != 0) return -1;
	return 0;
}

int dxApp::run(){

	while(ProcessMessage() == 0&&ClearDrawScreen() == 0){
		if(this->Entry() != 0)
			break;
		ScreenFlip();
	}

	delete this;
	return 0;
}

int dxApp::Entry(){
	if( player->Process() != 0 ) return 1;
	return 0;
}