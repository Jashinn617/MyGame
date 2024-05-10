#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Util/Game.h"
#include "../RecoveredItem.h"

using namespace std;

SceneMain::SceneMain():
	m_startHandle(-1),
	m_clearHandle(-1),
	m_backHandle(-1),
	m_groundModelHandle(-1),
	m_fastClearSeHandle(-1),
	m_clearSeHandle(-1),
	m_slowClearSeHandle(-1),
	m_startBgmHandle(-1),
	m_mainBgmHandle(-1),
	m_clearBgmHandle(-1),
	m_timeFontHandle(-1),
	m_itemFontHandle(-1),
	m_clearTimeFontHandle(-1),
	m_timeFrame(0),
	m_time(0),
	m_clearTime(0),
	m_itemNum(0),
	m_fadeAlpha(0),
	m_isStart(true),
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
	/*画像のデリート*/
	DeleteGraph(m_startHandle);
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_backHandle);
	/*モデルのデリート*/
	MV1DeleteModel(m_groundModelHandle);
	/*SEのデリート*/
	DeleteSoundMem(m_fastClearSeHandle);
	DeleteSoundMem(m_clearSeHandle);
	DeleteSoundMem(m_slowClearSeHandle);
	/*BGmのデリート*/
	DeleteSoundMem(m_startBgmHandle);
	DeleteSoundMem(m_mainBgmHandle);
	DeleteSoundMem(m_clearBgmHandle);
	/*フォントのデリート*/
	DeleteFontToHandle(m_timeFontHandle);
	DeleteFontToHandle(m_itemFontHandle);
	DeleteFontToHandle(m_clearTimeFontHandle);
}

void SceneMain::Init()
{
	/*ポインタの生成*/
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i] = make_shared<RecoveredItem>(m_pPlayer);
	}

	/*画像のロード*/
	m_startHandle = LoadGraph("Data/Img/StartImg.png");
	m_clearHandle = LoadGraph("Data/Img/ClearImg.png");
	m_backHandle = LoadGraph("Data/Img/Back/Sky.png");
	/*モデルのロード*/
	m_groundModelHandle = MV1LoadModel("Data/Model/Ground.mv1");
	/*SEのロード*/
	m_fastClearSeHandle = LoadSoundMem("Data/Sound/SE/FastClearSE.mp3");
	m_clearSeHandle = LoadSoundMem("Data/Sound/SE/NormalClearSE.mp3");
	m_slowClearSeHandle = LoadSoundMem("Data/Sound/SE/SlowClearSE.mp3");
	/*BGMのロード*/
	m_startBgmHandle = LoadSoundMem("Data/Sound/BGM/StartBGM.mp3");
	m_mainBgmHandle = LoadSoundMem("Data/Sound/BGM/MainBGM.mp3");
	m_clearBgmHandle = LoadSoundMem("Data/Sound/BGM/ClearBGM.mp3");
	/*BGM、SEの音量の調整*/
	ChangeVolumeSoundMem(kSeVolume, m_fastClearSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_clearSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_slowClearSeHandle);
	ChangeVolumeSoundMem(kBgmVolume, m_startBgmHandle);
	ChangeVolumeSoundMem(kBgmVolume, m_mainBgmHandle);
	ChangeVolumeSoundMem(kBgmVolume, m_clearBgmHandle);
	/*フォントのロード*/
	m_timeFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 100, -1);
	m_itemFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 80, -1);
	m_clearTimeFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 70, -1);

	ItemInit();	
}

shared_ptr<SceneBase> SceneMain::Update(Input& input, HandleManager& handle)
{
	m_pCamera->Update(*m_pPlayer);

	//地面モデルの位置、大きさの設定
	MV1SetScale(m_groundModelHandle, VGet(kGroundModelScale, 1, kGroundModelScale));
	MV1SetPosition(m_groundModelHandle, VGet(0, kGroundPosY, 0));

	if (m_isStart)
	{
		StartUpdate(input);
	}
	else if (m_isPlay)
	{
		PlayUpdate(input,handle);
	}
	else if (m_isClear)
	{
		ClearUpdate(input);
	}
	else if(m_fadeAlpha >= 255)
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
	DrawGraph(0, 0, m_backHandle, false);
	SetWriteZBufferFlag(true);
	m_pPlayer->Draw(handle);
	// 地面モデルの描画
	MV1DrawModel(m_groundModelHandle);
	for (const auto& item : m_pItem)
	{
		item->Draw();
	}

	SetWriteZBufferFlag(false);
	if (m_isStart)
	{
		StartDraw();
	}
	else if (m_isPlay)
	{		
		PlayDraw();
	}
	else
	{
		ClearDraw();
	}

#ifdef _DEBUG
	// XYZ軸
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));
	DrawString(8, 8, "MainScene", 0xffffff);
