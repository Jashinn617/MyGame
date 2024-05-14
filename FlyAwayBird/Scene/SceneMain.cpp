#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Util/Game.h"
#include "../RecoveredItem.h"

using namespace std;

SceneMain::SceneMain() :
	m_shadowMapHandle(-1),
	m_timeFrame(0),
	m_time(0),
	m_clearTime(0),
	m_itemNum(0),
	m_fadeAlpha(0),
	m_countdownFrame(kCountdownTime),
	m_isStart(true),
	m_isCountdown(false),
	m_isPlay(false),
	m_isClear(false),
	m_isSe(false),
	m_pPlayer(nullptr),
	m_pCamera(nullptr)
{
	m_pItem.resize(kItemNum);

	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i] = nullptr;
	}
}

SceneMain::~SceneMain()
{
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(m_shadowMapHandle);
}

void SceneMain::Init(HandleManager& handle)
{
	// ���C�g�̐ݒ�
	// �W���̃��C�g���f�B���N�V���i�����C�g�ɂ���
	ChangeLightTypeDir(kLightDir);

	/*�V���h�E�}�b�v�̐ݒ�*/
	// �V���h�E�}�b�v�n���h���̍쐬
	m_shadowMapHandle = MakeShadowMap(kShadowMapSizeX, kShadowMapSizeY);
	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(m_shadowMapHandle,kShadowMapLightDir);
	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(m_shadowMapHandle, kShadowMapRangeMin, kShadowMapRangeMax);

	/*�|�C���^�̐����Ɗe�N���X�̏�����*/
	m_pPlayer = make_shared<Player>();
	m_pPlayer->Init(handle);
	m_pCamera = make_shared<Camera>(m_pPlayer);
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i] = make_shared<RecoveredItem>(m_pPlayer);
	}
	ItemInit(handle);
}

shared_ptr<SceneBase> SceneMain::Update(Input& input, HandleManager& handle)
{
	//�n�ʃ��f���̈ʒu�A�傫���̐ݒ�
	MV1SetScale(handle.GetModel("ground"), VGet(kGroundModelScale, 1, kGroundModelScale));
	MV1SetPosition(handle.GetModel("ground"), VGet(0, kGroundPosY, 0));

	if (m_isStart)
	{
		StartUpdate(input, handle);
	}
	else if (m_isCountdown)
	{
		CountdownUpdate(input, handle);
	}
	else if (m_isPlay)
	{
		PlayUpdate(input, handle);
	}
	else if (m_isClear)
	{
		ClearUpdate(input, handle);
	}
	else if (m_fadeAlpha >= 255)
	{
		return make_shared<SceneMain>();
	}
	else
	{
		m_fadeAlpha += kFadeSpeed;
	}

	return shared_from_this();
}

void SceneMain::Draw(HandleManager& handle)
{
	DrawGraph(0, 0, handle.GetImg("backSky"), false);
	SetWriteZBufferFlag(true);

	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(m_shadowMapHandle);

	// �v���C���[�̕`��
	m_pPlayer->Draw(handle);
	// �n�ʃ��f���̕`��
	MV1DrawModel(handle.GetModel("ground"));
	// �A�C�e���̕`��
	for (const auto& item : m_pItem)
	{
		item->Draw(handle);
	}

	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, m_shadowMapHandle);

	// �v���C���[�̕`��
	m_pPlayer->Draw(handle);
	// �n�ʃ��f���̕`��
	MV1DrawModel(handle.GetModel("ground"));
	// �A�C�e���̕`��
	for (const auto& item : m_pItem)
	{
		item->Draw(handle);
	}

	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);



	SetWriteZBufferFlag(false);
	if (m_isStart)
	{
		StartDraw(handle);
	}
	else if (m_isCountdown)
	{

	}
	else if (m_isPlay)
	{
		PlayDraw(handle);
	}
	else
	{
		ClearDraw(handle);
	}

#ifdef _DEBUG
	// XYZ��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));
	DrawString(8, 8, "MainScene", 0xffffff);
#endif // DEBUG

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneMain::End()
{
	/*��������*/
}

void SceneMain::ItemInit(HandleManager& handle)
{
	for (const auto& item : m_pItem)
	{
		// �A�C�e���̈ʒu�������_���ɂ���
		int rand = GetRand(1);
		float x = 0;
		if (rand == 0)
		{
			x = static_cast<float>(GetRand(static_cast<int>(kWallX)));
		}
		else if (rand == 1)
		{
			x = static_cast<float>(GetRand(static_cast<int>(-kWallX)));
		}
		rand = GetRand(1);
		float z = 0;
		if (rand == 0)
		{
			z = static_cast<float>(GetRand(static_cast<int>(kWallZ)));
		}
		else if (rand == 1)
		{
			z = static_cast<float>(GetRand(static_cast<int>(-kWallZ)));

		}
		item->Init(x, z,handle);
	}
}

