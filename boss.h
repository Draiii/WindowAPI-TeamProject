#pragma once
#include "gameNode.h"
#define CHAOS_ORB 1
#define CHAOS_BALL_MAX 24
#define CHAOS_WAVE_MAX 10
#define METEO_STRIKE_MAX 7
#define CHAOS_TORNADO_MAX 8
#define CHAOS_ICEQUEEN_MAX 20




//방향 테스트
enum tagTestdirection
{
	TESTBOTTOM,
	TESTTOP,
	TESTRIGHT,
	TESTLEFT,
};

//자세
enum idle
{
	IDLE,
	MOVE,
	ATTACK,
	CAST
};
//방향
enum direction
{
	BOTTOM,
	TOP,
	RIGHT,
	LEFT,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTTOP,
	RIGHTBOTTOM
};
//보스
struct tagBoss
{
	RECT rc;
	RECT imageRc;
	POINT crossHair;
	int width, height;
	int imageWidth, imageHeight;
	int idle;
	int direction;
	float moveSpeed;
	float dashSpeed;
	float x, y;
	float dashX, dashY;
	float angle;
	float rangeX;
	float rangeY;
	bool dash;
	bool attack;
	bool cast;
	bool slamCast;
	bool ballCast;
	bool orbCast;
	//카오스 웨이브 발사
	bool chaosWaveFire;
	int chaosWavePatternCount;
	//카오스 볼 발사
	bool chaosBallFire;
	int chaosBallPatternCount;
	//메테오 발사
	bool meteoStrikeFire;
	int meteoStrikePatternCount;
	//카오스 토네이도 발사
	bool chaosTornadoFire;
	int chaosTornadoPatternCount;
	//카오스 아이스퀸 발사
	bool chaosIceQueenFire;
	int  chaosIceQueenPatternCount;

	//보스 페이즈 false = 1페이즈 true = 2페이즈
	bool phase;
};
//테스트 플레이어
struct tagTestplayer
{
	RECT rc;
	float x, y, width, height;	
};

//**********************스킬**********************
//메테오 써클
struct tagCastCircle
{
	RECT rc;
	image* castCirleImage;
	float x, y, width, height;
	int count, index;
	bool isCast;
};
//카오스 오브 써클
struct tagChaosOrb
{
	RECT rc;
	image* chaosOrbImage;
	float x, y, width, height;
	int count, index;
	bool isCast;
};

//메테오 스킬
struct tagMeteoStrikeSkill
{
	RECT rc;
	RECT ExplosionRc;
	image* meteoStrikeImage;
	image* meteoStrikeExplosionImage;
	image* meteoStrikeExplosion2Image;
	float x, y;
	float width, height;
	float angle;
	float speed;
	int skillCount;
	int skillIndex;
	int ExplosionCount;
	int ExplosionIndex;
	int Explosion2Count;
	int Explosion2Index;
	int coolDownTime;
	POINT range;
	bool isFire;
	bool isExplosion;
};
//카오스 스킬
struct tagChaosSkill
{

	image* chaosImage;
	float x, y, width, height;
	float angle;
	int count, index;
	float fire;
	bool isFire;
};
//카오스 웨이브 스킬
struct tagChaosWaveSkill
{
	RECT rc;
	RECT rc2;
	RECT rc3;
	image* chaosWaveImage;
	float x, y, width, height;
	float angle;
	int count, index;	
	bool isFire;
};
//카오스 볼 스킬
struct tagChaosBallSkill
{
	RECT rc;
	image* chaosBallImage;
	float x, y, width, height;
	float angle;
	float speed;
	int count, index;
	bool isFire;
};
//카오스 토네이도 스킬
struct tagChaosTornadoSkill
{
	RECT rc;
	image* chaosTornadoImage;
	float x, y, width, height;
	float angle;
	float range;
	int count, index;
	bool isFire;
};
//카오스 아이스퀸 스킬
struct tagChaosIceQueenSkill
{
	RECT rc;
	image* chaosIceQueenImage;
	float x, y, width, height;
	float angle;
	int count, index;
	bool isFire;
};


class boss : 	public gameNode
{
private:	
	//테스트
	int _testDirection;

