#pragma once
#include "gameNode.h"

/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
/*헤더파일만 메인게임에 추가하기*/
#include "intro.h"
#include "loading.h"
#include "boss.h"

class mainGame : public gameNode
{
	intro* _intro;
	boss* _boss;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

