#include "Stage_01.h"
#include "../Game.h"
#include "../util/Input.h"
#include "DxLib.h"
#include "../Player.h"
#include "../Attack/Vomit.h"
#include "../Attack/AirBullet.h"
#include "../Attack/Inhale.h"
#include "../Camera.h"
#include "../Enemy/StopEnemy.h"
#include "../Enemy/WalkEnemy.h"
#include "../Enemy/FlyEnemy.h"
#include "../UI.h"
#include "../Object/Door.h"
#include "../Object//RecoveryItem.h"
#include "GameOverScene.h"

namespace
{
	// �}�b�v�̍L��
	constexpr int kMapWidth = Game::kScreenWidth * 5;
	constexpr int kMapHeight = Game::kScreenHeight;

	// �w�i�̐�
	constexpr int kBackBgNum = 5;

	// �}�b�v�`�b�v�̏��
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;

	// �w�i�̑傫��
	constexpr int kBackWidth = Game::kScreenWidth;
	constexpr int kBackHeight = Game::kScreenHeight;

	// �`�b�v��u����
	constexpr int kChipNumX = (Game::kScreenWidth / kChipWidth) * 5;
	constexpr int kChipNumY = (Game::kScreenHeight / kChipHeight);

	// �v���C���[�̏������W
	constexpr int kStartX = 50;
	constexpr int kStartY = 300;

	// �G�l�~�[�̐�
	constexpr int kStopEnemyNum = 30;
	constexpr int kWalkEnemyNum = 15;
	constexpr int kFlyEnemyNum = 10;

	// �A�C�e���̐�
	constexpr int kItemNum = 5;

	// �v���C���[���~�X�������Ƃ��̉��o�t���[��
	constexpr int kMissSe02Frame = 60;
	constexpr int kMissFrameMax = 60 * 2;
	constexpr float kMissFadeFrame = 60 * 2.2;
	constexpr float kContinueFrame = 60 * 2.6;

	// ��ʂ̑傫��
	constexpr int kScreenWidht = Game::kScreenWidth;
	constexpr int kScreenHeight = Game::kScreenHeight;

	// �h�A�̈ʒu
	constexpr float kDoorX = static_cast<float>(kChipWidth) * 149.0f - static_cast<float>(kChipWidth) * 0.5f;
	constexpr float kDoorY = static_cast<float>(kChipHeight) * 5.0f;

	// BGM�̍ő�l
	constexpr int kBgmVolumeMax = 200;

	// �t�F�[�h�̑��x
	constexpr int kMissFadeSpeed = 20;
	constexpr int kSceneChangeFadeSpeed = 12;
	// �t�F�[�h�̍ő�Alpha��
	constexpr int kFadeMaxAlpha = 255;

	// ��ʂ̗h�ꕝ
	constexpr int kScreenShake = 16;

	// ��ʂ��h��鎞��
	constexpr int kScreenShakeFrameMax = 8;
	// �t�F�[�h���̐F
	constexpr unsigned int kFadeColor = 0xffffff;
	// �w�i�ɂ��Ԃ���F
	constexpr unsigned int kBackColor = 0xff0000;
}

