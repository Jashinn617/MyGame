#pragma once
#include "../Util/Game.h"
#include "ObjectBase.h"

#include <memory>

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
	
	virtual void Draw() override final;

	/// <summary>
	/// ©g‚Ì“–‚½‚è”»’èî•ñ
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType() const override final { return ColType::Field; }

private:
};

