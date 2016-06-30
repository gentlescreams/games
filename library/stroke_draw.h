#ifndef _STROKEDRAW_H_
#define _STROKEDRAW_H_


class StrokeDraw
{

public:
	~StrokeDraw();
	static StrokeDraw* GetInstance();
	void gameSet(const int player);
	void gameControl();
	void gameKeyControl();
	void Score(int team, const char* score, const char* name);
private:
	StrokeDraw();
	static StrokeDraw* instance;
};



#endif // _STROKEDRAW_H_
