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
	~Field();

	void Init();
	void Update(Input& input) override final;

	/// <summary>
	/// ©g‚Ì“–‚½‚è”»’èî•ñ
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType() const override final { return ColType::Field; }
};

