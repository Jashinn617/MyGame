#pragma once
#include <memory>

using namespace std;

class SceneBase:public enable_shared_from_this<SceneBase>
{
public:
	SceneBase(){}
	virtual ~SceneBase() {};

	// 初期化
	virtual void Init() = 0;
	// 更新
	virtual shared_ptr<SceneBase> Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// シーン終了時の処理
	virtual void End() = 0;
};

