#pragma once
#include "ObjectBase.h"
#include "../Util/Game.h"

class Input;
class Model;

class Field : public ObjectBase
{
public:
	Field() {};
	Field(Game::Stage stage);
	~Field();

	void Init();
	void Update(Input& input) override final;
	
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	virtual void ShadowMapDraw(std::shared_ptr<ShadowMapShader> pShadoeMapShader) override final;

	virtual void Draw2D() override final;

	virtual void StageClear() override final;

	/// <summary>
	/// �Q�[���I��������
	/// </summary>
	void GameEnd() override final;

	/// <summary>
	/// ���g�̓����蔻����
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType() const override final { return ColType::Field; }

private:
};

