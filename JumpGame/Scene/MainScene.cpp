#include "MainScene.h"
#include "../Player.h"
#include "DxLib.h"

MainScene::MainScene():
	m_pPlayer(nullptr)
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	m_pPlayer = make_shared<Player>();
}

shared_ptr<SceneBase> MainScene::Update()
{
	m_pPlayer->Update();

	// シーン移動しないときは自身のポインタを返す
	return shared_from_this();
}

void MainScene::Draw()
{
	m_pPlayer->Draw();

	DrawString(8, 8, "MainScene", 0xffffff);
}

void MainScene::End()
{
}
