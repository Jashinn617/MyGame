#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../RecoveredItem.h"

SceneMain::SceneMain():
	m_backHandle(-1),
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pItem(nullptr)
{

	
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_backHandle);
}

void SceneMain::Init()
{
	/*ポインタの生成*/
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pItem = make_shared<RecoveredItem>();

	/*画像のロード*/
	m_backHandle = LoadGraph("Data/Img/Back/Sky.png");

	m_pItem->Init();
}

shared_ptr<SceneBase> SceneMain::Update(Input& input)
{
	m_pPlayer->Update(input);
	m_pCamera->Update(*m_pPlayer);
	m_pItem->Update();

	return shared_from_this();
}

void SceneMain::Draw()
{
	DrawGraph(0, 0, m_backHandle, false);
	SetWriteZBufferFlag(true);
	m_pPlayer->Draw();
	m_pItem->Draw();
	SetWriteZBufferFlag(false);

#ifdef _DEBUG
	// XYZ軸
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));
	DrawString(8, 8, "MainScene", 0xffffff);
#endif // DEBUG
}

void SceneMain::End()
{
}
