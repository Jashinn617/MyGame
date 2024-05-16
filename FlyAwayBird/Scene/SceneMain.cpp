#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Util/Game.h"
#include "../RecoveredItem.h"

using namespace std;

SceneMain::SceneMain() :
	m_scrollX(0),
	m_shadowMapHandle(-1),
	m_timeFrame(0),
	m_time(0),
	m_clearTime(0),
	m_itemNum(0),
	m_fadeAlpha(0),
	m_countdownFrame(0),
	m_countdownScale(0),
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

	// �w�i�̃X�N���[��
	m_scrollX += kScrollSpeed;

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
		// �V�[�����ŏ������蒼��
		return make_shared<SceneMain>();
	}
	else
	{
		// �t�F�[�h�A�E�g
		m_fadeAlpha += kFadeSpeed;
	}

	return shared_from_this();
}

void SceneMain::Draw(HandleManager& handle)
{
	// �w�i�̕`��
	BackDraw(handle);
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

#ifdef _DEBUG
	// ��ʂ̍���ɃV���h�E�}�b�v�̃e�X�g�`�������
	TestDrawShadowMap(m_shadowMapHandle, 0, 0, 320, 240);
#endif // _DEBUG



	SetWriteZBufferFlag(false);
	if (m_isStart)
	{
		StartDraw(handle);
	}
	else if (m_isCountdown)
	{
		CountdownDraw(handle);
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
		// X�ʒu�����߂�
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
		// Z�ʒu�����߂�
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
	m_countdownFrame++;
	// �J�E���g�_�E���̃X�P�[����傫������
	m_countdownScale += kCountdownShrinkSpeed;
	// �J�E���g�_�E���̃X�P�[�����傫���Ȃ肷���Ȃ��悤�ɂ���
	if (m_countdownScale >= kCountdownMaxScale)
	{
		m_countdownScale = kCountdownMaxScale;
	}
	// ���ꂼ��̕b�����o���тɃX�P�[�������ɖ߂�
	if (m_countdownFrame == kOneSecond || m_countdownFrame == kTwoSecond)
	{
		m_countdownScale = 0;
	}

	// �J�E���g�_�E���p��SE
	if (!CheckSoundMem(handle.GetSound("countdownSE")))
	{
		PlaySoundMem(handle.GetSound("countdownSE"), DX_PLAYTYPE_BACK);
	}

	// �J�E���g�_�E�����́A������󂯕t���Ȃ��悤�ɂ���
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
	if (m_countdownFrame >= kCountdownTime)
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
	// �X�^�[�g���
	DrawGraph(kScreenPosX, kScreenPosY, handle.GetImg("startScreen"), false);
	// �X�^�[�g���S
	DrawGraph(kLogoX, kLogoY, handle.GetImg("startLogo"), true);
}

void SceneMain::CountdownDraw(HandleManager& handle)
{
	// �J�E���g�_�E��3
	if (m_countdownFrame <= kOneSecond && m_countdownFrame > 0)
	{
		DrawRotaGraph(kCountdownPosX, kCountdownPosY, 
			m_countdownScale, 0.0,
			handle.GetImg("countdown3"), true, false);
	}
	// �J�E���g�_�E��2
	if (m_countdownFrame <= kTwoSecond && m_countdownFrame > kOneSecond)
	{
		DrawRotaGraph(kCountdownPosX, kCountdownPosY,
			m_countdownScale, 0.0,
			handle.GetImg("countdown2"), true, false);
	}
	// �J�E���g�_�E��1
	if (m_countdownFrame <= kCountdownTime && m_countdownFrame > kTwoSecond)
	{
		DrawRotaGraph(kCountdownPosX, kCountdownPosY,
			m_countdownScale, 0.0,
			handle.GetImg("countdown1"), true, false);
	}
}

void SceneMain::PlayDraw(HandleManager& handle)
{
	// �ŏ���2�b�Ԃ���Go��\������
	if (m_timeFrame <= kTwoSecond)
	{
		DrawRotaGraph(kGoPosX, kGoPosY, m_countdownScale, 0.0, handle.GetImg("go"), true, false);
	}

	// �b��
	// �O
	DrawFormatStringToHandle(kTimePosX + kBackFontShiftPosX, kTimePosY,
		kFrontCharColor, handle.GetFont("timeFont"), "%d������", m_time);
	// ���
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 
		kBackCharColor, handle.GetFont("timeFont"), "%d������", m_time);

	// �c��̃A�C�e����
	// �O
	DrawFormatStringToHandle(kItemPosX + kBackFontShiftPosX, kItemPosY,
		kFrontCharColor, handle.GetFont("itemNumFont"), "�̂���F%d��", kItemNum - m_itemNum);
	// ���
	DrawFormatStringToHandle(kItemPosX, kItemPosY,
		kBackCharColor, handle.GetFont("itemNumFont"), "�̂���F%d��", kItemNum - m_itemNum);
}

void SceneMain::ClearDraw(HandleManager& handle)
{
	// �N���A�^�C���ɂ���āA�\�������摜���ς��
	if (m_clearTime <= kClearFastTime)
	{
		DrawGraph(kScreenPosX, kScreenPosY, handle.GetImg("fastClearScreen"), false);
	}
	else if (m_clearTime > kClearFastTime && m_clearTime < kClearSlowTime)
	{
		DrawGraph(kScreenPosX, kScreenPosY, handle.GetImg("normalClearScreen"), false);
	}
	else if (m_clearTime >= kClearSlowTime)
	{
		DrawGraph(kScreenPosX, kScreenPosY, handle.GetImg("slowClearScreen"), false);
	}

	// �b���̕`��
	DrawFormatStringToHandle(kClearTimePosX + kBackFontShiftPosX, kClearTimePosY,
		kFrontCharColor, handle.GetFont("clearTimeFont"), "�������F%d�т傤�I", m_clearTime);

	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY,
		kBackCharColor, handle.GetFont("clearTimeFont"), "�������F%d�т傤�I", m_clearTime);

	DrawGraph(kLogoX, kLogoY, handle.GetImg("clearLogo"), true);
}

void SceneMain::BackDraw(HandleManager& handle)
{
	// �w�i�̃T�C�Y���擾����
	BgSize bgSize;
	GetGraphSize(handle.GetImg("backSky"), &bgSize.width, &bgSize.height);

	// �w�i�摜���X�N���[��������
	int scrollBack = static_cast<int>(m_scrollX) % bgSize.width;
	for (int index = 0; index < kIndexBack; ++index)
	{
		DrawGraph(-scrollBack + index * bgSize.width,
			Game::kScreenHeight - bgSize.height,
			handle.GetImg("backSky"),
			true);
	}
}
