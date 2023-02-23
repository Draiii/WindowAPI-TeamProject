#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	_player.x = 500;
	_player.y = 500;
	_player.width = 70;
	_player.height = 125;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

	//보스 렉트
	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.width, _boss.height);
	_boss.imageRc = RectMakeCenter(_boss.x, _boss.y, _boss.imageWidth, _boss.imageHeight);

	//테스트 방향
	_testDirection = BOTTOM;
	_boss.direction = BOTTOM;
	_boss.idle = IDLE;
	//테스트용 크로스
	_boss.crossHair = { _ptMouse.x - 25, _ptMouse.y - 25 };
	_boss.x = WINSIZEX/2;
	_boss.y = WINSIZEY/2;
	_boss.width = 70;
	_boss.height = 120;
	_boss.imageWidth = 144;
	_boss.imageHeight = 144;
	_boss.rangeX = _boss.x;
	_boss.rangeY = _boss.y;
	_boss.moveSpeed = 4.0f;
	_boss.dashSpeed = 15.0f;
	_boss.attack = false;;
	_boss.dash = false;
	_boss.cast = false;
	_boss.slamCast = false;
	_boss.ballCast = false;
	_boss.orbCast = false;
	_boss.phase = false;

	//카오스 웨이브 발사
	_boss.chaosWaveFire = false;
	_boss.chaosWavePatternCount = GetTickCount64();	
	//카오스 볼 발사
	_boss.chaosBallFire = false;
	_boss.chaosBallPatternCount = GetTickCount64();
	//메테오 발사
	_boss.meteoStrikeFire = false;
	_boss.meteoStrikePatternCount = GetTickCount64();
	//카오스 토네이도 발사
	_boss.chaosTornadoFire = false;
	_boss.chaosTornadoPatternCount = GetTickCount64();
	//카오스 아이스퀸 발사
	_boss.chaosIceQueenFire = false;
	_boss.chaosIceQueenPatternCount = GetTickCount64();

	//보스 페이즈1 아이들
	_phase1BossIdleImage = IMAGEMANAGER->addFrameImage("phase1BossIdle", "tw/boss/phase1/phase1bossidle_432x144_3.bmp", 432, 144, 3, 1);
	_phase1BossIdleCount, _phase1BossIdleIndex = 0;
	//페이즈 1 보스 피격
	_phase1BossHurtImage = IMAGEMANAGER->addFrameImage("phase1BossHurt", "tw/boss/phase1/phase1bosshurt_720x288_5_2.bmp", 720, 288, 5, 2);
	_phase1BossHurtCount = _phase1BossHurtIndex = 0;
	//페이즈 1 보스 슬램캐스트
	_phase1BossCastImage = IMAGEMANAGER->addFrameImage("phase1BossSlamCast", "tw/boss/phase1/phase1bossslamcast_864x144_6.bmp", 864, 144, 6, 1);
	_phase1BossCastCount = _phase1BossCastIndex = 0;
	//페이즈 1 서몬 아이들
	_phase1SummonIdleImage = IMAGEMANAGER->addImage("summonIdle", "tw/boss/phase1/summonidle_324x324.bmp", 324, 324, true, RGB(255, 0, 255));
	//페이즈 1 서몬 볼 캐스트
	_phase1SummonBallCastImage = IMAGEMANAGER->addFrameImage("summonBallCast", "tw/boss/phase1/summonball_4680x324_10.bmp", 4680, 324, 10, 1);
	_phase1SummonBallCastCount = _phase1SummonBallCastIndex = 0;
	_phase1SummonBallCast = false;
	//페이즈 1 서몬 슬램 캐스트
	_phase1SummonSlamCastImage = IMAGEMANAGER->addFrameImage("summonSlamCast", "tw/boss/phase1/summonslamcast_3240x324_10.bmp", 3240, 324, 10, 1);
	_phase1SummonSlamCastCount = _phase1SummonSlamCastIndex = 0;
	_phase1SummonSlamCast = false;
	//페이즈 1 서몬 오브 캐스트
	_phase1SummonOrbCastImage = IMAGEMANAGER->addFrameImage("summonOrbCast", "tw/boss/phase1/summonorb_3240x324_10.bmp", 3240, 324, 10, 1);
	_phase1SummonOrbCastCount = _phase1SummonOrbCastIndex = 0;
	_phase1SummonOrbCast = false;
	//보스 페이즈 2 진입
	_phase2BossStartImage = IMAGEMANAGER->addFrameImage("phase2BossStart", "tw/boss/phase2/phase2_2880x144_20.bmp", 2880, 144, 20, 1);
	_phase2BossStartCount = _phase2BossStartIndex = 0;
	//페이즈2 보스 슬램 캐스트
	_phase2BossSlamCastImage = IMAGEMANAGER->addFrameImage("phase2BossSlamCast", "tw/boss/phase2/phase2bossslamcast_864x144_6.bmp", 864, 144, 6, 1);
	_phase2BossSlamCastCount = _phase2BossSlamCastIndex = 0;
	//페이즈2 보스 공격1
	_phase2BossAttack1Image = IMAGEMANAGER->addFrameImage("phase2BossAttack1", "tw/boss/phase2/phase2bossattack1_1008x576_7_4.bmp", 1008, 576, 7, 4);
	_phase2BossAttack1Count = _phase2BossAttack1Index = 0;
	//페이즈2 보스 공격2
	_phase2BossAttack2Image = IMAGEMANAGER->addFrameImage("phase2BossAttack2", "tw/boss/phase2/phase2bossattack2_864x576_6_4.bmp", 864, 576, 6, 4);
	_phase2BossAttack2Count = _phase2BossAttack2Index = 0;
	//페이즈2 보스 대쉬
	_phase2BossDashImage = IMAGEMANAGER->addFrameImage("phase2BossDash", "tw/boss/phase2/phase2bossdash_2160x864_10_4.bmp", 2160, 864, 10, 4);
	_phase2BossDashCount = _phase2BossDashIndex = 0;
	//페이즈2 보스 대쉬 그림자
	_phase2BossDashShadow1Image = IMAGEMANAGER->addFrameImage("phase2BossDashShadow1", "tw/boss/phase2/phase2bossdashshadow1_2160x864_10_4.bmp", 2160, 864, 10, 4);
	_phase2BossDashShadow2Image = IMAGEMANAGER->addFrameImage("phase2BossDashShadow2", "tw/boss/phase2/phase2bossdashshadow2_2160x864_10_4.bmp", 2160, 864, 10, 4);
	_phase2BossDashShadow3Image = IMAGEMANAGER->addFrameImage("phase2BossDashShadow3", "tw/boss/phase2/phase2bossdashshadow3_2160x864_10_4.bmp", 2160, 864, 10, 4);
	_phase2BossDashShoadow1Count = _phase2BossDashShoadow1Index = 0;
	_phase2BossDashShoadow2Count = _phase2BossDashShoadow2Index = 0;
	_phase2BossDashShoadow3Count = _phase2BossDashShoadow3Index = 0;



	//스킬 초기화
	//에어스핀 버스트
	_airSpinnerBurstImage = IMAGEMANAGER->addFrameImage("airSpinnerBurst", "tw/boss/skill/dashWind_1632x70_6.bmp", 1632, 70, 6, 1);
	_airSpinnerBurstCount, airSpinnerBurstIndex = 0;
	_airSpinnerBurstIsStart = false;
	//캐스트 서클
	for (int i = 0; i < METEO_STRIKE_MAX; i++)
	{
		tagCastCircle _castCircle;		
		_castCircle.count = _castCircle.index = 0;
		_castCircle.width = _castCircle.height = 384;
		_castCircle.x = 500;
		_castCircle.y = 500;		
		_castCircle.rc = RectMakeCenter(_castCircle.x, _castCircle.y, _castCircle.width, _castCircle.height);
		char cBuf[100];
		wsprintf(cBuf, "castCicle%d", i);
		_castCircle.isCast = false; 
		_castCircle.castCirleImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/CastingCircleEffect_7680x384_20.bmp", 7680, 384, 20, 1);
		_vCastCircle.push_back(_castCircle);
	}
	//카오스 오브
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		tagChaosOrb _chaosOrb;
		_chaosOrb.count = _chaosOrb.index = 0;
		_chaosOrb.width = _chaosOrb.height = 120;
		_chaosOrb.x = 500;
		_chaosOrb.y = 500;
		_chaosOrb.rc = RectMakeCenter(_chaosOrb.x, _chaosOrb.y, _chaosOrb.width, _chaosOrb.height);
		char cBuf[100];
		wsprintf(cBuf, "chaosOrb%d", i);
		_chaosOrb.isCast = false;
		_chaosOrb.chaosOrbImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/chaosorb_1200x120_10.bmp", 1200, 120, 10, 1);
		_vChaosOrb.push_back(_chaosOrb);
	}


	

	//레이저
	_chaosLaser.width = 1500;
	_chaosLaser.height = 72;
	_chaosLaser.angle = 0;
	_chaosLaser.fire = 0;
	_chaosLaser.isFire = false;
	_chaosLaser.index = _chaosLaser.count = 0;
	_chaosLaser.x = _chaosLaser.y = 0;
	_chaosLaser.chaosImage = IMAGEMANAGER->addImage("chaosLaser", "tw/boss/skill/chaosbeam_1500x72.bmp", _chaosLaser.width, _chaosLaser.height);

	//카오스 웨이브
	for (int i = 0; i < CHAOS_WAVE_MAX; i++)
	{
		tagChaosWaveSkill chaosWave;
		chaosWave.width = chaosWave.height = 285;
		chaosWave.index = chaosWave.count = 0;
		chaosWave.rc = RectMakeCenter(_boss.x, _boss.y, chaosWave.width, chaosWave.height);
		chaosWave.rc2 = RectMakeCenter(_boss.x, _boss.y, chaosWave.width, chaosWave.height);
		chaosWave.rc3 = RectMakeCenter(_boss.x, _boss.y, chaosWave.width, chaosWave.height);
		chaosWave.x = 700;
		chaosWave.y = 400;		
		chaosWave.angle = 0.0f;
		chaosWave.isFire = false;
		char cBuf[100];
		wsprintf(cBuf, "chaosWave%d", i);
		chaosWave.chaosWaveImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/chaoswave_2565x285_9.bmp", 2565, 285, 9, 1);
		_vChaosWave.push_back(chaosWave);
	}
	_ChaosWaveTurn = 0;

	//카오스 볼
	for (int i = 0; i < CHAOS_BALL_MAX; i++)
	{

		_chaosBall[i].x = _boss.x;
		_chaosBall[i].y = _boss.y;
		_chaosBall[i].width = _chaosBall[i].height = 124;
		_chaosBall[i].rc = RectMakeCenter(_boss.x, _boss.y, _chaosBall[i].width, _chaosBall[i].height);
		_chaosBall[i].count = _chaosBall[i].index = 0;
		_chaosBall[i].angle = 0.0f;
		_chaosBall[i].speed = 10.0f;
		_chaosBall[i].isFire = false;
		char cBuf[100];
		wsprintf(cBuf, "chaosBall%d", i);
		_chaosBall[i].chaosBallImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/chaosball_744x124_6.bmp", 744, 124, 6, 1);
	}
	_chaosBallTurn = 0;
	_ballAngleTurn = PI * 2 / 16;
	_chaosBallcoolDown = GetTickCount64();
	//메테오
	for (int i = 0; i < METEO_STRIKE_MAX; i++)
	{
		tagMeteoStrikeSkill _meteoStrike;
		_meteoStrike.width = 300;
		_meteoStrike.height = 400;
		_meteoStrike.x = 1000.f;
		_meteoStrike.y = -500.f;
		_meteoStrike.angle = 0.0f;
		_meteoStrike.speed = 12.0f;
		_meteoStrike.range.x = 0;
		_meteoStrike.range.y = 0;
		_meteoStrike.skillCount = _meteoStrike.skillIndex = 0;
		_meteoStrike.ExplosionCount = _meteoStrike.ExplosionIndex = 0;
		_meteoStrike.Explosion2Count = _meteoStrike.Explosion2Index = 0;
		_meteoStrike.coolDownTime = 0;
		_meteoStrike.isFire = false;
		_meteoStrike.isExplosion = false;
		char cBuf[100];
		wsprintf(cBuf, "meteoStrike%d", i);
		_meteoStrike.meteoStrikeImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/MeteorStrike_1800x410_6.bmp", (float)_meteoStrike.x, (float)_meteoStrike.y, 1800, 410, 6, 1);
		char cBuf2[100];
		wsprintf(cBuf2, "meteoStrikeExplosion%d", i);
		_meteoStrike.meteoStrikeExplosionImage = IMAGEMANAGER->addFrameImage(cBuf2, "tw/boss/skill/fireexplosion_2800x386_7.bmp", (float)_meteoStrike.range.x, (float)_meteoStrike.range.y, 2800, 386, 7, 1);
		char cBuf3[100];
		wsprintf(cBuf3, "meteoStrikeExplosion2%d", i);
		_meteoStrike.meteoStrikeExplosion2Image = IMAGEMANAGER->addFrameImage(cBuf3, "tw/boss/skill/fireexplosion2_462x366_11.bmp", (float)_meteoStrike.range.x, (float)_meteoStrike.range.y, 5082, 366, 11, 1);
		_vMeteoStrike.push_back(_meteoStrike);
	}
	_meteoStrikeTurn = 0;

	//카오스 토네이도
	for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
	{
		tagChaosTornadoSkill chaosTornado;

		chaosTornado.width = 300;
		chaosTornado.height = 232;
		chaosTornado.x = 700;
		chaosTornado.y = 400;
		chaosTornado.index = chaosTornado.count = 0;
		chaosTornado.angle = 0.0f;
		chaosTornado.range = 8.0f;
		chaosTornado.isFire = false;
		chaosTornado.rc = RectMakeCenter(_boss.x, _boss.y, chaosTornado.width, chaosTornado.height);
		char cBuf[100];
		wsprintf(cBuf, "chaosTornado%d", i);
		chaosTornado.chaosTornadoImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/chaostornado_3600x232_12.bmp", 3600, 232, 12, 1);
		_vChaosTornado.push_back(chaosTornado);
	}
	_chaosTornadoTurn= 0;

	//카오스 아이스퀸 
	for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
	{
		tagChaosIceQueenSkill chaosIceQueen;
	
		chaosIceQueen.width = 120;
		chaosIceQueen.height = 220;
		chaosIceQueen.x = 900;
		chaosIceQueen.y = 400;
		chaosIceQueen.count = chaosIceQueen.index = 0;
		chaosIceQueen.angle = (PI * 2 / 8);
		chaosIceQueen.isFire = false;
		chaosIceQueen.rc = RectMakeCenter(_boss.x, _boss.y, chaosIceQueen.width, chaosIceQueen.height);
		char cBuf[100];
		wsprintf(cBuf, "chaosIceQueen%d", i);
		chaosIceQueen.chaosIceQueenImage = IMAGEMANAGER->addFrameImage(cBuf, "tw/boss/skill/chaosicequeen_1200x220_10.bmp", 1200, 220, 10, 1);
		_vChaosIceQueen.push_back(chaosIceQueen);
	}
	_chaosIceQueenTrun = 0;
	

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{

	//페이즈1 보스 업데이트
	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.width, _boss.height);
	_boss.imageRc = RectMakeCenter(_boss.x, _boss.y, _boss.imageWidth, _boss.imageHeight);

	//페이즈 1 보스 패턴
	if (!_boss.phase)
	{
		//	int timer = GetTickCount64();
		//	if (GetTickCount64() - timer >= 1000)
		//		timer = GetTickCount64();

		//카오스 웨이브 5~10초마다 실행
		if ( GetTickCount64() - _boss.chaosWavePatternCount >= RND->range(5000, 10000) && !_boss.cast && !_boss.chaosTornadoFire)
		{			
			this->chaosWaveAction();
			_boss.chaosWavePatternCount = GetTickCount64();			
		}
		////3초뒤에 초기화
		if (GetTickCount64() - _boss.chaosWavePatternCount >= 2000 && _boss.chaosWaveFire)
		{
			_boss.chaosWaveFire = false;
		}

		//카오스 볼 패턴  7~11 초마다 실행
		if (GetTickCount64() - _boss.chaosBallPatternCount >= RND->range(7000, 11000) && !_boss.cast)
		{
			this->chaosBallAction();			
			_boss.chaosBallPatternCount = GetTickCount64();
		}		

		//메테오 15~20초마다 실행
		if (GetTickCount64() - _boss.meteoStrikePatternCount >= RND->range(15000, 20000) && !_boss.cast)
		{
			this->meteoStrikeAction();			
			_boss.meteoStrikePatternCount = GetTickCount64();
		}

		//카오스 토네이도 8~12초 마다 실행
		if (GetTickCount64() - _boss.chaosTornadoPatternCount >= RND->range(8000, 12000) && !_boss.cast && !_boss.chaosWaveFire)
		{
			this->chaosTornadoAction();
			_boss.chaosTornadoPatternCount = GetTickCount64();
		}

		//카오스 아이스퀸 10~15초마다 실행
		if (GetTickCount64() - _boss.chaosIceQueenPatternCount >= RND->range(10000, 15000) && !_boss.cast)
		{
			this->chaosIceQueenAction();
			_boss.chaosIceQueenPatternCount = GetTickCount64();
		}

		//각각 초기화인데 안씀 

		////4초뒤 초기화
		//if (GetTickCount64() - _boss.meteoStrikePatternCount >= 4000 && _boss.meteoStrikeFire)
		//{
		//	this->meteoStrikeStop();
		//}
		////4초뒤에 초기화
		//if (GetTickCount64() - _boss.chaosBallPatternCount >= 4000 && _boss.chaosBallFire)
		//{
		//	this->chaosBallStop();
		//}
		////2초뒤 초기화
		//if (GetTickCount64() - _boss.chaosTornadoPatternCount >= 2000 && _boss.chaosTornadoFire)
		//{
		//	this->ChaosTornadoStop();
		//}
	}


	//테스트키
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//초기화 

		//보스 초기화
		_boss.slamCast = false;
		_boss.cast = false;
		_phase1SummonSlamCast = false;
		//카오스 웨이브 테스트				
		_boss.chaosWaveFire = false;
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{
			_vChaosWave[i].isFire = false;
		}
	
		//실행 

		//보스 캐스트 1개만 실행
		//_boss.ballCast = false;
		//_boss.orbCast = false;
		_boss.slamCast = true;
		_boss.cast = true;
		
		//카오스 웨이브 테스트
		_ChaosWaveTurn = 0;
		_phase1BossCastIndex = _phase1SummonSlamCastIndex = 0;
		_boss.chaosWaveFire = true;
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{
			_vChaosWave[i].count = _vChaosWave[i].index = 0;
			//플레이어 좌표 받아오기			
			_vChaosWave[i].x = _boss.x;
			_vChaosWave[i].y = _boss.y;
			_vChaosWave[i].angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);			
		}
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		//보스 초기화
		_boss.slamCast = false;
		_boss.cast = false;
		_phase1SummonSlamCast = false;
		//카오스 웨이브 테스트				
		_boss.chaosWaveFire = false;
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{
			_vChaosWave[i].isFire = false;			
		}
		//카오스 오브 테스트
		for (int i = 0; i < CHAOS_ORB; i++)
		{
			_vChaosOrb[i].isCast = false;
		}
	}

	//볼 캐스트
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		//초기화

		//보스 초기화		
		_boss.ballCast = false;
		_boss.cast = false;
		_phase1SummonBallCast = false;
		//카오스 볼테스트
		_boss.chaosBallFire = false;

		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{
			_chaosBall[i].isFire = false;
			_chaosBall[i].x = _boss.x;
			_chaosBall[i].y = _boss.y;
			_chaosBallcoolDown = GetTickCount64();
		}
		//카오스 오브 테스트
		for (int i = 0; i < CHAOS_ORB; i++)
		{
			_vChaosOrb[i].isCast = false;
		}

		//실행

		//보스 캐스트 1개만 실행
		//_boss.slamCast = false;		
		//_boss.orbCast = false;
		_boss.ballCast = true;
		_boss.cast = true;
	
		//카오스볼 테스트		
		_phase1BossCastIndex = _phase1SummonBallCastIndex = 0;
		_chaosBallTurn = 0;
		_boss.chaosBallFire = true;
		//페이즈 2일때 속도 바꾸기
		if (_boss.phase)
		{
			for (int i = 0; i < CHAOS_BALL_MAX; i++)
			{
				_chaosBall[i].speed = RND->range(5, 12);
			}
		}
		//카오스 오브 테스트
		for (int i = 0; i < CHAOS_ORB; i++)
		{
			_vChaosOrb[i].count = _vChaosOrb[i].index = 0;
			_vChaosOrb[i].x = _boss.x;
			_vChaosOrb[i].y = _boss.y;
			_vChaosOrb[i].isCast = true;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{		
		//보스 초기화
		_boss.ballCast = false;
		_boss.cast = false;
		_phase1SummonBallCast = false;
		
		//카오스 볼테스트
		_boss.chaosBallFire = false;
		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{
			_chaosBall[i].isFire = false;
			_chaosBall[i].x = _boss.x;
			_chaosBall[i].y = _boss.y;
			_chaosBallcoolDown = GetTickCount64();
		}
		//카오스 오브 테스트
		for (int i = 0; i < CHAOS_ORB; i++)
		{
			_vChaosOrb[i].isCast = false;
		}
	}

	//메테오 캐스트
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		//초기화

		//보스 초기화
		_boss.orbCast = false;
		_boss.cast = false;		
		_phase1SummonOrbCast = false;
		//메테오 테스트
		_boss.meteoStrikeFire = false;
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{
			_vCastCircle[i].count = _vCastCircle[i].index = 0;
			_vCastCircle[i].isCast = false;
			_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
			_vMeteoStrike[i].isFire = false;
			_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
			_vMeteoStrike[i].isExplosion = false;
		}

		//실행

		//보스 캐스트 1개만 실행
		//_boss.slamCast = false;
		//_boss.ballCast = false;
		_boss.orbCast = true;
		_boss.cast = true;
		
		//메테오 저장 테스트	
		_meteoStrikeTurn = 0;
		_phase1BossCastIndex = _phase1SummonOrbCastIndex = 0;
		_boss.meteoStrikeFire = true;
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{			
			//_vCastCircle[i].x = _vMeteoStrike[i].range.x = 200 + (i * 200);
			//_vCastCircle[i].y = _vMeteoStrike[i].range.y = 400;			
			_vCastCircle[i].x = _vMeteoStrike[i].range.x = RND->range(1100);
			_vCastCircle[i].y = _vMeteoStrike[i].range.y = RND->range(700);
			_vMeteoStrike[i].x = _vCastCircle[i].x + 400;
			_vMeteoStrike[i].y = -300;
			_vCastCircle[i].count = _vCastCircle[i].index = 0;
			_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
			_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
			_vMeteoStrike[i].Explosion2Count = _vMeteoStrike[i].Explosion2Index = 0;
			//각도 저장
			_vMeteoStrike[i].angle = getAngle(_vMeteoStrike[i].x, _vMeteoStrike[i].y, _vCastCircle[i].x, _vCastCircle[i].y);		
		}
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		//보스 초기화
		_boss.orbCast = false;
		_boss.cast = false;
		_meteoStrikeTurn = 0;
		_boss.meteoStrikeFire = false;
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{
			_vCastCircle[i].count = _vCastCircle[i].index = 0;
			_vCastCircle[i].isCast = false;
			_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
			_vMeteoStrike[i].isFire = false;
			_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
			_vMeteoStrike[i].isExplosion = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		//초기화

		//보스 초기화
		_boss.slamCast = false;
		_boss.cast = false;
		_phase1SummonSlamCast = false;
		//카오스 토네이도 테스트				
		_boss.chaosTornadoFire = false;
		for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
		{
			_vChaosTornado[i].isFire = false;
		}

		//실행

		//보스 캐스트 1개만 실행
		//_boss.ballCast = false;
		//_boss.orbCast = false;
		_boss.slamCast = true;
		_boss.cast = true;		
		//카오스 토네이도 테스트			
		_chaosTornadoTurn = 0;
		_phase1BossCastIndex = _phase1SummonSlamCastIndex = 0;
		_boss.chaosTornadoFire = true;
		for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
		{
			_vChaosTornado[i].count = _vChaosTornado[i].index = 0;
			_vChaosTornado[i].x = _boss.x;
			_vChaosTornado[i].y = _boss.y;
			_vChaosTornado[i].angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		//보스 초기화
		_boss.slamCast = false;
		_boss.cast = false;
		_phase1SummonSlamCast = false;
		//카오스 토네이도 테스트				
		_boss.chaosTornadoFire = false;
		for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
		{
			_vChaosTornado[i].isFire = false;
		}
	}
	//카오스 아이스퀸
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		//초기화
		//보스 초기화
		_boss.orbCast = false;
		_boss.cast = false;
		_phase1SummonOrbCast = false;
		//카오스 아이스 퀸 테스트				
		_boss.chaosIceQueenFire = false;
		for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
		{
			_vChaosIceQueen[i].isFire = false;
		}


		//실행

		//보스 캐스트 1개만 실행
		//_boss.slamCast = false;
		//_boss.ballCast = false;
		_boss.orbCast = true;
		_boss.cast = true;

		//카오스 아이스퀸 테스트		
		
		_chaosIceQueenTrun = 0;
		_phase1BossCastIndex = _phase1SummonOrbCastIndex = 0;
		_boss.chaosIceQueenFire = true;
		for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
		{
			_vChaosIceQueen[i].count = _vChaosIceQueen[i].index = 0;
			_vChaosIceQueen[i].x = RND->range(200,1000);
			_vChaosIceQueen[i].y = RND->range(100, 700);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		//보스 초기화
		_boss.orbCast = false;
		_boss.cast = false;
		_phase1SummonOrbCast = false;
		//카오스 아이스 퀸 테스트				
		_boss.chaosIceQueenFire = false;
		for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
		{
			_vChaosIceQueen[i].isFire = false;
		}
	}
	//페이즈1 보스 아이들
	if (!_boss.phase && !_boss.cast)
	{
		//플레이어가 가운데 있을때
		if (_player.x >= 400 && _player.x <= 800)
		{
			_phase1BossIdleImage->setFrameX(0);
		}
		//플레이어가 오른쪽에 있을때
		else if (_player.x > 800)
		{
			_phase1BossIdleImage->setFrameX(1);
		}
		//플레이어가 왼쪽에 있을때
		else if (_player.x < 400)
		{
			_phase1BossIdleImage->setFrameX(2);
		}

		//윈드 이펙트 초기화
		_airSpinnerBurstCount = airSpinnerBurstIndex = 0;
	}
	

	//윈드 이펙트 업데이트
	if (_airSpinnerBurstIsStart)
	{
		_airSpinnerBurstImage->setFrameY(0);
		_airSpinnerBurstCount++;
		if (_airSpinnerBurstCount % 6 == 0)
		{
			airSpinnerBurstIndex++;
			if (airSpinnerBurstIndex >= _airSpinnerBurstImage->getMaxFrameX())
			{				
				airSpinnerBurstIndex = _airSpinnerBurstImage->getMaxFrameX();
				_airSpinnerBurstIsStart = false;
			}
			_airSpinnerBurstImage->setFrameX(airSpinnerBurstIndex);
		}
	}

	//페이즈1 보스 캐스트
	if (!_boss.phase)
	{
		//페이즈1 보스 캐스트 모션 업데이트
		if (_boss.cast)
		{
			_airSpinnerBurstIsStart = true;
			_phase1BossCastImage->setFrameY(0);
			_phase1BossCastCount++;
			if (_phase1BossCastCount % 7 == 0)
			{
				_phase1BossCastIndex++;
				//맥스는 6장인데 좀더 돌리는건 마지막 샷을 유지?
				if (_phase1BossCastIndex >= 12)			{

					_boss.cast = false;
				}
				_phase1BossCastImage->setFrameX(_phase1BossCastIndex);
			}
		}
		//페이즈1 서몬 슬램 캐스트
		if (_boss.slamCast)
		{
			_boss.ballCast = false;
			_boss.orbCast = false;
			_phase1SummonSlamCastImage->setFrameY(0);
			_phase1SummonSlamCastCount++;
			if (_phase1SummonSlamCastCount % 7 == 0)
			{
				_phase1SummonSlamCastIndex++;
				//5번째컷일때 스킬발사 
				//5번째컷이 발사이미지 이후론 똑같음
				if (_phase1SummonSlamCastIndex >= 5)
				{					
					_phase1SummonSlamCast = true;							
				}
				if (_phase1SummonSlamCastIndex >= _phase1SummonSlamCastImage->getMaxFrameX())
				{					
					_phase1SummonSlamCastIndex = _phase1SummonSlamCastImage->getMaxFrameX();
					_boss.slamCast = false;
					
				}
				_phase1SummonSlamCastImage->setFrameX(_phase1SummonSlamCastIndex);
			}
		}
		//페이즈1 서몬 발사 캐스트
		if (_boss.ballCast)
		{
			_boss.slamCast = false;
			_boss.orbCast = false;
			_phase1SummonBallCastImage->setFrameY(0);
			_phase1SummonBallCastCount++;
			if (_phase1SummonBallCastCount % 7 == 0)
			{
				_phase1SummonBallCastIndex++;
				//5번째컷일때 스킬발사 
				//5번째컷이 발사이미지 이후론 똑같음
				if (_phase1SummonBallCastIndex >= 5)
				{					
					_phase1SummonBallCast = true;		

				}
				if (_phase1SummonBallCastIndex >= _phase1SummonBallCastImage->getMaxFrameX())
				{
					_phase1SummonBallCastIndex = _phase1SummonBallCastImage->getMaxFrameX();					
					_boss.ballCast = false;
				}
				_phase1SummonBallCastImage->setFrameX(_phase1SummonBallCastIndex);
			}
		}
		//페이즈1 서몬 오브 캐스트
		if (_boss.orbCast)
		{
			_boss.slamCast = false;
			_boss.ballCast = false;
			_phase1SummonOrbCastImage->setFrameY(0);
			_phase1SummonOrbCastCount++;
			if (_phase1SummonOrbCastCount % 7 == 0)
			{
				_phase1SummonOrbCastIndex++;
				//5번째컷일때 스킬발사 
				//5번째컷이 발사이미지 이후론 똑같음
				if (_phase1SummonOrbCastIndex >= 5)
				{					
					_phase1SummonOrbCast = true;					
				}
				if (_phase1SummonOrbCastIndex >= _phase1SummonOrbCastImage->getMaxFrameX())
				{
					_phase1SummonOrbCastIndex = _phase1SummonOrbCastImage->getMaxFrameX();
					
					_boss.orbCast = false;
				}
				_phase1SummonOrbCastImage->setFrameX(_phase1SummonOrbCastIndex);
			}
		}
	}

	//카오스 오브 업데이트 
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		if (_vChaosOrb[i].isCast)
		{
			_vChaosOrb[i].rc = RectMakeCenter(_vChaosOrb[i].x, _vChaosOrb[i].y, _vChaosOrb[i].width, _vChaosOrb[i].height);
			_vChaosOrb[i].chaosOrbImage->setFrameY(0);
			_vChaosOrb[i].count++;
			if (_vChaosOrb[i].count % 5 == 0)
			{
				_vChaosOrb[i].index++;
				if (_vChaosOrb[i].index >= _vChaosOrb[i].chaosOrbImage->getMaxFrameX())
				{
					_vChaosOrb[i].index = 6;
				}
				_vChaosOrb[i].chaosOrbImage->setFrameX(_vChaosOrb[i].index);
			}
		}
	}


	//카오스 웨이브 업데이트
	if (_boss.chaosWaveFire && _phase1SummonSlamCast)
	{	//카운트 100/1000초
		_ChaosWaveTurn++;
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{				
			//턴
			if (_ChaosWaveTurn > i * 10 && _ChaosWaveTurn <= (i + 1) * 10 )
			{			
				_vChaosWave[i].isFire = true;				
			}

			//발사
			if (_vChaosWave[i].isFire)
			{				
				//케릭기준
				_vChaosWave[i].rc = RectMakeCenter(_vChaosWave[i].x + (cos(_vChaosWave[i].angle) * i * (_vChaosWave[i].width - 150)), _vChaosWave[i].y + (-sin(_vChaosWave[i].angle) * i * (_vChaosWave[i].width - 150)) , _vChaosWave[i].width, _vChaosWave[i].height);
				_vChaosWave[i].rc2 = RectMakeCenter(_vChaosWave[i].x + (cos(_vChaosWave[i].angle + 0.5f) * i * (_vChaosWave[i].width - 150)), _vChaosWave[i].y + (-sin(_vChaosWave[i].angle + 0.5f) * i * (_vChaosWave[i].width - 150)), _vChaosWave[i].width, _vChaosWave[i].height);
				_vChaosWave[i].rc3 = RectMakeCenter(_vChaosWave[i].x + (cos(_vChaosWave[i].angle - 0.5f) * i * (_vChaosWave[i].width - 150)), _vChaosWave[i].y + (-sin(_vChaosWave[i].angle - 0.5f) * i * (_vChaosWave[i].width - 150)), _vChaosWave[i].width, _vChaosWave[i].height);
				_vChaosWave[i].chaosWaveImage->setFrameY(0);
				_vChaosWave[i].count++;

				if (_vChaosWave[i].count % 4 == 0)
				{
					_vChaosWave[i].index++;
					if (_vChaosWave[i].index >= _vChaosWave[i].chaosWaveImage->getMaxFrameX())
					{
						_vChaosWave[i].isFire = false;																		
					}
				}
				_vChaosWave[i].chaosWaveImage->setFrameX(_vChaosWave[i].index);
			}
		}	
	}

	////카오스 웨이브 자동 초기 좌표 초기화
	//if (_vChaosWave[CHAOS_WAVE_MAX - 1].isFire)
	//{		
	//	//카오스 오브 테스트
	//	for (int i = 0; i < CHAOS_ORB; i++)
	//	{
	//		_vChaosOrb[i].isCast = false;
	//	}
	//}

	//카오스 볼 업데이트
	if (_boss.chaosBallFire && _phase1SummonBallCast)
	{
		_chaosBallTurn++;
		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{
			//턴
			if (_chaosBallTurn > i * 5 && _chaosBallTurn <= (i + 1) * 5)
			{
				_chaosBall[i].isFire = true;

				if (CHAOS_BALL_MAX - 1 == i)
					_chaosBallcoolDown = GetTickCount64();
			}

			//발사
			if (_chaosBall[i].isFire)
			{				
				_chaosBall[i].rc = RectMakeCenter(_chaosBall[i].x, _chaosBall[i].y, _chaosBall[i].width, _chaosBall[i].height);
				_chaosBall[i].x += cos((_ballAngleTurn  * i)) * _chaosBall[i].speed;
				_chaosBall[i].y += -sin((_ballAngleTurn  * i)) * _chaosBall[i].speed;

				_chaosBall[i].chaosBallImage->setFrameY(0);
				_chaosBall[i].count++;
				if (_chaosBall[i].count % 5 == 0)
				{
					_chaosBall[i].index++;
					if (_chaosBall[i].index >= _chaosBall[i].chaosBallImage->getMaxFrameX())
					{
						_chaosBall[i].index = 0;
					}
				}
				_chaosBall[i].chaosBallImage->setFrameX(_chaosBall[i].index);
			}
		}
	}

	//카오스볼 자동 초기 좌표 초기화
	if (_chaosBall[CHAOS_BALL_MAX - 1].isFire)
	{			
		//카오스 오브 테스트
		for (int i = 0; i < CHAOS_ORB; i++)
		{
			_vChaosOrb[i].isCast = false;
		}
		//카오스 볼 5초후 초기화	
		if (GetTickCount64() - _chaosBallcoolDown >= 3000)
		{
			_boss.ballCast = false;
			_phase1SummonBallCast = false;

			for (int i = 0; i < CHAOS_BALL_MAX; i++)
			{
				_chaosBall[i].isFire = false;
				_chaosBall[i].x = _boss.x;
				_chaosBall[i].y = _boss.y;		
				_chaosBallcoolDown = GetTickCount64();
			}			
		}
	}




	//메테오 
	//써클렌더 > 써클마지막되면 > 메테오발사 > 메테오써클에닿으면 폭발 > 폭발끝나면 전부 false	
	if (_boss.meteoStrikeFire)
	{
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{
			_meteoStrikeTurn++;
			if (_meteoStrikeTurn > i * 100 && _meteoStrikeTurn <= (i + 1) * 100)
			{
				_vCastCircle[i].isCast = true;
			}
			//써클 업데이트
			if (_vCastCircle[i].isCast)
			{
				_vCastCircle[i].rc = RectMakeCenter(_vCastCircle[i].x, _vCastCircle[i].y, _vCastCircle[i].width, _vCastCircle[i].height);
				_vCastCircle[i].castCirleImage->setFrameY(0);
				_vCastCircle[i].count++;
				if (_vCastCircle[i].count % 3 == 0)
				{
					_vCastCircle[i].index++;
					if (_vCastCircle[i].index >= _vCastCircle[i].castCirleImage->getMaxFrameX())
					{
						_vCastCircle[i].index = 19;
						_vMeteoStrike[i].isFire = true;
					}
					_vCastCircle[i].castCirleImage->setFrameX(_vCastCircle[i].index);
				}
			}
			//메테오 업데이트
			//메테오 발사
			if (_vMeteoStrike[i].isFire)
			{
				_vMeteoStrike[i].rc = RectMakeCenter(_vMeteoStrike[i].x, _vMeteoStrike[i].y, _vMeteoStrike[i].width, _vMeteoStrike[i].height);

				_vMeteoStrike[i].x += cos(_vMeteoStrike[i].angle) * _vMeteoStrike[i].speed;
				_vMeteoStrike[i].y += -sin(_vMeteoStrike[i].angle) * _vMeteoStrike[i].speed;
				_vMeteoStrike[i].skillCount++;
				_vMeteoStrike[i].meteoStrikeImage->setFrameY(0);
				if (_vMeteoStrike[i].skillCount % 8 == 0)
				{
					_vMeteoStrike[i].skillIndex++;
					if (_vMeteoStrike[i].skillIndex > 5)
					{
						_vMeteoStrike[i].skillIndex = 0;
					}
					_vMeteoStrike[i].meteoStrikeImage->setFrameX(_vMeteoStrike[i].skillIndex);
				}
			}
			//메테오 충돌
			if (_vMeteoStrike[i].isFire && _vMeteoStrike[i].rc.bottom >= _vMeteoStrike[i].range.y + 50)
			{
				_vMeteoStrike[i].isFire = false;
				_vCastCircle[i].isCast = false;
				_vMeteoStrike[i].isExplosion = true;				
			}

			//메테오 폭발
			if (_vMeteoStrike[i].isExplosion)
			{
				//폭발 이미지1
				_vMeteoStrike[i].ExplosionCount++;
				_vMeteoStrike[i].meteoStrikeExplosionImage->setFrameY(0);
				if (_vMeteoStrike[i].ExplosionCount % 8 == 0)
				{
					_vMeteoStrike[i].ExplosionIndex++;
					if (_vMeteoStrike[i].ExplosionIndex >= _vMeteoStrike[i].meteoStrikeExplosionImage->getMaxFrameX())
					{						
						//_vMeteoStrike[i].isExplosion = false;						
					}
					_vMeteoStrike[i].meteoStrikeExplosionImage->setFrameX(_vMeteoStrike[i].ExplosionIndex);
				}

				//폭발 이미지2
				_vMeteoStrike[i].Explosion2Count++;
				_vMeteoStrike[i].meteoStrikeExplosion2Image->setFrameY(0);
				if (_vMeteoStrike[i].Explosion2Count % 5 == 0)
				{
					_vMeteoStrike[i].Explosion2Index++;
					if (_vMeteoStrike[i].Explosion2Index >= _vMeteoStrike[i].meteoStrikeExplosion2Image->getMaxFrameX())
					{
						_vMeteoStrike[i].isExplosion = false;
					}
				}
				_vMeteoStrike[i].meteoStrikeExplosion2Image->setFrameX(_vMeteoStrike[i].Explosion2Index);				
			}
		}
	}

	//카오스 토네이도 업데이트
	if (_boss.chaosTornadoFire && _phase1SummonSlamCast)
	{	//카운트 100/1000초
		_chaosTornadoTurn++;
		for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
		{
			//턴
			if (_chaosTornadoTurn > i * 3 && _chaosTornadoTurn <= (i + 1) * 3)
			{
				_vChaosTornado[i].isFire = true;
			}

			//발사
			if (_vChaosTornado[i].isFire)
			{
				_vChaosTornado[i].rc = RectMakeCenter(_vChaosTornado[i].x , _vChaosTornado[i].y, _vChaosTornado[i].width, _vChaosTornado[i].height);
				//반시계 방향으로 코사인값/사인값줌
				_vChaosTornado[i].x += -cos((PI * 2 / 8 * i)) * _vChaosTornado[i].range;
				_vChaosTornado[i].y += sin((PI * 2 / 8 * i)) *  _vChaosTornado[i].range;
				_vChaosTornado[i].chaosTornadoImage->setFrameY(0);
				_vChaosTornado[i].count++;
				if (_vChaosTornado[i].count % 4 == 0)
				{
					_vChaosTornado[i].index++;
					if (_vChaosTornado[i].index >= _vChaosTornado[i].chaosTornadoImage->getMaxFrameX())
					{
						_vChaosTornado[i].isFire = false;
						if (_vChaosTornado[CHAOS_TORNADO_MAX-1].index >= _vChaosTornado[i].chaosTornadoImage->getMaxFrameX())
						{
							_boss.chaosTornadoFire = false;
						}
					}
				}
				_vChaosTornado[i].chaosTornadoImage->setFrameX(_vChaosTornado[i].index);
			}
		}
	}

	//카오스 아이스퀸 업데이트
	if (_boss.chaosIceQueenFire && _phase1SummonOrbCast)
	{	//카운트 10/1000초
		_chaosIceQueenTrun++;
		for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
		{
			//턴
			if (_chaosIceQueenTrun > i * 10 && _chaosIceQueenTrun <= (i + 1) * 10 )
			{
				_vChaosIceQueen[i].isFire = true;
			}

			//발사
			if (_vChaosIceQueen[i].isFire)
			{
				_vChaosIceQueen[i].rc = RectMakeCenter(_vChaosIceQueen[i].x, _vChaosIceQueen[i].y, _vChaosIceQueen[i].width, _vChaosIceQueen[i].height);
				
				//_vChaosIceQueen[i].x += cos(_vChaosIceQueen[i].angle);
				//_vChaosIceQueen[i].y += -sin(_vChaosIceQueen[i].angle);
				_vChaosIceQueen[i].chaosIceQueenImage->setFrameY(0);
				_vChaosIceQueen[i].count++;
				if (_vChaosIceQueen[i].count % 4 == 0)
				{
					_vChaosIceQueen[i].index++;
					if (_vChaosIceQueen[i].index >= _vChaosIceQueen[i].chaosIceQueenImage->getMaxFrameX())
					{
						_vChaosIceQueen[i].isFire = false;
						if (_vChaosIceQueen[CHAOS_ICEQUEEN_MAX - 1].index >= 10)
						{
							_boss.chaosIceQueenFire = false;
						}
						
					}
				}
				_vChaosIceQueen[i].chaosIceQueenImage->setFrameX(_vChaosIceQueen[i].index);
			}
		}
	}





	//플레이어 좌표 받아오기
	_player.x = _ptMouse.x;
	_player.y = _ptMouse.y;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);


	//테스트 업데이트
	//this->testUpdate();

}

