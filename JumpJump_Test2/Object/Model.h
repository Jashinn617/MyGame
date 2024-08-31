#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>

class Model
{
public:	// �֐�

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
	/// <param name="ModelH"></param>
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
	/// �ʒu�̐ݒ�
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPos(VECTOR pos);

	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="scale">�T�C�Y</param>
	void SetScale(VECTOR scale);

	/// <summary>
	/// ��]��Ԃ̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRot(VECTOR rot);

	/// <summary>
	/// ���f���n���h���̎擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle()const { return m_modelH; }

	/// <summary>
	/// �����蔻��p�̃t���[���C���f�b�N�X�̎擾
	/// </summary>
	/// <returns></returns>
	int GetColFrameIndex() const { return m_colFrameIndex; }


	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>�ʒu</returns>
	VECTOR GetPos()const { return m_pos; }

	/*�A�j���[�V��������*/

	/// <summary>
	/// �A�j���[�V������ݒ肷��
	/// (�u�����h���ɍl�������ɐ؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX��̃A�j���[�V�����ԍ�</param>
	/// <param name="isLoop">�A�j���[�V���������[�v���邩</param>
	/// <param name="isForceChange">����animNo�Ɠ����A�j���[�V�������Đ�����Ă��Ă��ύX���邩</param>
	void SetAnim(int animNo, bool isLoop, bool isForceChange);

	/// <summary>
	/// �A�j���[�V������ω�������
	/// (changeFrame�����ăA�j���[�V������؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX��̃A�j���[�V�����ԍ�</param>
	/// <param name="isLoop">�A�j���[�V���������[�v���邩</param>
	/// <param name="isForceChange">����animNo�Ɠ����A�j���[�V�������Đ�����Ă��Ă��ύX���邩</param>
	/// <param name="changeFrameNum">�A�j���[�V������ω�������t���[����</param>
	void ChangeAnim(int animNo, bool isLoop, bool isForceChange, int changeFrameNum);

	/// <summary>
	/// ���݂̃A�j���[�V�������I�����Ă��邩�ǂ������擾����
	/// (Loop����A�j���[�V�����̏ꍇ�͎擾�ł��Ȃ�)
	/// </summary>
	/// <returns>�A�j���[�V�������I�����Ă��邩�ǂ���</returns>
	bool IsAnimEnd();

private:	// �\����
	// �A�j���[�V�������
	struct AnimData
	{
		int animNo;			// �A�j���[�V�����ԍ�
		int attachNo;		// �A�^�b�`�ԍ�
		float totalTime;	// �A�j���[�V�����̑��Đ�����
		bool isLoop;		// �A�j���[�V���������[�v����̂�
	};

private:	// �֐�
	/// <summary>
	/// �A�j���[�V�������̃N���A
	/// </summary>
	/// <param name="anim"></param>
	void ClearAnimData(AnimData& anim);

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	/// <param name="anim">�A�j���[�V�������</param>
	/// <param name="dt">�A�j���[�V�����X�s�[�h(�f�t�H���g��1.0f)</param>
	void UpdateAnim(AnimData anim, float animSpeed = 1.0f);

	/// <summary>
	// �A�j���[�V�����̃u�����h����ݒ肷��
	/// </summary>
	void UpdateAnimBlendRate();


private:	// �ϐ�
	VECTOR m_pos;					// �ʒu
	int m_modelH;					// ���f���n���h��
	int m_animSpeed;

	/*�A�j���[�V�����̐؂�ւ����*/
	int m_animChangeFrame;			// ���݂̐؂�ւ��t���[����
	int m_animChangeFrameTotal;		// �؂�ւ��ɂ����鑍�t���[����

	int m_animChangeSpeed;			// �A�j���[�V�����̕ύX���x
	int m_colFrameIndex;		// �����蔻��Ƃ��Ďg�p����t���[���̃C���f�b�N�X

	bool m_isUseCol;				// �����蔻��̏����g�p���邩�ǂ���
	bool m_isUpdateCol;				// �����蔻��̏��𖈃t���[���X�V���邩�ǂ���

	AnimData m_prevAnim;		// �ύX�O�̃A�j���[�V����
	AnimData m_nextAnim;		// �ύX��̃A�j���[�V����

};

