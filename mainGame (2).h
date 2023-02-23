#pragma once
#include "gameNode.h"

/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
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