#endif // DEBUG

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneMain::End()
{
	/*処理無し*/
}

void SceneMain::ItemInit()
{
	for (const auto& item : m_pItem)
	{
		// アイテムの位置をランダムにする
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
		item->Init(x, z);
	}
}

void SceneMain::StartUpdate(Input& input)
{
	if (!CheckSoundMem(m_startBgmHandle))
	{
		PlaySoundMem(m_startBgmHandle, DX_PLAYTYPE_LOOP);
	}
	
	if (input.IsTriggered("A"))
	{
		StopSoundMem(m_startBgmHandle);
		m_isPlay = true;
		m_isStart = false;
	}
}

void SceneMain::PlayUpdate(Input& input, HandleManager& handle)
{
	// 秒数
	m_timeFrame++;
	m_time = m_timeFrame / 60;

	// BGM
	if (!CheckSoundMem(m_mainBgmHandle))
	{
		PlaySoundMem(m_mainBgmHandle, DX_PLAYTYPE_LOOP);
	}

	m_itemNum = 0;
	for (const auto& item : m_pItem)
	{
		if (!item->IsExist())
		{
			m_itemNum++;
		}
	}
	if (kItemNum - m_itemNum == 0)
	{
		m_clearTime = m_time;
		StopSoundMem(m_mainBgmHandle);
		m_isClear = true;
		m_isPlay = false;
	}

	m_pPlayer->Update(input,handle);
	

	for (const auto& item : m_pItem)
	{
		item->Update();
	}

#ifdef _DEBUG
	if (input.IsTriggered("B"))
	{
		m_clearTime = m_time;
		StopSoundMem(m_mainBgmHandle);
		m_isClear = true;
		m_isPlay = false;
	}
#endif // _DEBUG


}

void SceneMain::ClearUpdate(Input& input)
{
	// SEの再生
	// クリアタイムによってSEの内容が変わる
	if (!m_isSe)
	{
		if (m_clearTime <= kClearFastTime)
		{			
			PlaySoundMem(m_fastClearSeHandle, DX_PLAYTYPE_NORMAL);
		}
		else if (m_clearTime > kClearFastTime && m_clearTime < kClearSlowTime)
		{
			PlaySoundMem(m_clearSeHandle, DX_PLAYTYPE_NORMAL);
		}
		else if (m_clearTime >= kClearSlowTime)
		{
			PlaySoundMem(m_slowClearSeHandle, DX_PLAYTYPE_NORMAL);
		}

		m_isSe = true;
	}
	// BGM
	if (!CheckSoundMem(m_clearBgmHandle))
	{
		PlaySoundMem(m_clearBgmHandle, DX_PLAYTYPE_LOOP);
	}
	

	if (input.IsTriggered("A"))
	{
		m_isClear = false;
	}
}

void SceneMain::StartDraw()
{
	DrawGraph(200, 100, m_startHandle, false);
}

void SceneMain::PlayDraw()
{
	TimeDraw();
	ItemNumDraw();
}

void SceneMain::ClearDraw()
{
	DrawGraph(200, 100, m_clearHandle, false);

	// 秒数の描画
	DrawFormatStringToHandle(kClearTimePosX + kBackFontShiftPosX, kClearTimePosY, 0x00008b, m_clearTimeFontHandle, "けっか：%dびょう！", m_clearTime);
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xff7f50, m_clearTimeFontHandle, "けっか：%dびょう！", m_clearTime);
}

void SceneMain::TimeDraw()
{
	// 秒数の描画
	DrawFormatStringToHandle(kTimePosX+kBackFontShiftPosX, kTimePosY, 0x00008b, m_timeFontHandle, "%dけいか", m_time);
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xff7f50, m_timeFontHandle, "%dけいか", m_time);
}

void SceneMain::ItemNumDraw()
{
	// 残りのアイテム数の描画
	DrawFormatStringToHandle(kItemPosX+kBackFontShiftPosX, kItemPosY, 0x000086, m_itemFontHandle, "のこり：%dこ", kItemNum - m_itemNum);
	DrawFormatStringToHandle(kItemPosX, kItemPosY, 0xff6347, m_itemFontHandle, "のこり：%dこ", kItemNum - m_itemNum);
}
