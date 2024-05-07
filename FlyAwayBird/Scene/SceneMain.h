#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class RecoveredItem;

/// <summary>
/// ���C���V�[���N���X
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:	// �֐�
	void ItemInit();

	void StartUpdate(Input& input);
	void PlayUpdate(Input& input);
	void ClearUpdate(Input& input);

	void StartDraw();
	void PlayDraw();
	void ClearDraw();

	void TimeDraw();
	void ItemNumDraw();

private:	// �ϐ�
	int m_startHandle;	// �X�^�[�g��ʂ̉摜�n���h��
	int m_clearHandle;	// �N���A��ʂ̉摜�n���h��
	int m_backHandle;	// �w�i�̃n���h��
	int m_groundModelHandle;	// �n�ʂ̃��f���n���h��
	int m_fastClearSeHandle;		// �S�[������SE(30�b�ȉ�)
	int m_clearSeHandle;			// �S�[������SE
	int m_slowClearSeHandle;		// �S�[������SE(50�b�ȏ�)
	int m_startBgmHandle;			// �X�^�[�g��ʂ�BGM
	int m_mainBgmHandle;			// �v���C���O��ʂ�BGM
	int m_clearBgmHandle;			// �N���A��ʂ�BGM
	int m_timeFontHandle;		// �b���\���p�̃t�H���g�̃n���h��(�O)
	int m_itemFontHandle;	// �A�C�e���\���p�̃t�H���g�̃n���h��(�O)
	int m_clearTimeFontHandle;	// �N���A�^�C���\���p�̃t�H���g�̃n���h��(�O)
	int m_timeFrame;	// �o�߃t���[��
	int m_time;			// �o�ߕb��
	int m_clearTime;	// �N���A���̕b��
	int m_itemNum;		// �Ƃ����A�C�e����
	int m_fadeAlpha;	// �t�F�[�h�C���E�A�E�g�̔Z��
	bool m_isStart;		// �X�^�[�g��ʂ��ǂ���
	bool m_isPlay;		// �v���C��ʂ��ǂ���
	bool m_isClear;		// �S�[����ʂ��ǂ���
	bool m_isSe;		// SE���Ȃ������ǂ���

	/*�|�C���^*/
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
	//shared_ptr<RecoveredItem> m_pItem;
	vector<shared_ptr<RecoveredItem>> m_pItem;

private:	 // �萔
	static constexpr float kWallZ = 30;				// z���̕�
	static constexpr float kWallX = 50;				// x���̕�
	static constexpr int kItemNum = 20;				// �A�C�e���̐�
	static constexpr int kBgmVolume = 130;			// BGM�̉���
	static constexpr int kSeVolume = 255;			// SE�̉���
	static constexpr int kFadeSpeed = 4;			// �t�F�[�h�̃X�s�[�h
	static constexpr float kGroundModelScale = 20;	// �n�ʃ��f���̃X�P�[��
	static constexpr float kGroundPosY = -1.2;		// �n�ʂ�Y�ʒu
	/*�b���̕\���ʒu*/
	static constexpr int kTimePosX = 600;			// �b����X�ʒu
	static constexpr int kTimePosY = 40;			// �b����Y�ʒu
	static constexpr int kItemPosX = 550;			// �A�C�e����X�ʒu
	static constexpr int kItemPosY = 150;			// �A�C�e����Y�ʒu
	static constexpr int kClearTimePosX = 500;		// �N���A�^�C����X�ʒu
	static constexpr int kClearTimePosY = 120;		// �N���A�^�C����Y�ʒu
	static constexpr int kBackFontShiftPosX = 10;		// ���̃t�H���g�����炷�ʒu
	/*�N���A���̃^�C��*/
	static constexpr int kClearFastTime = 30;
	static constexpr int kClearSlowTime = 50;
};