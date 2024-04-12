#pragma once
#include <memory>
#include "../Input.h"
#include <math.h>

using namespace std;

class SceneBase:public enable_shared_from_this<SceneBase>
{
public:
	SceneBase(){}
	virtual ~SceneBase() {};

	// ������
	virtual void Init() = 0;
	// �X�V
	virtual shared_ptr<SceneBase> Update(Input& input) = 0;
	// �`��
	virtual void Draw() = 0;
	// �V�[���I�����̏���
	virtual void End() = 0;
};

