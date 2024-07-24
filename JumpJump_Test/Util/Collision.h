#pragma once

#include <memory>
#include <vector>

class ObjectBase;

class Collision
{
	Collision();
	~Collision();

	void Init();

	/// <summary>
	/// “–‚½‚è”»’èˆ—
	/// </summary>
	/// <param name="my"></param>
	/// <param name="target"></param>
	void Update(ObjectBase* my, ObjectBase* target);
};