void boss::render()
{
	//보스 렉트
	//Rectangle(getMemDC(), _boss.imageRc);
	//Rectangle(getMemDC(), _boss.rc);
	
	char str[128];
	wsprintf(str, "%d", _boss.chaosWavePatternCount);
	TextOut(getMemDC(), 20, 20, str, strlen(str));

	//페이즈1 보스 아이들
	if (!_boss.phase && !_boss.cast)
	{
		//보스 아이들
		_phase1BossIdleImage->frameRender(getMemDC(), _boss.imageRc.left, _boss.imageRc.top);
	}
	//서몬 아이들
	if (!_boss.phase && !_boss.cast)
	{
		//서몬 아이들
		_phase1SummonIdleImage->alphaRender(getMemDC(), _boss.imageRc.left - 88, _boss.imageRc.top - 162, 200);
	}

	//에어스핀 버스트 렌더
	if (_airSpinnerBurstIsStart)
	{
		_airSpinnerBurstImage->frameRender(getMemDC(), _boss.x - 135, _boss.y + 20);
	}


	//페이즈 1 보스 슬램 캐스트
	if (_boss.cast)
	{
		//보스 캐스트 모션
		_phase1BossCastImage->frameRender(getMemDC(), _boss.imageRc.left, _boss.imageRc.top + 12);

		if (!_boss.phase && _boss.slamCast)
		{
			//서몬 슬램 캐스트
			_phase1SummonSlamCastImage->alphaFrameRender(getMemDC(), _boss.imageRc.left - 88, _boss.imageRc.top - 162, 80);
		}
		//페이즈1 보스 볼 캐스트
		if (!_boss.phase && _boss.ballCast)
		{
			//서몬 볼 캐스트
			_phase1SummonBallCastImage->alphaFrameRender(getMemDC(), _boss.imageRc.left - 160, _boss.imageRc.top - 162, 80);
		}
		//페이즈1 보스 오브 캐스트
		if (!_boss.phase && _boss.orbCast)
		{
			//서몬 슬램 캐스트
			_phase1SummonOrbCastImage->alphaFrameRender(getMemDC(), _boss.imageRc.left - 88, _boss.imageRc.top - 162, 80);
		}
	}



	//카오스 레이저 렌더

	//카오스 웨이브 렌더
	if (_boss.chaosWaveFire)
	{
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{
			if (_vChaosWave[i].isFire)
			{
				//Rectangle(getMemDC(), _vChaosWave[i].rc);
				//Rectangle(getMemDC(), _vChaosWave[i].rc2);
				//Rectangle(getMemDC(), _vChaosWave[i].rc3);
				_vChaosWave[i].chaosWaveImage->frameRender(getMemDC(), _vChaosWave[i].rc.left, _vChaosWave[i].rc.top);
				_vChaosWave[i].chaosWaveImage->frameRender(getMemDC(), _vChaosWave[i].rc2.left, _vChaosWave[i].rc2.top);
				_vChaosWave[i].chaosWaveImage->frameRender(getMemDC(), _vChaosWave[i].rc3.left, _vChaosWave[i].rc3.top);
			}
		}
	}
	//카오스 볼 렌더
	if (_boss.chaosBallFire)
	{
		//카오스 볼
		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{			
			if (_chaosBall[i].isFire)
			{
				_chaosBall[i].chaosBallImage->rotateFrameRender(getMemDC(), _chaosBall[i].x, _chaosBall[i].y+100, _chaosBall[i].index, 0, _ballAngleTurn * i);
			}			
		}
	}
	//써클렌더 && 메테오 렌더 && 폭발 렌더
	if (_boss.meteoStrikeFire)
	{
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{
			//써클
			if (_vCastCircle[i].isCast)
			{
				//Rectangle(getMemDC(), _vCastCircle[i].rc);
				_vCastCircle[i].castCirleImage->alphaFrameRender(getMemDC(), _vCastCircle[i].rc.left, _vCastCircle[i].rc.top,150);
			}
			//메테오
			if (_vMeteoStrike[i].isFire)
			{
				//Rectangle(getMemDC(), _vMeteoStrike[i].rc);
				_vMeteoStrike[i].meteoStrikeImage->frameRender(getMemDC(), _vMeteoStrike[i].rc.left, _vMeteoStrike[i].rc.top);
			}

			//폭발 렌더
			if (_vMeteoStrike[i].isExplosion)
			{
				//메테오 폭발1 렌더
				_vMeteoStrike[i].meteoStrikeExplosionImage->frameRender(getMemDC(), _vMeteoStrike[i].range.x - 180, _vMeteoStrike[i].range.y - 250);

				//메테오 폭발2 렌더
				_vMeteoStrike[i].meteoStrikeExplosion2Image->frameRender(getMemDC(), _vMeteoStrike[i].range.x - 221, _vMeteoStrike[i].range.y - 260);
			}
		}
	}
	//카오스 토네이도 렌더
	if (_boss.chaosTornadoFire)
	{
		for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
		{
			if (_vChaosTornado[i].isFire)
			{
				_vChaosTornado[i].chaosTornadoImage->frameRender(getMemDC(), _vChaosTornado[i].rc.left, _vChaosTornado[i].rc.top);
			}
		}
	}
	//카오스 아이스퀸 렌더
	if (_boss.chaosIceQueenFire)
	{
		for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
		{
			if (_vChaosIceQueen[i].isFire)
			{
				_vChaosIceQueen[i].chaosIceQueenImage->frameRender(getMemDC(), _vChaosIceQueen[i].rc.left, _vChaosIceQueen[i].rc.top);
			}			
		}
	}
	//테스트 플레이어
	Rectangle(getMemDC(), _player.rc);

	//Q 디버깅
	if (KEYMANAGER->isToggleKey('Q'))
	{

		//페이즈1 보스 아이들
		_phase1BossIdleImage->frameRender(getMemDC(), 10, 10);
		//페이즈1 보스 피격
		_phase1BossHurtImage->frameRender(getMemDC(), 100, 10);
		//페이즈1 보스 슬램 캐스트
		_phase1BossCastImage->frameRender(getMemDC(), 200, 10);

		//페이즈1 서몬 아이들
		_phase1SummonIdleImage->alphaRender(getMemDC(), 300, 10, 150);
		//페이즈1 서몬 볼 캐스트
		_phase1SummonBallCastImage->alphaFrameRender(getMemDC(), 500, 10, 150);
		//페이즈1 서몬 슬램 캐스트
		_phase1SummonSlamCastImage->alphaFrameRender(getMemDC(), 700, 10, 150);
		//페이즈1 서몬 오브 캐스트
		_phase1SummonOrbCastImage->alphaFrameRender(getMemDC(), 900, 10, 150);

		//페이즈2 보스 진입
		_phase2BossStartImage->frameRender(getMemDC(), 10, 100);
		//페이즈2 보스 공격 1
		_phase2BossAttack1Image->frameRender(getMemDC(), 110, 100);
		//페이즈2 보스 공격 2
		_phase2BossAttack2Image->frameRender(getMemDC(), 210, 100);
		//페이즈2 보스 슬램 캐스트
		_phase2BossSlamCastImage->frameRender(getMemDC(), 310, 100);
		//페이즈2 보스 대쉬  그림자
		_phase2BossDashShadow3Image->frameRender(getMemDC(), _boss.imageRc.left - (_boss.width / 2), _boss.imageRc.top - (_boss.width / 2));
		_phase2BossDashShadow2Image->frameRender(getMemDC(), _boss.imageRc.left - (_boss.width / 2), _boss.imageRc.top - (_boss.width / 2));
		_phase2BossDashShadow1Image->frameRender(getMemDC(), _boss.imageRc.left - (_boss.width / 2), _boss.imageRc.top - (_boss.width / 2));
		//페이즈2 보스 대쉬
		_phase2BossDashImage->frameRender(getMemDC(), _boss.imageRc.left - (_boss.width / 2), _boss.imageRc.top - (_boss.width / 2));

		//서클 캐스트
		for (int i = 0; i < 3; i++)
		{
			if (_vCastCircle[i].isCast)
			{
				_vCastCircle[i].castCirleImage->frameRender(getMemDC(), _vCastCircle[i].rc.left, _vCastCircle[i].rc.top);
			}
		}

		//메테오 렌더
		for (int i = 0; i < METEO_STRIKE_MAX; i++)
		{
			if (_vMeteoStrike[i].isFire)
			{
				//Rectangle(memDC, _meteoStrike.rc);
				_vMeteoStrike[i].meteoStrikeImage->frameRender(getMemDC(), _vMeteoStrike[i].rc.left, _vMeteoStrike[i].rc.top);
			}

			//메테오 폭발 렌더
			if (_vMeteoStrike[i].isExplosion)
			{
				_vMeteoStrike[i].meteoStrikeExplosionImage->frameRender(getMemDC(), _vMeteoStrike[i].range.x - 180, _vMeteoStrike[i].range.y - 250);
				//메테오 폭발2 렌더
				_vMeteoStrike[i].meteoStrikeExplosion2Image->frameRender(getMemDC(), _vMeteoStrike[i].range.x, _vMeteoStrike[i].range.y);
			}

		}

	

		//카오스 레이저
		_chaosLaser.chaosImage->render(getMemDC(), 100, 700, 0,0, _chaosLaser.fire, 0);

		//카오스 웨이브
		for (int i = 0; i < CHAOS_WAVE_MAX; i++)
		{
			_vChaosWave[i].chaosWaveImage->frameRender(getMemDC(), _vChaosWave[i].x, _vChaosWave[i].y);
		}
		
		//카오스 볼
		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{
			_chaosBall[i].chaosBallImage->frameRender(getMemDC(), _chaosBall[i].x, _chaosBall[i].y);
		}
	

	}

	//카오스 서클 렌더 (항상 맨위에 업데이트 되게 마지막에 렌더하자)
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		if (_vChaosOrb[i].isCast)
		{
			_vChaosOrb[i].chaosOrbImage->frameRender(getMemDC(), _vChaosOrb[i].rc.left, _vChaosOrb[i].rc.top+100);
		}
	}
	
}
/////////////////////////////////////////////렌더 끝








