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
	m_timeFrontFontHandle(-1),
	m_timeBackFontHandle(-1),
	m_itemFrontFontHandle(-1),
	m_itemBackFontHandle(-1),
	m_timeFrame(0),
	m_time(0),
	m_clearTime(0),
	m_itemNum(0),
	m_fadeAlpha(0),
	m_isStart(true),
	m_isPlay(false),
	m_isClear(false),
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
	/*フォントのデリート*/
	DeleteFontToHandle(m_timeFrontFontHandle);
	DeleteFontToHandle(m_timeBackFontHandle);
	DeleteFontToHandle(m_itemFrontFontHandle);
	DeleteFontToHandle(m_itemBackFontHandle);
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
	// 秒数表示用のフォント
	m_timeFrontFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 100, -1);
	m_timeBackFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 110, -1);
	m_itemFrontFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 80, -1);
	m_itemBackFontHandle = CreateFontToHandle("GN-キルゴUかなNA", 82, -1);

	ItemInit();	
}

shared_ptr<SceneBase> SceneMain::Update(Input& input)
{
	m_pCamera->Update(*m_pPlayer);

	if (m_isStart)
	{
		StartUpdate(input);
	}
	else if (m_isPlay)
	{
		PlayUpdate(input);
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

void SceneMain::Draw()
{
	DrawGraph(0, 0, m_backHandle, false);
	SetWriteZBufferFlag(true);
	m_pPlayer->Draw();
	for (const auto& item : m_pItem)
	{
		item->Draw();
	}

	SetWriteZBufferFlag(false);
	if (m_isStart)
	{
		DrawGraph(200, 100, m_startHandle, false);
	}
	else if (m_isPlay)
	{		
		TimeDraw();
		ItemNumDraw();
	}
	else
	{
		DrawGraph(200, 100, m_clearHandle, false);
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
	if (input.IsTriggered("A"))
	{
		m_isPlay = true;
		m_isStart = false;
	}
}

void SceneMain::PlayUpdate(Input& input)
{
	// 秒数
	m_timeFrame++;
	m_time = m_timeFrame / 60;

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
		m_isClear = true;
		m_isPlay = false;
	}

	m_pPlayer->Update(input);
	

	for (const auto& item : m_pItem)
	{
		item->Update();
	}

}

void SceneMain::ClearUpdate(Input& input)
{
	if (input.IsTriggered("A"))
	{
		m_isClear = false;
	}
}

void SceneMain::TimeDraw()
{
	// 秒数の描画
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0x00008b, m_timeBackFontHandle, "%dけいか", m_time);
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xff7f50, m_timeFrontFontHandle, "%dけいか", m_time);
}

void SceneMain::ItemNumDraw()
{
	// 残りのアイテム数の描画
	DrawFormatStringToHandle(kItemPosX, kItemPosY, 0x000086, m_itemBackFontHandle, "のこり：%dこ", kItemNum - m_itemNum);
	DrawFormatStringToHandle(kItemPosX, kItemPosY, 0xff6347, m_itemFrontFontHandle, "のこり：%dこ", kItemNum - m_itemNum);
}
