#pragma once
#include "gameNode.h"

/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
#include "intro.h"
#include "loading.h"

class mainGame : public gameNode
{
	intro* _intro;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