void SceneMain::StartUpdate(Input& input, HandleManager& handle)
{
	if (!CheckSoundMem(handle.GetSound("startBGM")))
	{
		PlaySoundMem(handle.GetSound("startBGM"), DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("A"))
	{
		StopSoundMem(handle.GetSound("startBGM"));
		m_isCountdown = true;
		m_isStart = false;
	}
}

void SceneMain::CountdownUpdate(Input& input, HandleManager& handle)
{
	m_countdownFrame--;
	// �J�E���g�_�E���p��SE
	if (!CheckSoundMem(handle.GetSound("countdownSE")))
	{
		PlaySoundMem(handle.GetSound("countdownSE"), DX_PLAYTYPE_BACK);
	}

	/*�J�E���g�_�E�����́A������󂯕t���Ȃ��悤�ɂ���*/
	// �J����
	m_pCamera->Update(input,false);
	// �v���C���[
	m_pPlayer->Update(input, handle,false);
	// �A�C�e��
	for (const auto& item : m_pItem)
	{
		item->Update(handle);
	}

	// �J�E���g�_�E����0�ɂȂ�����Q�[���X�^�[�g
	if (m_countdownFrame <= 0)
	{
		m_countdownFrame = 0;
		m_isPlay = true;
		m_isCountdown = false;
	}
}

void SceneMain::PlayUpdate(Input& input, HandleManager& handle)
{
	// �b��
	m_timeFrame++;
	m_time = m_timeFrame / 60;

	// BGM
	if (!CheckSoundMem(handle.GetSound("mainBGM")))
	{
		PlaySoundMem(handle.GetSound("mainBGM"), DX_PLAYTYPE_LOOP);
	}


	// �c��̃A�C�e���̐���0�������ꍇ�̓Q�[�����I������
	m_itemNum = 0;
	for (const auto& item : m_pItem)
	{
		// ���ݎ���Ă���A�C�e���̐����擾����
		if (!item->IsExist())
		{
			m_itemNum++;
		}
	}
	// �S�ẴA�C�e�����������Q�[���I��
	if (kItemNum - m_itemNum == 0)
	{
		// ���݂̕b�����N���A�b���ɋL�^����
		m_clearTime = m_time;
		// BGM�̏I��
		StopSoundMem(handle.GetSound("mainBGM"));
		// ���݂̃V�[�����I�����ăN���A��ʂɑJ�ڂ���
		m_isPlay = false;
		m_isClear = true;
	}

	/*�J������A�v���C���[�̑�����󂯕t����悤�ɂ���*/
	// �J����
	m_pCamera->Update(input, true);
	// �v���C���[
	m_pPlayer->Update(input, handle,true);
	// �A�C�e��
	for (const auto& item : m_pItem)
	{
		item->Update(handle);
	}

	// �f�o�b�O�p�̃V�[���J��
	// B�{�^�����������玩���I�ɃV�[�����I������
#ifdef _DEBUG
	if (input.IsTriggered("B"))
	{
		m_clearTime = m_time;
		StopSoundMem(handle.GetSound("mainBGM"));
		m_isClear = true;
		m_isPlay = false;
	}
#endif // _DEBUG
}

void SceneMain::ClearUpdate(Input& input, HandleManager& handle)
{
	// SE�̍Đ�
	// �N���A�^�C���ɂ����SE�̓��e���ς��
	if (!m_isSe)
	{
		// SE�����Ă���Ƃ��͑��삪�ł��Ȃ�
		if (m_clearTime <= kClearFastTime)
		{
			PlaySoundMem(handle.GetSound("fastClearSE"), DX_PLAYTYPE_NORMAL);
		}
		else if (m_clearTime > kClearFastTime && m_clearTime < kClearSlowTime)
		{
			PlaySoundMem(handle.GetSound("normalClearSE"), DX_PLAYTYPE_NORMAL);
		}
		else if (m_clearTime >= kClearSlowTime)
		{
			PlaySoundMem(handle.GetSound("slowClearSE"), DX_PLAYTYPE_NORMAL);
		}

		// SE�����[�v���Ȃ��悤�ɂ���
		m_isSe = true;
	}
	// BGM
	if (!CheckSoundMem(handle.GetSound("clearBGM")))
	{
		PlaySoundMem(handle.GetSound("clearBGM"), DX_PLAYTYPE_LOOP);
	}
	if (input.IsTriggered("A"))
	{
		PlaySoundMem(handle.GetSound("selectSE"), DX_PLAYTYPE_BACK);
		// BGM�̏I��
		StopSoundMem(handle.GetSound("clearBGM"));
		m_isClear = false;
	}
}

void SceneMain::StartDraw(HandleManager& handle)
{
	DrawGraph(200, 100, handle.GetImg("startScreen"), false);
}

void SceneMain::PlayDraw(HandleManager& handle)
{
	// �b���̕`��
	DrawFormatStringToHandle(kTimePosX + kBackFontShiftPosX, kTimePosY, 0x00008b, handle.GetFont("timeFont"), "%d������", m_time);
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xff7f50, handle.GetFont("timeFont"), "%d������", m_time);

	// �c��̃A�C�e�����̕`��
	DrawFormatStringToHandle(kItemPosX + kBackFontShiftPosX, kItemPosY, 0x000086, handle.GetFont("itemNumFont"), "�̂���F%d��", kItemNum - m_itemNum);
	DrawFormatStringToHandle(kItemPosX, kItemPosY, 0xff6347, handle.GetFont("itemNumFont"), "�̂���F%d��", kItemNum - m_itemNum);
}

void SceneMain::ClearDraw(HandleManager& handle)
{
	DrawGraph(200, 100, handle.GetImg("clearScreen"), false);

	// �b���̕`��
	DrawFormatStringToHandle(kClearTimePosX + kBackFontShiftPosX, kClearTimePosY, 0x00008b, handle.GetFont("clearTimeFont"), "�������F%d�т傤�I", m_clearTime);
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xff7f50, handle.GetFont("clearTimeFont"), "�������F%d�т傤�I", m_clearTime);
}