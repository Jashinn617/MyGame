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

	// 初期化
	virtual void Init() = 0;
	// 更新
	virtual shared_ptr<SceneBase> Update(Input& input) = 0;
	// 描画
	virtual void Draw() = 0;
	// シーン終了時の処理
	virtual void End() = 0;
};