//테스트 방향
void boss::testDirection()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_testDirection = TESTBOTTOM;	
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_testDirection = TESTTOP;	
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_testDirection = TESTRIGHT;		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_testDirection = TESTLEFT;		
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{		
		_player.y += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{		
		_player.y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{		
		_player.x += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{		
		_player.x -= 3;
	}
}
//테스트 업데이트
void boss::testUpdate()
{

	this->testDirection();
	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.width, _boss.height);
	_boss.imageRc = RectMakeCenter(_boss.x, _boss.y, _boss.imageWidth, _boss.imageHeight);

	//페이즈1 보스 아이들
	//_phase1BossIdleImage->setFrameY(0);
	//_phase1BossIdleCount++;
	//if (_phase1BossIdleCount % 10 == 0)
	//{
	//	_phase1BossIdleIndex++;
	//	if (_phase1BossIdleIndex >= 3)
	//	{
	//		_phase1BossIdleIndex = 0;
	//	}
	//	_phase1BossIdleImage->setFrameX(_phase1BossIdleIndex);
	//}

	//페이즈1 보스 볼 캐스트
	_phase1SummonBallCastImage->setFrameY(0);
	_phase1SummonBallCastCount++;
	if (_phase1SummonBallCastCount % 10 == 0)
	{
		_phase1SummonBallCastIndex++;
		if (_phase1SummonBallCastIndex >= 6)
		{
			_phase1SummonBallCastIndex = 0;
		}
		_phase1SummonBallCastImage->setFrameX(_phase1SummonBallCastIndex);
	}

	//페이즈1 보스 피격
	//오른쪽피격 = 0
	//왼쪽피격 = 1
	_phase1BossHurtImage->setFrameY(1);
	_phase1BossHurtCount++;
	if (_phase1BossHurtCount % 10 == 0)
	{
		_phase1BossHurtIndex++;
		if (_phase1BossHurtIndex >= 5)
		{
			_phase1BossHurtIndex = 0;
		}
		_phase1BossHurtImage->setFrameX(_phase1BossHurtIndex);
	}


	//페이즈1 보스 슬램캐스트
	_phase1BossCastImage->setFrameY(0);
	_phase1BossCastCount++;
	if (_phase1BossCastCount % 10 == 0)
	{
		_phase1BossCastIndex++;
		if (_phase1BossCastIndex >= 6)
		{
			_phase1BossCastIndex = 0;
		}
		_phase1BossCastImage->setFrameX(_phase1BossCastIndex);
	}

	//페이즈1 서몬 슬램 캐스트
	_phase1SummonSlamCastImage->setFrameY(0);
	_phase1SummonSlamCastCount++;
	if (_phase1SummonSlamCastCount % 10 == 0)
	{
		_phase1SummonSlamCastIndex++;
		if (_phase1SummonSlamCastIndex >= 6)
		{
			_phase1SummonSlamCastIndex = 0;
		}
		_phase1SummonSlamCastImage->setFrameX(_phase1SummonSlamCastIndex);
	}

	//페이즈1 서몬 오브 캐스트
	_phase1SummonOrbCastImage->setFrameY(0);
	_phase1SummonOrbCastCount++;
	if (_phase1SummonOrbCastCount % 10 == 0)
	{
		_phase1SummonOrbCastIndex++;
		if (_phase1SummonOrbCastIndex >= 6)
		{
			_phase1SummonOrbCastIndex = 0;
		}
		_phase1SummonOrbCastImage->setFrameX(_phase1SummonOrbCastIndex);
	}

	//페이즈2 보스 시작 이미지
	_phase2BossStartImage->setFrameY(0);
	_phase2BossStartCount++;
	if (_phase2BossStartCount % 10 == 0)
	{
		_phase2BossStartIndex++;
		if (_phase2BossStartIndex >= 20)
		{
			_phase2BossStartIndex = 0;
		}
		_phase2BossStartImage->setFrameX(_phase2BossStartIndex);
	}

	//페이즈 2 보스 공격 1
	_phase2BossAttack1Image->setFrameY(_testDirection);
	_phase2BossAttack1Count++;
	if (_phase2BossAttack1Count % 10 == 0)
	{
		_phase2BossAttack1Index++;
		if (_phase2BossAttack1Index >= 7)
		{
			_phase2BossAttack1Index = 0;
		}
		_phase2BossAttack1Image->setFrameX(_phase2BossAttack1Index);
	}

	//페이즈 2 보스 공격 2
	_phase2BossAttack2Image->setFrameY(_testDirection);
	_phase2BossAttack2Count++;
	if (_phase2BossAttack2Count % 10 == 0)
	{
		_phase2BossAttack2Index++;
		if (_phase2BossAttack2Index >= 6)
		{
			_phase2BossAttack2Index = 0;
		}
		_phase2BossAttack2Image->setFrameX(_phase2BossAttack2Index);
	}

	//페이즈2 보스 슬램캐스트
	_phase2BossSlamCastImage->setFrameY(0);
	_phase2BossSlamCastCount++;
	if (_phase2BossSlamCastCount % 10 == 0)
	{
		_phase2BossSlamCastIndex++;
		if (_phase2BossSlamCastIndex >= 6)
		{
			_phase2BossSlamCastIndex = 0;
		}
		_phase2BossSlamCastImage->setFrameX(_phase2BossSlamCastIndex);
	}

	//페이즈 2 보스 대쉬
	_phase2BossDashImage->setFrameY(_testDirection);
	_phase2BossDashCount++;
	if (_phase2BossDashCount % 5 == 0)
	{
		_phase2BossDashIndex++;
		if (_phase2BossDashIndex >= 10)
		{
			_phase2BossDashIndex = 0;
		}
		_phase2BossDashImage->setFrameX(_phase2BossDashIndex);
	}
	//페이즈 2 보스 그림자1
	_phase2BossDashShadow1Image->setFrameY(_testDirection);
	_phase2BossDashShoadow1Count++;
	if (_phase2BossDashShoadow1Count % 5 == 0)
	{
		_phase2BossDashShoadow1Index++;
		if (_phase2BossDashShoadow1Index >= 10)
		{
			_phase2BossDashShoadow1Index = 0;
		}
		_phase2BossDashShadow1Image->setFrameX(_phase2BossDashShoadow1Index - 1);
	}
	//페이즈 2 보스 그림자2
	_phase2BossDashShadow2Image->setFrameY(_testDirection);
	_phase2BossDashShoadow2Count++;
	if (_phase2BossDashShoadow2Count % 5 == 0)
	{
		_phase2BossDashShoadow2Index++;
		if (_phase2BossDashShoadow2Index >= 10)
		{
			_phase2BossDashShoadow2Index = 0;
		}
		_phase2BossDashShadow2Image->setFrameX(_phase2BossDashShoadow2Index - 2);
	}
	//페이즈 2 보스 그림자3
	_phase2BossDashShadow3Image->setFrameY(_testDirection);
	_phase2BossDashShoadow3Count++;
	if (_phase2BossDashShoadow3Count % 5 == 0)
	{
		_phase2BossDashShoadow3Index++;
		if (_phase2BossDashShoadow3Index >= 10)
		{
			_phase2BossDashShoadow3Index = 0;
		}
		_phase2BossDashShadow3Image->setFrameX(_phase2BossDashShoadow3Index - 3);
	}

	//스킬 테스트
	//서클 캐스트
	for (int i = 0; i < 3; i++)
	{
		_vCastCircle[i].castCirleImage->setFrameY(0);
		_vCastCircle[i].count++;
		if (_vCastCircle[i].count % 5 == 0)
		{
			_vCastCircle[i].index++;
			if (_vCastCircle[i].index >= 20)
			{
				_vCastCircle[i].index = 0;
			}
			_vCastCircle[i].castCirleImage->setFrameX(_vCastCircle[i].index);
		}
	}


	//메테오 스킬
	//if (KEYMANAGER->isOnceKeyDown('R') && !_meteoStrike.isFire)
	//{
	//
	//	_meteoStrike.x = 1000;
	//	_meteoStrike.y = -200.f;
	//	_meteoStrike.skillCount = _meteoStrike.skillIndex = 0;
	//	//발사
	//	_meteoStrike.isFire = true;
	//	//위치저장
	//	_meteoStrike.range.x = _castCircle.x;
	//	_meteoStrike.range.y = _castCircle.y;
	//	//각도 저장
	//	_meteoStrike.angle = getAngle(_meteoStrike.x, _meteoStrike.y, _castCircle.x, _castCircle.y);
	//}
	////메테오 발사
	//if (_meteoStrike.isFire)
	//{
	//	_meteoStrike.rc = RectMakeCenter(_meteoStrike.x, _meteoStrike.y, _meteoStrike.width, _meteoStrike.height);
	//
	//	_meteoStrike.x += cos(_meteoStrike.angle) * _meteoStrike.speed;
	//	_meteoStrike.y += -sin(_meteoStrike.angle) * _meteoStrike.speed;
	//	_meteoStrike.skillCount++;
	//	_meteoStrike.meteoStrikeImage->setFrameY(0);
	//	if (_meteoStrike.skillCount % 8 == 0)
	//	{
	//		_meteoStrike.skillIndex++;
	//		if (_meteoStrike.skillIndex > 5)
	//		{
	//			_meteoStrike.skillIndex = 0;
	//		}
	//		_meteoStrike.meteoStrikeImage->setFrameX(_meteoStrike.skillIndex);
	//	}
	//}
	//
	////메테오 폭발
	//if (_meteoStrike.isExplosion)
	//{
	//	_meteoStrike.ExplosionCount++;
	//	_meteoStrike.meteoStrikeExplosionImage->setFrameY(0);
	//	if (_meteoStrike.ExplosionCount % 6 == 0)
	//	{
	//		_meteoStrike.ExplosionIndex++;
	//		if (_meteoStrike.ExplosionIndex > 6)
	//		{
	//			_meteoStrike.ExplosionIndex = 0;
	//			_meteoStrike.isExplosion = false;
	//		}
	//		_meteoStrike.meteoStrikeExplosionImage->setFrameX(_meteoStrike.ExplosionIndex);
	//	}
	//}
	////메테오 충돌
	//if (_meteoStrike.isFire == true && _meteoStrike.rc.bottom >= _meteoStrike.range.y + 50)
	//{
	//	_meteoStrike.isFire = false;
	//	_meteoStrike.isExplosion = true;
	//}

	//레이저
	_chaosLaser.fire += 30;
	if (_chaosLaser.fire >= 1500)
	{
		_chaosLaser.fire = 0;
	}

	//카오스 웨이브
	for (int i = 0; i < CHAOS_WAVE_MAX; i++)
	{
		_vChaosWave[i].chaosWaveImage->setFrameY(0);
		_vChaosWave[i].count++;
		if (_vChaosWave[i].count % 10 == 0)
		{
			_vChaosWave[i].index++;
			if (_vChaosWave[i].index >= 9)
			{
				_vChaosWave[i].index = 0;
			}
		}
		_vChaosWave[i].chaosWaveImage->setFrameX(_vChaosWave[i].index);
	}

	//카오스 볼
	for (int i = 0; i < CHAOS_BALL_MAX; i++)
	{
		_chaosBall[i].chaosBallImage->setFrameY(0);
		_chaosBall[i].count++;
		if (_chaosBall[i].count % 10 == 0)
		{
			_chaosBall[i].index++;
			if (_chaosBall[i].index >= 6)
			{
				_chaosBall[i].index = 0;
			}
		}
		_chaosBall[i].chaosBallImage->setFrameX(_chaosBall[i].index);
	}
}


//카오스 웨이브 실행
void boss::chaosWaveAction()
{
	//초기화 

	//보스 초기화
	_boss.slamCast = false;
	_boss.cast = false;
	_phase1SummonSlamCast = false;
	//카오스 웨이브 테스트				
	_boss.chaosWaveFire = false;
	for (int i = 0; i < CHAOS_WAVE_MAX; i++)
	{
		_vChaosWave[i].isFire = false;
	}

	//실행 

	//보스 캐스트 1개만 실행
	//_boss.ballCast = false;
	//_boss.orbCast = false;
	_boss.slamCast = true;
	_boss.cast = true;

	//카오스 웨이브 테스트
	_ChaosWaveTurn = 0;
	_phase1BossCastIndex = _phase1SummonSlamCastIndex = 0;
	_boss.chaosWaveFire = true;
	for (int i = 0; i < CHAOS_WAVE_MAX; i++)
	{
		_vChaosWave[i].count = _vChaosWave[i].index = 0;
		//플레이어 좌표 받아오기			
		_vChaosWave[i].x = _boss.x;
		_vChaosWave[i].y = _boss.y;
		_vChaosWave[i].angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);
	}
}
//카오스 웨이브 중지
void boss::chaosWaveStop()
{
	//보스 초기화
	_boss.slamCast = false;


	//카오스 웨이브 테스트				
	_boss.chaosWaveFire = false;
	for (int i = 0; i < CHAOS_WAVE_MAX; i++)
	{
		_vChaosWave[i].isFire = false;
	}
	//카오스 오브 테스트
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		_vChaosOrb[i].isCast = false;
	}

	//서몬 슬램 초기화
	_phase1SummonSlamCast = false;
}

