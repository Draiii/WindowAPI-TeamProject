#include "stdafx.h"
#include "intro.h"




HRESULT intro::init()
{
	_introBackground = IMAGEMANAGER->addFrameImage("introBackground", "tw/intro/introbackground_21760x800_17.bmp",21760,800,17,1);
	_count = _index = 0;
	
	return S_OK;
}

void intro::release()
{
}

void intro::update()
{
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

}

void intro::render()
{
	_introBackground->frameRender(getMemDC(), 0, 0);
}
