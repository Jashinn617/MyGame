#pragma once
#include "SceneBase.h"

class SkyDome;
class Camera;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	virtual SceneKind GetSceneKind() { return SceneKind::Title; }

private:	// �ϐ�
	int m_H1;	// �摜�n���h��
	int m_H2;	// �摜�n���h��
	int m_movieH;	// ����n���h��
	int m_TitlePosY;	// �^�C�g���ʒu
	bool m_IsPlayFallSE;	// �^�C�g���������������Ƃ���SE��炵�����ǂ���
};