Stage_01::Stage_01() :
	m_gameScreenHandle(-1),
	m_backgroundHandle(-1),
	m_chipHandle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_bgmHandle(-1),
	m_missSeHandle(-1),
	m_moveSeHandle(-1),
	m_missSeHandle2(-1),
	m_fadeAlpha(255),
	m_backAlpha(50),
	m_ismissFade(false),
	m_shakeFrame(0),
	m_nextScene(kStage02),
	m_isMiss(false),
	m_isSceneEnd(false)
{
	// �Q�[����ʕ`���̐���
	m_gameScreenHandle = MakeScreen(kScreenWidht, kScreenHeight, true);
	/*�摜�̃��[�h*/
	m_backgroundHandle = LoadGraph("data/Map/Stage_01Bg.png");
	m_chipHandle = LoadGraph("data/Map/map.png");

	/*�G�̐������߂�*/
	m_pStopEnemy.resize(kStopEnemyNum);
	m_pWalkEnemy.resize(kWalkEnemyNum);
	m_pFlyEnemy.resize(kFlyEnemyNum);
	/*�A�C�e���̐������߂�*/
	m_pRecoveryItem.resize(kItemNum);

	/*�}�b�v�`�b�v�̐��𐔂���*/
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_chipHandle, &graphW, &graphH);
	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	// �}�b�v�`�b�v�̔z�u�f�[�^�̏�����
	m_chipData = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01,01,01, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0,01,01,01,01},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01, 0, 0,01,01, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02, 0, 0,02,02,02,02},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,01,01,01, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0,01,01, 0, 0, 0, 0, 0, 0,01, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01,01,02,02, 0, 0,02,02,02,02},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0,01,01,01, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,01, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02, 0, 0, 0, 0,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02},
		{01,01,01,01,01,01, 0, 0,01,02, 0, 0,02,01,01,01,01,01,01,01,01, 0, 0,01,01,01,01,01,01,02,02,02,01,01,01,01,01,02,02,02,01,01,01,02, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0,02,01,01,01,01,02,02, 0, 0, 0,01,01,01,01,01, 0, 0,01,01,01,01,01,01, 0, 0,01,01,01,01,01,01,01,01,01,02,02,02, 0, 0, 0, 0,01,01,01,01,01,01,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,01,01,01,01,01,01,01,01,01,01,01,01,01, 0, 0, 0, 0,02,02,02,02},
		{02,02,02,02,02,02, 0, 0,02,02, 0, 0,02,02,02,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0,02,02,02,02,02, 0, 0,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02},
		{02,02,02,02,02,02, 0, 0,02,02, 0, 0,02,02,02,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0,02,02,02,02,02, 0, 0,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02},
		{02,02,02,02,02,02, 0, 0,02,02, 0, 0,02,02,02,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0,02,02,02,02,02, 0, 0,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02},
		{02,02,02,02,02,02, 0, 0,02,02, 0, 0,02,02,02,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0,02,02,02,02,02, 0, 0,02,02,02,02,02,02, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02,02,02,02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02, 0, 0, 0, 0,02,02,02,02},
	};	
}

Stage_01::~Stage_01()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_gameScreenHandle);
	DeleteGraph(m_backgroundHandle);
	DeleteGraph(m_chipHandle);
}

void Stage_01::Init()
{
	// �}�b�v�̍L�������߂�
	m_pCamera->StartHorizon();
	m_pCamera->Init();

	// �v���C���[��HP�Ǝc�@��S�񕜂���
	m_pPlayer->CompleteRecoveryHp();
	m_pPlayer->CompleteRecoveryLives();

	// ������
	RestartInit();
	// �h�A�̈ʒu��ݒ肷��
	m_pDoor->Init(kDoorX, kDoorY);
	// �Q�[���I�[�o�[�V�[���̃R���e�j���[���ɖ߂�V�[����ݒ肷��
	m_pGameOver->ChangeNextScene(m_pGameOver->GetStage01());

	/*BGM�̃��[�h*/
	m_bgmHandle = LoadSoundMem(_T("data/Sound/BGM/Stage_01.wav"));
	// BGM�̉��ʐݒ�
	ChangeVolumeSoundMem(kBgmVolumeMax, m_bgmHandle);

	/*SE�̃��[�h*/
	m_missSeHandle = LoadSoundMem(_T("data/Sound/SE/Miss.wav"));
	m_missSeHandle2 = LoadSoundMem(_T("data/Sound/SE/Miss02.mp3"));
	m_moveSeHandle = LoadSoundMem(_T("data/Sound/SE/Move.wav"));

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, true);

	// �V�[�����I�����Ȃ��悤�ɂ���
	m_isSceneEnd = false;
}

