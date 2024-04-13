#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class Player;
class Camera;
class Map;
class EnemyManager;
class Input;

/// <summary>
/// ���C���V�[��
/// </summary>
class MainScene:public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	void BackDraw();

	VECTOR m_bgPos;	// �w�i�̕\���ʒu
	int m_bgHandle;	// �w�i�摜
	int m_bgFrame;

	int m_time;

	int m_bgmHandle;


	struct BgSize	// �w�i�摜�̃T�C�Y
	{
		int width;
		int height;
	};

	/*�|�C���^�̎擾*/
	// �v���C���[
	shared_ptr<Player> m_pPlayer;
	// �J����
	shared_ptr<Camera> m_pCamera;
	// �}�b�v
	shared_ptr<Map> m_pMap;
	// �G�L�����N�^�[
	shared_ptr<EnemyManager> m_pEnemy;

private:	// �萔
	static constexpr float kBgScale = 0.5f;		// �w�i�摜�̃X�P�[���T�C�Y
	static constexpr float kBgSpeed = -1.0f;	// �w�i�̈ړ��X�s�[�h

	/*�w�i�̕`��ʒu*/
	static constexpr float kBgPosX = 0.0f;
	static constexpr float kBgPosY = 0.0f;
	static constexpr float kBgPosZ = 200.0f;

	static constexpr int kBgmVolume = 130;	// BGM�̉���
	static constexpr int kSeVolume = 255;	// SE�̉���
};

