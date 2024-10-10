#pragma once
#include "DxLib.h"

#include <vector>
#include <memory>

/// <summary>
/// 3D���f���̊Ǘ����s���N���X
/// </summary>
class Model
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// �t�@�C�������w�肵�ă��[�h���s��
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	Model(const char* fileName);

	/// <summary>
	/// �R���X�g���N�^
	/// �w�肵���n���h���̃��f�����R�s�[�Ƃ��Đ�������
	/// </summary>
	/// <param name="modelH">���f���n���h��</param>
	Model(int modelH);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Model();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(VECTOR pos);

	/// <summary>
	/// �X�P�[���ݒ�
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void SetScale(VECTOR scale);

	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRot(VECTOR rot);

public:		// �֐�(�A�j���[�V��������)
	/// <summary>
	/// �A�j���[�V������ݒ肷��
	/// (�u�����h�����l�������ɐ؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX����A�j���[�V�����ԍ�</param>
	/// <param name="isLoop">�A�j���[�V���������[�v���邩</param>
	/// <param name="isForceChange">���Ɏw�肵���A�j���[�V�����ԍ��Ɠ����A�j���[�V�������Đ�����Ă��Ă��ύX�����邩</param>
	void SetAnim(int animNo, bool isLoop, bool isForceChange);

	/// <summary>
	/// �A�j���[�V������ω�������
	/// (�w�肵���t���[�������ăA�j���[�V������؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX����A�j���[�V�����ԍ�</param>
	/// <param name="changeFrameNum">�A�j���[�V������ω�������t���[����</param>
	/// <param name="isLoop">�A�j���[�V���������[�v���邩</param>
	/// <param name="isForceChange">���Ɏw�肵���A�j���[�V�����ԍ��Ɠ����A�j���[�V�������Đ�����Ă��Ă��ύX�����邩</param>
	void ChangeAnim(int animNo, int changeFrameNum, bool isLoop, bool isForceChange);

	/// <summary>
	/// ���݂̃A�j���[�V�������I���������ǂ����̎擾
	/// (Loop����A�j���[�V�����̏ꍇ��false��Ԃ�)
	/// </summary>
	/// <returns>�A�j���[�V�������I���������ǂ���</returns>
	bool IsAnimEnd();

private:	// �\����
	struct AnimData
	{
		int animNo;			// �A�j���[�V�����ԍ�
		int attachNo;		// �A�j���[�V�����A�^�b�`�ԍ�
		float totalTime;	// �A�j���[�V�����̑��Đ�����
		bool isLoop;		// �A�j���[�V���������[�v���邩�ǂ���
	};

private:	// �֐�
	/// <summary>
	/// �A�j���[�V�������̃N���A
	/// </summary>
	/// <param name="anim">�A�j���[�V�������</param>
	void ClearAnimData(AnimData& anim);

	/// <summary>
	/// �A�j���[�V�����X�V
	/// </summary>
	/// <param name="anim">�A�j���[�V�������</param>
	/// <param name="animSpeed">�A�j���[�V�������x</param>
	void UpdateAnim(AnimData anim, float animSpeed = 1.0f);

	/// <summary>
	/// �A�j���[�V�����̃u�����h����ݒ肷��
	/// </summary>
	void UpdateAnimBlendRate();

private:	// �ϐ�
	int m_modelH;					// ���f���n���h��
	int m_animSpeed;				// �A�j���[�V�������x
	int m_animChangeFrame;			// ���݂̐؂�ւ��t���[����
	int m_animChangeFrameTotal;		// �؂�ւ��ɂ����鑍�t���[����
	int m_animChangeSpeed;			// �A�j���[�V�����̕ύX���x
	int m_colFrameIndex;			// �����蔻��Ƃ��Ďg�p����t���[���̃C���f�b�N�X
	bool m_isUseCol;				// �����蔻��̏����g�p���邩�ǂ���
	bool m_isUpdateCol;				// �����蔻��̏����}�C�t���[���X�V���邩�ǂ���
	VECTOR m_pos;					// ���W
	AnimData m_prevAnim;			// �ύX�O�A�j���[�V����
	AnimData m_nextAnim;			// �ύX��A�j���[�V����
};

