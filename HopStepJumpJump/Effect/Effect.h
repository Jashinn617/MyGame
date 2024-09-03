#pragma once
#include "Effekseer3DManager.h"

#include <memory>

// 追従とループをするエフェクトのクラス
class EffectLoopFollow : public Effekseer3DManager::EffectBehavior
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="FileName">ファイルパス</param>
	/// <param name="pObject">オブジェクト</param>
	EffectLoopFollow(const char* FileName, ObjectBase* pObject);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EffectLoopFollow();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override final;

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	void Play() override final;

private:
	ObjectBase* m_pObject;	// オブジェクト
};

// 追従するエフェクトのクラス
class EffectFollow : public Effekseer3DManager::EffectBehavior
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="FileName">ファイルパス</param>
	/// <param name="pObject">オブジェクト</param>
	EffectFollow(const char* FileName, ObjectBase* pObject);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EffectFollow();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override final;

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	void Play() override final;

private:
	ObjectBase* m_pObject;	// オブジェクト
};

// ループするエフェクトのクラス
class EffectLoop : public Effekseer3DManager::EffectBehavior
{

};

// その他のエフェクトのクラス
class EffectNormal : public Effekseer3DManager::EffectBehavior
{

};

