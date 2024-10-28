#include "Field.h"
#include "Model.h"
#include "ObjectManager.h"
#include "Player/Player.h"

#include "../Shader/ToonShader.h"

#include <cassert>

Field::Field()
{
}

Field::Field(Game::StageKind stageKind)
{
	// モデル生成
	m_pModel = std::make_shared<Model>("Data/Model/Field/Stage1/Stage1.mv1");

	m_pModel->SetScale(VGet(0.4f, 0.4f, 0.4f));
	m_pModel->SetPos(VGet(0.0f, -300.0f, 0.0f));
}

Field::~Field()
{
}

void Field::Update()
{
	m_pModel->Update();
}

void Field::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// 描画
	m_pModel->Draw();
}
