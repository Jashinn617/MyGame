#pragma once
#include "ObjectBase.h"
#include "../Util/Game.h"

class Model;

class Field : public ObjectBase
{
public:
	Field() {};
	Field(Game::Stage stage);
	~Field();

	void Init();
	void Update() override final;
	
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	virtual void ShadowMapDraw(std::shared_ptr<ShadowMapShader> pShadoeMapShader) override final;

	virtual void Draw2D() override final;

	virtual void StageClear() override final;

	/// <summary>
	/// ゲーム終了時処理
	/// </summary>
	void StageEnd() override final;

	/// <summary>
	/// 自身の当たり判定情報
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType() const override final { return ColType::Field; }

private:
};

