#pragma once
#include "gameNode.h"
class intro :
	public gameNode
{
public:
	image* _introBackground;
	int _count;
	int _index;

	HRESULT init();
	void release();
	void update();
	void render();
	intro() {}
	~intro() {}
};

