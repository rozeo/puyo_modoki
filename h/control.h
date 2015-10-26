#define KEYS 256

class c_control{
public:
	c_control();
	void UpdateKeyInput();
	int GetStateKey(unsigned char handle);
private:
	int key[KEYS];
};