	//플레이어
	tagTestplayer _player;
	//보스
	tagBoss _boss;
	vector <tagCastCircle> _vCastCircle;
	vector <tagChaosOrb> _vChaosOrb;
	tagChaosSkill _chaosLaser;
	vector <tagChaosWaveSkill> _vChaosWave;
	int _ChaosWaveTurn;
	tagChaosBallSkill _chaosBall[CHAOS_BALL_MAX];
	int _chaosBallTurn;
	float _ballAngleTurn;
	int _chaosBallcoolDown;
	vector <tagMeteoStrikeSkill> _vMeteoStrike;
	int _meteoStrikeTurn;
	vector <tagChaosTornadoSkill> _vChaosTornado;
	int _chaosTornadoTurn;
	vector < tagChaosIceQueenSkill> _vChaosIceQueen;
	int _chaosIceQueenTrun;



	//페이즈1 보스 아이들
	image* _phase1BossIdleImage;
	int _phase1BossIdleCount, _phase1BossIdleIndex;
	//에어스핀 버스트
	image* _airSpinnerBurstImage;
	int _airSpinnerBurstCount, airSpinnerBurstIndex;
	bool _airSpinnerBurstIsStart;
	//페이즈1 보스 피격
	image* _phase1BossHurtImage;
	int _phase1BossHurtCount, _phase1BossHurtIndex;
	//페이즈1 보스 캐스트
	image* _phase1BossCastImage;
	int _phase1BossCastCount, _phase1BossCastIndex;
	//페이즈1 서몬 아이들
	image* _phase1SummonIdleImage;
	//페이즈1 서몬 볼 캐스트
	image* _phase1SummonBallCastImage;
	int _phase1SummonBallCastCount, _phase1SummonBallCastIndex;
	bool _phase1SummonBallCast;
	//페이즈1 서몬 슬램 캐스트
	image* _phase1SummonSlamCastImage;
	int _phase1SummonSlamCastCount, _phase1SummonSlamCastIndex;
	bool _phase1SummonSlamCast;
	//페이즈1 서몬 오브 캐스트
	image* _phase1SummonOrbCastImage;
	int _phase1SummonOrbCastCount, _phase1SummonOrbCastIndex;
	bool _phase1SummonOrbCast;
	

	//페이즈2시작시 변신 이미지
	image* _phase2BossStartImage;
	int _phase2BossStartCount, _phase2BossStartIndex;
	
	//페이즈2 보스 공격1
	image* _phase2BossAttack1Image;
	int _phase2BossAttack1Count, _phase2BossAttack1Index;

	//페이즈2 보스 공격2
	image* _phase2BossAttack2Image;
	int _phase2BossAttack2Count, _phase2BossAttack2Index;
	
	//페이즈2 보스 슬램 캐스트
	image* _phase2BossSlamCastImage;
	int _phase2BossSlamCastCount, _phase2BossSlamCastIndex;

	//페이즈2 보스 대쉬
	image* _phase2BossDashImage;
	int _phase2BossDashCount, _phase2BossDashIndex;

	//페이즈2 보스 대쉬 그림자
	image* _phase2BossDashShadow1Image;
	image* _phase2BossDashShadow2Image;
	image* _phase2BossDashShadow3Image;
	int _phase2BossDashShoadow1Count, _phase2BossDashShoadow1Index;
	int _phase2BossDashShoadow2Count, _phase2BossDashShoadow2Index;
	int _phase2BossDashShoadow3Count, _phase2BossDashShoadow3Index;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	//테스트 방향
	void testDirection();
	//테스트 업데이트
	void testUpdate();

	//카오스 웨이브 실행
	void chaosWaveAction();
	//카오스 웨이브 중지
	void chaosWaveStop();
	//카오스 볼 실행
	void chaosBallAction();
	//카오스 볼 중지
	void chaosBallStop();
	//메테오 실행
	void meteoStrikeAction();
	//메테오 중지
	void meteoStrikeStop();
	//카오스 토네이도 실행
	void chaosTornadoAction();
	//카오스 토네이도 중지
	void ChaosTornadoStop();
	//카오스 아이스퀸 실행
	void chaosIceQueenAction();
	 
	boss() {}
	~boss() {}
};

