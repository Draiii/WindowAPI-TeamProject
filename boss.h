#pragma once
#include "gameNode.h"
#define CHAOS_ORB 1
#define CHAOS_BALL_MAX 24
#define CHAOS_WAVE_MAX 10
#define METEO_STRIKE_MAX 7
#define CHAOS_TORNADO_MAX 8
#define CHAOS_ICEQUEEN_MAX 20




//���� �׽�Ʈ
enum tagTestdirection
{
	TESTBOTTOM,
	TESTTOP,
	TESTRIGHT,
	TESTLEFT,
};

//�ڼ�
enum idle
{
	IDLE,
	MOVE,
	ATTACK,
	CAST
};
//����
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
//����
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
	//ī���� ���̺� �߻�
	bool chaosWaveFire;
	int chaosWavePatternCount;
	//ī���� �� �߻�
	bool chaosBallFire;
	int chaosBallPatternCount;
	//���׿� �߻�
	bool meteoStrikeFire;
	int meteoStrikePatternCount;
	//ī���� ����̵� �߻�
	bool chaosTornadoFire;
	int chaosTornadoPatternCount;
	//ī���� ���̽��� �߻�
	bool chaosIceQueenFire;
	int  chaosIceQueenPatternCount;

	//���� ������ false = 1������ true = 2������
	bool phase;
};
//�׽�Ʈ �÷��̾�
struct tagTestplayer
{
	RECT rc;
	float x, y, width, height;	
};

//**********************��ų**********************
//���׿� ��Ŭ
struct tagCastCircle
{
	RECT rc;
	image* castCirleImage;
	float x, y, width, height;
	int count, index;
	bool isCast;
};
//ī���� ���� ��Ŭ
struct tagChaosOrb
{
	RECT rc;
	image* chaosOrbImage;
	float x, y, width, height;
	int count, index;
	bool isCast;
};

//���׿� ��ų
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
//ī���� ��ų
struct tagChaosSkill
{

	image* chaosImage;
	float x, y, width, height;
	float angle;
	int count, index;
	float fire;
	bool isFire;
};
//ī���� ���̺� ��ų
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
//ī���� �� ��ų
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
//ī���� ����̵� ��ų
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
//ī���� ���̽��� ��ų
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
	//�׽�Ʈ
	int _testDirection;

	//�÷��̾�
	tagTestplayer _player;
	//����
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



	//������1 ���� ���̵�
	image* _phase1BossIdleImage;
	int _phase1BossIdleCount, _phase1BossIdleIndex;
	//����� ����Ʈ
	image* _airSpinnerBurstImage;
	int _airSpinnerBurstCount, airSpinnerBurstIndex;
	bool _airSpinnerBurstIsStart;
	//������1 ���� �ǰ�
	image* _phase1BossHurtImage;
	int _phase1BossHurtCount, _phase1BossHurtIndex;
	//������1 ���� ĳ��Ʈ
	image* _phase1BossCastImage;
	int _phase1BossCastCount, _phase1BossCastIndex;
	//������1 ���� ���̵�
	image* _phase1SummonIdleImage;
	//������1 ���� �� ĳ��Ʈ
	image* _phase1SummonBallCastImage;
	int _phase1SummonBallCastCount, _phase1SummonBallCastIndex;
	bool _phase1SummonBallCast;
	//������1 ���� ���� ĳ��Ʈ
	image* _phase1SummonSlamCastImage;
	int _phase1SummonSlamCastCount, _phase1SummonSlamCastIndex;
	bool _phase1SummonSlamCast;
	//������1 ���� ���� ĳ��Ʈ
	image* _phase1SummonOrbCastImage;
	int _phase1SummonOrbCastCount, _phase1SummonOrbCastIndex;
	bool _phase1SummonOrbCast;
	

	//������2���۽� ���� �̹���
	image* _phase2BossStartImage;
	int _phase2BossStartCount, _phase2BossStartIndex;
	
	//������2 ���� ����1
	image* _phase2BossAttack1Image;
	int _phase2BossAttack1Count, _phase2BossAttack1Index;

	//������2 ���� ����2
	image* _phase2BossAttack2Image;
	int _phase2BossAttack2Count, _phase2BossAttack2Index;
	
	//������2 ���� ���� ĳ��Ʈ
	image* _phase2BossSlamCastImage;
	int _phase2BossSlamCastCount, _phase2BossSlamCastIndex;

	//������2 ���� �뽬
	image* _phase2BossDashImage;
	int _phase2BossDashCount, _phase2BossDashIndex;

	//������2 ���� �뽬 �׸���
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

	//�׽�Ʈ ����
	void testDirection();
	//�׽�Ʈ ������Ʈ
	void testUpdate();

	//ī���� ���̺� ����
	void chaosWaveAction();
	//ī���� ���̺� ����
	void chaosWaveStop();
	//ī���� �� ����
	void chaosBallAction();
	//ī���� �� ����
	void chaosBallStop();
	//���׿� ����
	void meteoStrikeAction();
	//���׿� ����
	void meteoStrikeStop();
	//ī���� ����̵� ����
	void chaosTornadoAction();
	//ī���� ����̵� ����
	void ChaosTornadoStop();
	//ī���� ���̽��� ����
	void chaosIceQueenAction();
	 
	boss() {}
	~boss() {}
};

