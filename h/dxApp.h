#include "../h/player.h"

class dxApp{
public:
	dxApp(int,int,int,int);
	~dxApp();

	int Init();
	int run();
private:
	int e_Stat;
	int Entry();
	c_player *player;
};