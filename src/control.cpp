#include "../h/control.h"
#include <DxLib_GCC.h>


c_control::c_control(){
	for(int i = 0;i < KEYS;i++)
		key[i] = 0;
}

void c_control::UpdateKeyInput(){
	char s_key[KEYS];
	GetHitKeyStateAll(s_key);
	for(int i = 0;i < KEYS;i++){
		if(s_key[i] == 0) key[i] = 0;
		else			  key[i]++;
	}
}

int c_control::GetStateKey(unsigned char handle){
	return key[(int)handle];
}