void Stage_01::Update(Input& input)
{
	if (!m_isSceneEnd)
	{
		// �v���C���[���~�X�������ۂ̓v���C���[�ȊO���~�܂�
		if (!m_isMiss)
		{
			EnemyUpdate();
			ItemUpdate();
			m_pDoor->Update();
			m_pUI->Update();
		}
		// �v���C���[�Ƀ}�b�v�`�b�v�̃f�[�^��n���Ă���
		m_pPlayer->Update(input, m_chipData, kChipNumX, kChipNumY, kChipWidth, kChipHeight);

		// ��ʗh��̏���
		m_shakeFrame--;
		if (m_shakeFrame <= 0) m_shakeFrame = 0;

		// �~�X
		OnMiss();

		// �c�@��0�ɂȂ�����Q�[���I�[�o�[
		if (m_pPlayer->GetRemainingLives() < 0)
		{
			// ���̃V�[�����Q�[���I�[�o�[�V�[���ɂ���
			m_nextScene = kGameOver;
			m_isSceneEnd = true;
		}

		// �v���C���[���~�X���������̃t�F�[�h����
		if (m_ismissFade)// �t�F�[�h�C��
		{
			m_fadeAlpha += kMissFadeSpeed;
			if (m_fadeAlpha > kFadeMaxAlpha)
			{
				m_fadeAlpha = kFadeMaxAlpha;
				m_ismissFade = false;
			}
		}
		else // �t�F�[�h�A�E�g
		{
			m_fadeAlpha -= kMissFadeSpeed;
			if (m_fadeAlpha < 0)
			{
				m_fadeAlpha = 0;
			}
		}

		// �v���C���[�����ɓ������玟�̃V�[���Ɉڍs����
		if (m_pDoor->IsColision())
		{
			if (input.IsTriggered("up"))
			{
				// SE��炷
				PlaySoundMem(m_moveSeHandle, DX_PLAYTYPE_BACK, true);
				// ���̃V�[�����X�e�[�W2�ɂ���
				m_nextScene = kStage02;
				m_isSceneEnd = true;
			}
		}

		// �t�F�[�h�A�E�g
		m_fadeAlpha -= kSceneChangeFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	// ��ʓ]���̃t�F�[�h
	else // �t�F�[�h�C��
	{
		m_fadeAlpha += kSceneChangeFadeSpeed;
		if (m_fadeAlpha > kFadeMaxAlpha)
		{
			m_fadeAlpha = kFadeMaxAlpha;
		}
	}

#ifdef _DEBUG
	// S�L�[�ŃQ�[���I�[�o�[�ɔ��
	if (input.IsTriggered("S"))
	{
		m_nextScene = kGameOver;
		m_isSceneEnd = true;
	}
	// P�L�[�Ŏ��̃V�[���ɔ��
	else if (input.IsTriggered("P"))
	{
		PlaySoundMem(m_moveSeHandle, DX_PLAYTYPE_BACK, true);
		m_nextScene = kStage02;
		m_isSceneEnd = true;
	}
#endif
}

void Stage_01::Draw()
{
	// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	BackDraw();
	// �}�b�v�`�b�v�̕`��
	ChipDraw();
	
	// �h�A�̕`��
	m_pDoor->Draw();

	// �G�L�����N�^�[�̕`��
	EnemyDraw();

	// �A�C�e���̕`��
	ItemDraw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	m_pUI->Draw();

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[����ʂ��o�b�N�o�b�t�@�ɕ`�悷��
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
	{
		// ��ʂ�h�炷
		screenX = GetRand(kScreenShake) - (kScreenShake / 2);
		screenY = GetRand(kScreenShake) - (kScreenShake / 2);
	}

	// �X�N���[���̕`��
	DrawGraph(screenX, screenY, m_gameScreenHandle, true);

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidht, kScreenHeight, kFadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void Stage_01::End()
{
	// BGM���~�߂�
	StopSoundMem(m_bgmHandle);
	// BGM������������폜����
	DeleteSoundMem(m_bgmHandle);
	// SE������������폜����
	DeleteSoundMem(m_missSeHandle);
	DeleteSoundMem(m_missSeHandle2);
	DeleteSoundMem(m_moveSeHandle);
}

bool Stage_01::IsSceneEnd() const
{
	// �t�F�[�h��������Ă���V�[�����ړ�����
	return m_isSceneEnd && (m_fadeAlpha >= kFadeMaxAlpha);
}

void Stage_01::RestartInit()
{
	/*�v���C���[�̏�����*/
	m_pPlayer->Init();
	// �������W�̐ݒ�
	m_pPlayer->SetStartPos(kStartX, kStartY);
	// �d�͂̏�����
	m_pPlayer->GravityReset();

	m_pCamera->Init();
	m_pUI->Init();

	// �G�L�����N�^�[�̏�����
	EnemyInit();
	// �A�C�e���̏�����
	ItemInit();

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, true);
	// ��ʗh��̃t���[�����[���ɖ߂�
	m_shakeFrame = 0;
}

void Stage_01::EnemyInit()
{
	/*�������ƍ��W�̐ݒ�*/

	// �~�܂��Ă���G
	{
		m_pStopEnemy[0]->Init(static_cast<float>((kChipWidth * 6) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[1]->Init(static_cast<float>((kChipWidth * 10) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[2]->Init(static_cast<float>((kChipWidth * 13) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 9)));
		m_pStopEnemy[3]->Init(static_cast<float>((kChipWidth * 16) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[4]->Init(static_cast<float>((kChipWidth * 17) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[5]->Init(static_cast<float>((kChipWidth * 17) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
		m_pStopEnemy[6]->Init(static_cast<float>((kChipWidth * 19) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
		m_pStopEnemy[7]->Init(static_cast<float>((kChipWidth * 32) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[8]->Init(static_cast<float>((kChipWidth * 34) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[9]->Init(static_cast<float>((kChipWidth * 36) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[10]->Init(static_cast<float>((kChipWidth * 38) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 8)));
		m_pStopEnemy[11]->Init(static_cast<float>((kChipWidth * 40) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 8)));
		m_pStopEnemy[12]->Init(static_cast<float>((kChipWidth * 44) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[13]->Init(static_cast<float>((kChipWidth * 57) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
		m_pStopEnemy[14]->Init(static_cast<float>((kChipWidth * 63) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[15]->Init(static_cast<float>((kChipWidth * 68) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
		m_pStopEnemy[16]->Init(static_cast<float>((kChipWidth * 85) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[17]->Init(static_cast<float>((kChipWidth * 87) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[18]->Init(static_cast<float>((kChipWidth * 91) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[19]->Init(static_cast<float>((kChipWidth * 93) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[20]->Init(static_cast<float>((kChipWidth * 104) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 6)));
		m_pStopEnemy[21]->Init(static_cast<float>((kChipWidth * 106) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
		m_pStopEnemy[22]->Init(static_cast<float>((kChipWidth * 108) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 6)));
		m_pStopEnemy[23]->Init(static_cast<float>((kChipWidth * 116) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 4)));
		m_pStopEnemy[24]->Init(static_cast<float>((kChipWidth * 120) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 6)));
		m_pStopEnemy[25]->Init(static_cast<float>((kChipWidth * 133) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 4)));
		m_pStopEnemy[26]->Init(static_cast<float>((kChipWidth * 141) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 7)));
		m_pStopEnemy[27]->Init(static_cast<float>((kChipWidth * 142) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)));
		m_pStopEnemy[28]->Init(static_cast<float>((kChipWidth * 143) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 3)));
		m_pStopEnemy[29]->Init(static_cast<float>((kChipWidth * 147) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)));
	}
	// �����G
	{
		m_pWalkEnemy[0]->Init(static_cast<float>((kChipWidth * 14) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 220);
		m_pWalkEnemy[1]->Init(static_cast<float>((kChipWidth * 24) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 150);
		m_pWalkEnemy[2]->Init(static_cast<float>((kChipWidth * 35) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 5)), 100);
		m_pWalkEnemy[4]->Init(static_cast<float>((kChipWidth * 41) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 60);
		m_pWalkEnemy[5]->Init(static_cast<float>((kChipWidth * 58) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 95);
		m_pWalkEnemy[6]->Init(static_cast<float>((kChipWidth * 67) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 120);
		m_pWalkEnemy[7]->Init(static_cast<float>((kChipWidth * 74) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 170);
		m_pWalkEnemy[8]->Init(static_cast<float>((kChipWidth * 82) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 250);
		m_pWalkEnemy[9]->Init(static_cast<float>((kChipWidth * 98) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 190);
		m_pWalkEnemy[10]->Init(static_cast<float>((kChipWidth * 130) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 190);
		m_pWalkEnemy[11]->Init(static_cast<float>((kChipWidth * 133) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 190);
		m_pWalkEnemy[12]->Init(static_cast<float>((kChipWidth * 136) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 11)), 190);
		m_pWalkEnemy[13]->Init(static_cast<float>((kChipWidth * 131) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 4)), 140);
		m_pWalkEnemy[14]->Init(static_cast<float>((kChipWidth * 143) - (kChipWidth * 0.5f)), static_cast<float>((kChipHeight * 3)), 30);
	}
	// ��ԓG
	{
		m_pFlyEnemy[0]->Init(static_cast<float>((kChipWidth * 10) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 2), 90);
		m_pFlyEnemy[1]->Init(static_cast<float>((kChipWidth * 30) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 3), 500);
		m_pFlyEnemy[2]->Init(static_cast<float>((kChipWidth * 60) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 3), 200);
		m_pFlyEnemy[3]->Init(static_cast<float>((kChipWidth * 80) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 4), 70);
		m_pFlyEnemy[4]->Init(static_cast<float>((kChipWidth * 110) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 4), 300);
		m_pFlyEnemy[5]->Init(static_cast<float>((kChipWidth * 132) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 3), 260);
		m_pFlyEnemy[6]->Init(static_cast<float>((kChipWidth * 70) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 2), 30);
		m_pFlyEnemy[7]->Init(static_cast<float>((kChipWidth * 105) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 4), 500);
		m_pFlyEnemy[8]->Init(static_cast<float>((kChipWidth * 55) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 6), 50);
		m_pFlyEnemy[9]->Init(static_cast<float>((kChipWidth * 30) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 3), 200);
	}
}

void Stage_01::ItemInit()
{
	/*�������ƍ��W�̐ݒ�*/

	// �񕜃A�C�e��
	{
		m_pRecoveryItem[0]->Init(static_cast<float>((kChipWidth * 5) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 11));
		m_pRecoveryItem[1]->Init(static_cast<float>((kChipWidth * 58) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 11));
		m_pRecoveryItem[2]->Init(static_cast<float>((kChipWidth * 103) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 11));
		m_pRecoveryItem[3]->Init(static_cast<float>((kChipWidth * 77) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 11));
		m_pRecoveryItem[4]->Init(static_cast<float>((kChipWidth * 135) - (kChipWidth * 0.5f)), static_cast<float>(kChipHeight * 11));
	}
}

void Stage_01::EnemyUpdate()
{
	// �~�܂��Ă���G
	for (int i = 0; i < m_pStopEnemy.size(); i++)
	{
		m_pStopEnemy[i]->Update();
	}
	// �����Ă���G
	for (int i = 0; i < m_pWalkEnemy.size(); i++)
	{
		m_pWalkEnemy[i]->Update();
	}
	// ���ł���G
	for (int i = 0; i < m_pFlyEnemy.size(); i++)
	{
		m_pFlyEnemy[i]->Update();
	}
}

void Stage_01::ItemUpdate()
{
	// �񕜃A�C�e��
	for (int i = 0; i < m_pRecoveryItem.size(); i++)
	{
		m_pRecoveryItem[i]->Update();
	}
}

void Stage_01::BackDraw()
{
	// �v���C���[�̈ʒu�ɉ������X�N���[���ʂ����肷��
	int scrollX = m_pCamera->GetScrollX();
	int scrollY = m_pCamera->GetScrollY();

	// �w�i�̕`��
	DrawBox(0, 0, kMapWidth, kMapHeight, 0xffffbc, true);

	// �w�i�̃X�N���[��
	for (int i = 0; i < kBackBgNum; i++)
	{
		int posX = kBackWidth * i - scrollX;
		int posY = scrollY;

		DrawGraph(posX, posY, m_backgroundHandle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_backAlpha);
	DrawBox(0, 0, kMapWidth, kMapHeight, kBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void Stage_01::ChipDraw()
{
	// �v���C���[�̈ʒu�ɉ������X�N���[���ʂ����肷��
	int scrollX = m_pCamera->GetScrollX();
	int scrollY = m_pCamera->GetScrollY();

	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			int posX = kChipWidth * x - scrollX;
			int posY = kChipHeight * y - scrollY;

			// ��ʊO��`�悵�Ȃ�
			if (posX < 0 - kChipWidth)        continue;
			if (posX > Game::kScreenWidth)    continue;
			if (posY < 0 - kChipHeight)        continue;
			if (posY > Game::kScreenHeight)    continue;

			int chipNo = m_chipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�̐؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(posX, posY,
				srcX, srcY,
				kChipWidth, kChipHeight,
				m_chipHandle, true);
		}
	}
}

void Stage_01::EnemyDraw()
{
	// �~�܂��Ă���G
	for (int i = 0; i < m_pStopEnemy.size(); i++)
	{
		m_pStopEnemy[i]->Draw();
	}
	// �����Ă���G
	for (int i = 0; i < m_pWalkEnemy.size(); i++)
	{
		m_pWalkEnemy[i]->Draw();
	}
	// ���ł���G
	for (int i = 0; i < m_pFlyEnemy.size(); i++)
	{
		m_pFlyEnemy[i]->Draw();
	}
}

void Stage_01::ItemDraw()
{
	// �񕜃A�C�e��
	for (int i = 0; i < m_pRecoveryItem.size(); i++)
	{
		m_pRecoveryItem[i]->Draw();
	}
}

void Stage_01::OnMiss()
{
	// �v���C���[���~�X�������ꍇ�͎c�@�����炵��HP��S�񕜂��ď����ʒu�ɖ߂�
	// �������ꍇ��HP���[���ɂȂ����ꍇ�ŉ��o���Ⴄ���ߕʁX�ŏ��������
	// �������ꍇ�̏���
	if ((m_pPlayer->GetBottom() >= kMapHeight) || (m_pPlayer->GetHp() <= 0))
	{
		// �������ꍇ
		if ((m_pPlayer->GetBottom() >= kMapHeight) && !m_isMiss)
		{
			// ��ʂ�h�炷
			// ��x��ʂ��h�ꂽ�������x�h��Ȃ��悤�ɂ���
			m_shakeFrame = kScreenShakeFrameMax;
			m_pPlayer->FellMiss();
		}
		else if ((m_pPlayer->GetHp() <= 0) && !m_isMiss)// HP���[���ɂȂ����ꍇ
		{
			m_shakeFrame = kScreenShakeFrameMax;
			m_pPlayer->DamageMiss();
		}

		// BGM���~�߂�
		StopSoundMem(m_bgmHandle);

		// SE��炷
		if (!CheckSoundMem(m_missSeHandle2) && !m_isMiss)
		{
			PlaySoundMem(m_missSeHandle2, DX_PLAYTYPE_BACK, true);
		}
		m_pPlayer->OnMiss();

		// ��ʂ��~�߂�
		m_isMiss = true;

	}
	// �~�X�����ď����o���Ă���~�X���o�p��SE��炷
	if (m_pPlayer->GetMissFrame() >= kMissSe02Frame)
	{
		if (!CheckSoundMem(m_missSeHandle))
		{
			PlaySoundMem(m_missSeHandle, DX_PLAYTYPE_BACK, true);
		}
	}
	// �t�F�[�h���o
	if (m_pPlayer->GetMissFrame() >= kMissFrameMax)
	{
		m_ismissFade = true;
	}
	// ���X�^�[�g
	if (m_pPlayer->GetMissFrame() >= kContinueFrame)
	{
		// �v���C���[�̎c�@�����炵��HP�͑S�񕜂���
		// �v���C���[��G�l�~�[�̈ʒu������������
		m_pPlayer->DeleteLives();
		m_pPlayer->CompleteRecoveryHp();
		RestartInit();
		m_isMiss = false;
	}
}

