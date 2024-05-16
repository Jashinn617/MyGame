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

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Init(HandleManager& handle);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	/// <returns>�V�[���|�C���^</returns>
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Draw(HandleManager& handle);
	/// <summary>
	/// �I������
	/// </summary>
	virtual void End();

private:	// �֐�
	/// <summary>
	/// �A�C�e���̏�����
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void ItemInit(HandleManager& handle);

	/// <summary>
	/// �X�^�[�g��ʂ̍X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void StartUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// �J�E���g�_�E���̍X�V
	/// </summary>
	/// /// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void CountdownUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// �v���C��ʂ̍X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void PlayUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// �N���A��ʂ̍X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void ClearUpdate(Input& input, HandleManager& handle);

	/// <summary>
	/// �X�^�[�g��ʂ̕`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void StartDraw(HandleManager& handle);
	/// <summary>
	/// �J�E���g�_�E����ʂ̕`��
	/// </summary>
	/// <param name="handle"></param>
	void CountdownDraw(HandleManager& handle);
	/// <summary>
	/// �v���C��ʂ̕`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void PlayDraw(HandleManager& handle);
	/// <summary>
	/// �N���A��ʂ̕`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void ClearDraw(HandleManager& handle);
	/// <summary>
	/// �w�i�̕`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void BackDraw(HandleManager& handle);

private:	// �ϐ�
	float m_scrollX;			// �w�i�̃X�N���[��
	int m_shadowMapHandle;		// �V���h�E�}�b�v�̃n���h��
	int m_timeFrame;			// �o�߃t���[��
	int m_time;					// �o�ߕb��
	int m_clearTime;			// �N���A���̕b��
	int m_itemNum;				// �Ƃ����A�C�e����
	int m_fadeAlpha;			// �t�F�[�h�C���E�A�E�g�̔Z��
	int m_countdownFrame;		// �J�E���g�_�E���̌o�߃t���[��
	double m_countdownScale;	// �J�E���g�_�E���̃X�P�[��
	bool m_isStart;				// �X�^�[�g��ʂ��ǂ���
	bool m_isCountdown;			// �J�E���g�_�E�������ǂ���
	bool m_isPlay;				// �v���C��ʂ��ǂ���
	bool m_isClear;				// �S�[����ʂ��ǂ���
	bool m_isSe;				// SE���Ȃ������ǂ���

	/*�|�C���^*/
	shared_ptr<Player> m_pPlayer;					// �v���C���[�̃|�C���^
	shared_ptr<Camera> m_pCamera;					// �J�����̃|�C���^
	vector<shared_ptr<RecoveredItem>> m_pItem;		// �A�C�e���̃|�C���^

	// �w�i�摜�̃T�C�Y
	struct BgSize	
	{
		int width;	// ��
		int height;	// �c
	};

private:	 // �萔
	static constexpr float kWallZ = 30;						// z���̕�
	static constexpr float kWallX = 50;						// x���̕�
	static constexpr int kItemNum = 20;						// �A�C�e���̐�
	static constexpr int kFadeSpeed = 2;					// �t�F�[�h�̃X�s�[�h
	static constexpr float kGroundModelScale = 20;			// �n�ʃ��f���̃X�P�[��
	static constexpr float kGroundPosY = -1.2f;				// �n�ʂ�Y�ʒu
	static constexpr float kCountdownTime = 3 * 60;			// �J�E���g�_�E��������b��
	static constexpr float kOneSecond = 60;					// 1�b
	static constexpr float kTwoSecond = 120;				// 2�b
	static constexpr double kCountdownShrinkSpeed = 0.01;	// �J�E���g�_�E���̕b�����k�܂�X�s�[�h
	static constexpr double kCountdownMaxScale = 0.2;		// �J�E���g�_�E���̍ő�X�P�[��
	static constexpr int kScreenPosX = 200;					// �X�^�[�g�A�N���A�̉摜��X�ʒu
	static constexpr int kScreenPosY = 80;					// �X�^�[�g�A�N���A�̉摜��Y�ʒu
	static constexpr float kScrollSpeed = 1.5f;				// �w�i�̃X�N���[���X�s�[�h
	static constexpr int kIndexBack = 2;					// �X�N���[���ɕK�v�Ȕw�i�̐�
	static constexpr int kLogoX = 200;						// �X�^�[�g�A�N���A�̃��S��X�ʒu
	static constexpr int kLogoY = 640;						// �X�^�[�g�A�N���A�̃��S��Y�ʒu
	/*�b���̕\���ʒu*/
	static constexpr int kCountdownPosX = 800;				// �J�E���g�_�E����X�ʒu
	static constexpr int kCountdownPosY = 200;				// �J�E���g�_�E����Y�ʒu
	static constexpr int kGoPosX = 800;						// Go�̕�����X�ʒu
	static constexpr int kGoPosY = 300;						// Go�̕�����Y�ʒu
	static constexpr int kTimePosX = 600;					// �b����X�ʒu
	static constexpr int kTimePosY = 40;					// �b����Y�ʒu
	static constexpr int kItemPosX = 550;					// �A�C�e����X�ʒu
	static constexpr int kItemPosY = 150;					// �A�C�e����Y�ʒu
	static constexpr int kClearTimePosX = 500;				// �N���A�^�C����X�ʒu
	static constexpr int kClearTimePosY = 150;				// �N���A�^�C����Y�ʒu
	static constexpr int kBackFontShiftPosX = 10;			// ���̃t�H���g�����炷�ʒu
	static constexpr int kFrontCharColor = 0x00008b;		// ��O���̕����̐F
	static constexpr int kBackCharColor = 0xff6347;			// ��둤�̕����̐F
	/*�N���A���̃^�C��*/
	static constexpr int kClearFastTime = 25;				// �����N���A
	static constexpr int kClearSlowTime = 45;				// �x���N���A
	/*�V���h�E�}�b�v*/
	static constexpr int kShadowMapSizeX = 1024;							// �V���h�E�}�b�v�̃T�C�YX
	static constexpr int kShadowMapSizeY = 1024;							// �V���h�E�}�b�v�̃T�C�YY
	static constexpr VECTOR kShadowMapRangeMin = { -55.0f,-1.2f,-35.0f };	// �V���h�E�}�b�v��`�悷��ő�͈�
	static constexpr VECTOR kShadowMapRangeMax = { 55.0f,10.0f,35.0f };		// �V���h�E�}�b�v��`�悷��ŏ��͈�
	static constexpr VECTOR kShadowMapLightDir = { 0.01f, -0.5f, 0.0f };	// �V���h�E�}�b�v���z�肷�郉�C�g�̕���
	
	static constexpr VECTOR kLightDir = { 0.0f,-0.5f,0.0f };				// ���C�g�̕���
};