#pragma once

#include <memory>
#include <vector>

class ObjectBase;

class Collision
{
public:
	Collision();
	~Collision();

	void Init();

	/// <summary>
	/// �����蔻�菈��
	/// </summary>
	/// <param name="my"></param>
	/// <param name="target"></param>
	void Update(ObjectBase* my, ObjectBase* target);
};

