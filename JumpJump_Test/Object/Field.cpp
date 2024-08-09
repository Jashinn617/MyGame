#include "Field.h"
#include "Model.h"
#include "ObjectManager.h"
#include "Player/Player.h"

namespace
{
	// フィールドのファイル名
	const char* const kFileName[static_cast<int>(Game::Stage::StageName)]
	{
		"Data/Model/Stage/stage.mv1",
		"Data/Model/Stage/stage.mv1",
		"Data/Model/Stage/stage.mv1",
	};
}

Field::Field(Game::Stage stage)
{
	// モデルの生成
	m_pModel = std::make_shared<Model>(kFileName[static_cast<int>(stage)]);

	m_pModel->SetScale(VGet(1.0f, 1.0f, 1.0f));
	m_pModel->SetPos(VGet(0.0f, 0.0f, 0.0f));
}

Field::~Field()
{
}

void Field::Init()
{
}

void Field::Update(Input& input)
{
	m_pModel->Update();
}

void Field::Draw()
{
}
