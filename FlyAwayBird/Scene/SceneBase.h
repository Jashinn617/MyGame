#pragma once
#include "../Util/Input.h"
#include "../Util/HandleManager.h"
#include "../Util/Game.h"
#include <memory>
#include <math.h>

using namespace std;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBase :public enable_shared_from_this<SceneBase>
{
public:
	SceneBase() {}
	virtual ~SceneBase() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Init(HandleManager& handle) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	/// <returns>�V�[���|�C���^</returns>
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Draw(HandleManager& handle) = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void End() = 0;
};
