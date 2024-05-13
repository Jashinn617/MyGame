#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Util/Game.h"
#include "../RecoveredItem.h"

using namespace std;

SceneMain::SceneMain() :
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
	/*処理無し*/
}

void SceneMain::Init(HandleManager& handle)
{
	// ライトの設定
	// 標準のライトをディレクショナルライトにする
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));

	/*ポインタの生成*/
	m_pPlayer = make_shared<Player>();
	m_pPlayer->Init(handle);
	m_pCamera = make_shared<Camera>(m_pPlayer);
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i] = make_shared<RecoveredItem>(m_pPlayer);
	}
	ItemInit(handle);

	/*BGM、SEの音量の調整*/
	ChangeVolumeSoundMem(kSeVolume, handle.GetSound("fastClearSE"));
	ChangeVolumeSoundMem(kSeVolume, handle.GetSound("normalClearSE"));
	ChangeVolumeSoundMem(kSeVolume, handle.GetSound("slowClearSE"));
	ChangeVolumeSoundMem(kBgmVolume, handle.GetSound("startBGM"));
	ChangeVolumeSoundMem(kBgmVolume, handle.GetSound("mainBGM"));
	ChangeVolumeSoundMem(kBgmVolume, handle.GetSound("clearBGM"));

}

shared_ptr<SceneBase> SceneMain::Update(Input& input, HandleManager& handle)
{
	

	//地面モデルの位置、大きさの設定
	MV1SetScale(handle.GetModel("ground"), VGet(kGroundModelScale, 1, kGroundModelScale));
	MV1SetPosition(handle.GetModel("ground"), VGet(0, kGroundPosY, 0));

	if (m_isStart)
	{
		StartUpdate(input, handle);
	}
	else if (m_isPlay)
	{
		m_pCamera->Update(input);
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
	m_pPlayer->Draw(handle);
	// 地面モデルの描画
	MV1DrawModel(handle.GetModel("ground"));
	for (const auto& item : m_pItem)
	{
		item->Draw(handle);
	}

	SetWriteZBufferFlag(false);
	if (m_isStart)
	{
		StartDraw(handle);
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

void SceneMain::ItemInit(HandleManager& handle)
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
	if (!CheckSoundMem(handle.GetSound("mainBGM")))
	{
		PlaySoundMem(handle.GetSound("mainBGM"), DX_PLAYTYPE_LOOP);
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
		StopSoundMem(handle.GetSound("mainBGM"));
		m_isClear = true;
		m_isPlay = false;
	}

	m_pPlayer->Update(input, handle);


	for (const auto& item : m_pItem)
	{
		item->Update(handle);
	}

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
	// SEの再生
	// クリアタイムによってSEの内容が変わる
	if (!m_isSe)
	{
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

		m_isSe = true;
	}
	// BGM
	if (!CheckSoundMem(handle.GetSound("clearBGM")))
	{
		PlaySoundMem(handle.GetSound("clearBGM"), DX_PLAYTYPE_LOOP);
	}


	if (input.IsTriggered("A"))
	{
		m_isClear = false;
		StopSoundMem(handle.GetSound("clearBGM"));
	}
}

void SceneMain::StartDraw(HandleManager& handle)
{
	DrawGraph(200, 100, handle.GetImg("startScreen"), false);
}

void SceneMain::PlayDraw(HandleManager& handle)
{
	// 秒数の描画
	DrawFormatStringToHandle(kTimePosX + kBackFontShiftPosX, kTimePosY, 0x00008b, handle.GetFont("timeFont"), "%dけいか", m_time);
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xff7f50, handle.GetFont("timeFont"), "%dけいか", m_time);

	// 残りのアイテム数の描画
	DrawFormatStringToHandle(kItemPosX + kBackFontShiftPosX, kItemPosY, 0x000086, handle.GetFont("itemNumFont"), "のこり：%dこ", kItemNum - m_itemNum);
	DrawFormatStringToHandle(kItemPosX, kItemPosY, 0xff6347, handle.GetFont("itemNumFont"), "のこり：%dこ", kItemNum - m_itemNum);
}

void SceneMain::ClearDraw(HandleManager& handle)
{
	DrawGraph(200, 100, handle.GetImg("clearScreen"), false);

	// 秒数の描画
	DrawFormatStringToHandle(kClearTimePosX + kBackFontShiftPosX, kClearTimePosY, 0x00008b, handle.GetFont("clearTimeFont"), "けっか：%dびょう！", m_clearTime);
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xff7f50, handle.GetFont("clearTimeFont"), "けっか：%dびょう！", m_clearTime);
}