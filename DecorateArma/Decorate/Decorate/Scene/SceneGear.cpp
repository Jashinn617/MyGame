#include "SceneGear.h"

#include "../Object/Player/Gear.h"

SceneGear::SceneGear():
	m_pGear(std::make_shared<Gear>())
{
}

SceneGear::~SceneGear()
{
}

void SceneGear::Init()
{
}

std::shared_ptr<SceneBase> SceneGear::Update()
{
	return shared_from_this();
}

void SceneGear::Draw()
{

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "装備画面");
#endif // _DEBUG

}

void SceneGear::End()
{
}
