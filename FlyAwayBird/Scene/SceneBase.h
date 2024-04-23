#pragma once
#include "../Util/Input.h"
#include <memory>
#include <math.h>

using namespace std;

class SceneBase :public enable_shared_from_this<SceneBase>
{
public:
	SceneBase() {}
	virtual ~SceneBase() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <returns>���݂̃V�[��</returns>
	virtual shared_ptr<SceneBase> Update(Input& input) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �V�[���I�����̏���
	/// </summary>
	virtual void End() = 0;
};