//카오스 볼 실행
void boss::chaosBallAction()
{
	//초기화

	//보스 초기화		
	_boss.ballCast = false;
	_boss.cast = false;
	_phase1SummonBallCast = false;
	//카오스 볼테스트
	_boss.chaosBallFire = false;

	for (int i = 0; i < CHAOS_BALL_MAX; i++)
	{
		_chaosBall[i].isFire = false;
		_chaosBall[i].x = _boss.x;
		_chaosBall[i].y = _boss.y;
		_chaosBallcoolDown = GetTickCount64();
	}
	//카오스 오브 테스트
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		_vChaosOrb[i].isCast = false;
	}

	//실행

	//보스 캐스트 1개만 실행
	//_boss.slamCast = false;		
	//_boss.orbCast = false;
	_boss.ballCast = true;
	_boss.cast = true;

	//카오스볼 테스트		
	_phase1BossCastIndex = _phase1SummonBallCastIndex = 0;
	_chaosBallTurn = 0;
	_boss.chaosBallFire = true;
	//페이즈 2일때 속도 바꾸기
	if (_boss.phase)
	{
		for (int i = 0; i < CHAOS_BALL_MAX; i++)
		{
			_chaosBall[i].speed = RND->range(5, 12);
		}
	}
	//카오스 오브 테스트
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		_vChaosOrb[i].count = _vChaosOrb[i].index = 0;
		_vChaosOrb[i].x = _boss.x;
		_vChaosOrb[i].y = _boss.y;
		_vChaosOrb[i].isCast = true;
	}
}
//카오스 볼 중지
void boss::chaosBallStop()
{
	//보스 초기화
	_boss.ballCast = false;

	//카오스 볼테스트
	_boss.chaosBallFire = false;
	for (int i = 0; i < CHAOS_BALL_MAX; i++)
	{
		_chaosBall[i].isFire = false;
	}
	//카오스 오브 테스트
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		_vChaosOrb[i].isCast = false;
	}

	// 서몬 볼 초기화
	_phase1SummonBallCast = false;
}
//메테오 실행
void boss::meteoStrikeAction()
{
	//초기화

	//보스 초기화
	_boss.orbCast = false;
	_boss.cast = false;
	_phase1SummonOrbCast = false;
	//메테오 테스트
	_boss.meteoStrikeFire = false;
	for (int i = 0; i < METEO_STRIKE_MAX; i++)
	{
		_vCastCircle[i].count = _vCastCircle[i].index = 0;
		_vCastCircle[i].isCast = false;
		_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
		_vMeteoStrike[i].isFire = false;
		_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
		_vMeteoStrike[i].isExplosion = false;
	}

	//실행

	//보스 캐스트 1개만 실행
	//_boss.slamCast = false;
	//_boss.ballCast = false;
	_boss.orbCast = true;
	_boss.cast = true;

	//메테오 저장 테스트	
	_meteoStrikeTurn = 0;
	_phase1BossCastIndex = _phase1SummonOrbCastIndex = 0;
	_boss.meteoStrikeFire = true;
	for (int i = 0; i < METEO_STRIKE_MAX; i++)
	{
		//_vCastCircle[i].x = _vMeteoStrike[i].range.x = 200 + (i * 200);
		//_vCastCircle[i].y = _vMeteoStrike[i].range.y = 400;			
		_vCastCircle[i].x = _vMeteoStrike[i].range.x = RND->range(1100);
		_vCastCircle[i].y = _vMeteoStrike[i].range.y = RND->range(700);
		_vMeteoStrike[i].x = _vCastCircle[i].x + 400;
		_vMeteoStrike[i].y = -300;
		_vCastCircle[i].count = _vCastCircle[i].index = 0;
		_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
		_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
		_vMeteoStrike[i].Explosion2Count = _vMeteoStrike[i].Explosion2Index = 0;
		//각도 저장
		_vMeteoStrike[i].angle = getAngle(_vMeteoStrike[i].x, _vMeteoStrike[i].y, _vCastCircle[i].x, _vCastCircle[i].y);
	}
}
//메테오 중지
void boss::meteoStrikeStop()
{
	//보스 초기화
	_boss.orbCast = false;
	_meteoStrikeTurn = 0;
	_boss.meteoStrikeFire = false;
	for (int i = 0; i < METEO_STRIKE_MAX; i++)
	{
		_vCastCircle[i].count = _vCastCircle[i].index = 0;
		_vCastCircle[i].isCast = false;
		_vMeteoStrike[i].skillCount = _vMeteoStrike[i].skillIndex = 0;
		_vMeteoStrike[i].isFire = false;
		_vMeteoStrike[i].ExplosionCount = _vMeteoStrike[i].ExplosionIndex = 0;
		_vMeteoStrike[i].isExplosion = false;
	}
	// 서몬 오브 초기화
	_phase1SummonOrbCast = false;
}
//카오스 토네이도 실행
void boss::chaosTornadoAction()
{
	//초기화

	//보스 초기화
	_boss.slamCast = false;
	_boss.cast = false;
	_phase1SummonSlamCast = false;
	//카오스 토네이도 테스트				
	_boss.chaosTornadoFire = false;
	for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
	{
		_vChaosTornado[i].isFire = false;
	}

	//실행

	//보스 캐스트 1개만 실행
	//_boss.ballCast = false;
	//_boss.orbCast = false;
	_boss.slamCast = true;
	_boss.cast = true;
	//카오스 토네이도 테스트			
	_chaosTornadoTurn = 0;
	_phase1BossCastIndex = _phase1SummonSlamCastIndex = 0;
	_boss.chaosTornadoFire = true;
	for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
	{
		_vChaosTornado[i].count = _vChaosTornado[i].index = 0;
		_vChaosTornado[i].x = _boss.x;
		_vChaosTornado[i].y = _boss.y;
		_vChaosTornado[i].angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);
	}
	//카오스 오브 테스트
}
//카오스 토네이도 중지
void boss::ChaosTornadoStop()
{
	//보스 초기화
	_boss.slamCast = false;

	//카오스 토네이도 테스트				
	_boss.chaosTornadoFire = false;
	for (int i = 0; i < CHAOS_TORNADO_MAX; i++)
	{
		_vChaosTornado[i].isFire = false;
	}
	//카오스 오브 테스트
	for (int i = 0; i < CHAOS_ORB; i++)
	{
		_vChaosOrb[i].isCast = false;
	}

	//서몬 슬램 초기화
	_phase1SummonSlamCast = false;
}
//카오스 아이스퀸 실행
void boss::chaosIceQueenAction()
{
	//초기화
//보스 초기화
	_boss.orbCast = false;
	_boss.cast = false;
	_phase1SummonOrbCast = false;
	//카오스 아이스 퀸 테스트				
	_boss.chaosIceQueenFire = false;
	for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
	{
		_vChaosIceQueen[i].isFire = false;
	}


	//실행

	//보스 캐스트 1개만 실행
	//_boss.slamCast = false;
	//_boss.ballCast = false;
	_boss.orbCast = true;
	_boss.cast = true;

	//카오스 아이스퀸 테스트		

	_chaosIceQueenTrun = 0;
	_phase1BossCastIndex = _phase1SummonOrbCastIndex = 0;
	_boss.chaosIceQueenFire = true;
	for (int i = 0; i < CHAOS_ICEQUEEN_MAX; i++)
	{
		_vChaosIceQueen[i].count = _vChaosIceQueen[i].index = 0;
		_vChaosIceQueen[i].x = RND->range(200, 1000);
		_vChaosIceQueen[i].y = RND->range(100, 700);
	}
}
