#pragma once
#include "gameNode.h"
class intro :
	public gameNode
{
public:
	image* _introBackground;
	int _count;
	int _index;

	RECT _gameStartRc;
	image* _gameStartImage;
	image* _gameStartOverImage;

	RECT _optionRc;
	image* _optionImage;
	image* _optionOverImage;

	RECT _quitRc;
	image* _quitImage;
	image* _quitOverImage;

	HRESULT init();
	void release();
	void update();
	void render();
	intro() {}
	~intro() {}
};

