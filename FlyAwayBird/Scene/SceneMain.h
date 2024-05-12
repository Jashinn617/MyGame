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
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle);
	virtual void Draw(HandleManager& handle);
	virtual void End();

private:	// �֐�
	void ItemInit();

	void StartUpdate(Input& input, HandleManager& handle);
	void PlayUpdate(Input& input, HandleManager& handle);
	void ClearUpdate(Input& input, HandleManager& handle);

	void StartDraw(HandleManager& handle);
	void PlayDraw(HandleManager& handle);
	void ClearDraw(HandleManager& handle);

	void TimeDraw(HandleManager& handle);
	void ItemNumDraw(HandleManager& handle);

private:	// �ϐ�
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