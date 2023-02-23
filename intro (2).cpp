#include "stdafx.h"
#include "intro.h"




HRESULT intro::init()
{
	_introBackground = IMAGEMANAGER->addFrameImage("introBackground", "tw/intro/introbackground_21760x800_17.bmp",21760,800,17,1);
	_count = _index = 0;

	_gameStartRc = RectMakeCenter(WINSIZEX / 2, 560, 400, 60);
	_gameStartImage = IMAGEMANAGER->addImage("gameStart", "tw/intro/gamestart1_390x60.bmp", 390, 60, true, RGB(255, 0, 255));
	_gameStartOverImage = IMAGEMANAGER->addImage("gameStartOver", "tw/intro/gamestart_over_390x60.bmp", 390, 60, true, RGB(255, 0, 255));

	_optionRc = RectMakeCenter(WINSIZEX / 2, 640, 260, 60);
	_optionImage = IMAGEMANAGER->addImage("option", "tw/intro/option1_260x60.bmp", 260, 60, true, RGB(255, 0, 255));
	_optionOverImage = IMAGEMANAGER->addImage("optionOver", "tw/intro/option_over_260x60.bmp", 260, 60, true, RGB(255, 0, 255));

	_quitRc = RectMakeCenter(WINSIZEX / 2, 720, 180, 60);
	_quitImage = IMAGEMANAGER->addImage("quit", "tw/intro/quit1_180x60.bmp", 180, 60, true, RGB(255, 0, 255));
	_quitOverImage = IMAGEMANAGER->addImage("quitOver", "tw/intro/quit_over_180x60.bmp", 180, 60, true, RGB(255, 0, 255));
	
	return S_OK;
}

void intro::release()
{
}

void intro::update()
{

	//로고배경 번쩍임 반복
	_introBackground->setFrameY(0);
	_count++;
	if (_count % 10 == 0)
	{
		_index++;
		if (_index >= 17)
		{
			_index = 0;
		}
		_introBackground->setFrameX(_index);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_gameStartRc, _ptMouse))
		{
			SCENEMANAGER->loadScene("boss");
		}
		//게임종료
		if (PtInRect(&_quitRc, _ptMouse))
		{
			PostMessage(_hWnd, WM_QUIT, 0, 0);
		}
	}
}

void intro::render()
{
	_introBackground->frameRender(getMemDC(), 0, 0);

	//Rectangle(getMemDC(), _gameStartRc);
	//Rectangle(getMemDC(), _optionRc);
	//Rectangle(getMemDC(), _exitRc);
	
	//game start 
	_gameStartImage->render(getMemDC(), _gameStartRc.left, _gameStartRc.top);
	//game start 마우스 오버
	if (PtInRect(&_gameStartRc, _ptMouse))
	{		
		_gameStartOverImage->render(getMemDC(), _gameStartRc.left, _gameStartRc.top);
	}

	//option 
	_optionImage->render(getMemDC(), _optionRc.left, _optionRc.top);
	//option 마우스 오버
	if (PtInRect(&_optionRc, _ptMouse))
	{
		_optionOverImage->render(getMemDC(), _optionRc.left, _optionRc.top);
	}

	//quit 
	_quitImage->render(getMemDC(), _quitRc.left, _quitRc.top);
	//quit 마우스 오버
	if (PtInRect(&_quitRc, _ptMouse))
	{
		_quitOverImage->render(getMemDC(), _quitRc.left, _quitRc.top);
	}

}
