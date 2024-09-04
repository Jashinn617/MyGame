#pragma once
#include "DxLib.h"
#include "ObjectBase.h"

#include <memory>
#include <vector>

class Input;
class Circle;
class Player;
class Time;

class Camera
{
public:
	Camera();
	~Camera();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W�̎擾</param>
	void Update(VECTOR playerPos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �J�����̍��W�̃��Z�b�g
	/// </summary>
	void ResetCamera();

	/// <summary>
	/// �����蔻��̍X�V
	/// </summary>
	/// <param name="Field"></param>
	void ColUpdate(ObjectBase* Field);

	/// <summary>
	/// �X�e�[�W�N���A���̃J�����̍X�V
	/// </summary>
	void StageClearUpdate();

	/// <summary>
	/// �X�e�[�W���N���A��
	/// </summary>
	/// <param name="angle"></param>
	/// <param name="targetPos"></param>
	void StageClear(float angle, VECTOR targetPos);

	/// <summary>
	/// �J������X�p�x�̎擾
	/// </summary>
	/// <returns></returns>
	float GetCameraAngleX() { return m_angleH; }
	
	/// <summary>
	/// �����蔻��̃T�[�N���擾
	/// </summary>
	/// <returns>�J�����̓����蔻��̃T�[�N���|�C���^</returns>
	const std::shared_ptr<Circle> GetCircle() const { return m_pCircle; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>�J�������W</returns>
	const VECTOR& GetPos() const { return m_nextPos; }

	/// <summary>
	/// �J�������W�̐ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(VECTOR pos) { m_nextPos = pos; }

	/// <summary>
	/// �O�t���[���̃J�����̍��W�̎擾
	/// </summary>
	/// <returns></returns>
	const VECTOR& GetPrevPos()const { return m_prevPos; }


private:	// �֐�
	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// �ʏ펞�̍X�V
	/// </summary>
	/// <param name="targetPos"></param>
	void NormalUpdate(VECTOR targetPos);

	/// <summary>
	/// ���W�̍X�V
	/// </summary>
	void UpdatePos();

	/// <summary>
	/// �����蔻����l���������W�X�V
	/// </summary>
	void FixPos();

	/// <summary>
	/// �����o������
	/// </summary>
	void FixPosInternal();


private:	// �ϐ�
	float m_angleH;	// �����p�x
	float m_angleV;	// �����p�x
	float m_cameraToTargetLenght;	// �J��������^�[�Q�b�g�܂ł̋���
	float m_clearCameraToTargetLength; // �X�e�[�W�N���A���̃J��������^�[�Q�b�g�܂ł̋���
	float m_stageClearEasingTime;		// �Q�[���N���A���̃C�[�W���O�ɂ����鎞��
	float m_stageClearTargetEasingTime;	// �Q�[���N���A���̃^�[�Q�b�g�̈ړ����̃C�[�W���O�ɂ����鎞��
	bool m_isStageClear;	// �X�e�[�W���N���A������

	VECTOR m_pos;		// ���W
	VECTOR m_nextPos;	// ���̍��W
	VECTOR m_prevPos;	// �O�̍��W
	VECTOR m_targetPos;	// �^�[�Q�b�g�̍��W
	VECTOR m_leftVec;	// �J��������^�[�Q�b�g�܂ł̃x�N�g�����猩�č������̃x�N�g��
	VECTOR m_stageClearTargetStartPos;	// �X�e�[�W�N���A���̃^�[�Q�b�g�̏������W
	VECTOR m_stageClearTargetEndPos;	// �X�e�[�W�N���A���̃^�[�Q�b�g�̍ŏI���W

	MATRIX m_rotX;	// ��]�p�s��X
	MATRIX m_rotY;	// ��]�p�s��Y

	std::shared_ptr<Circle> m_pCircle;	// �����蔻��̃|�C���^
	std::shared_ptr<Time> m_pClearTargetStartMoveTime;	// �X�e�[�W�N���A���̃^�[�Q�b�g���ړ�����܂ł̈ړ�����


	/*�����蔻��p�̏��*/
	bool m_isMove;		// �ړ��������ǂ���
	bool m_isHit;		// �|���S���ɓ���������
	
	MV1_COLL_RESULT_POLY_DIM m_hitDim{};								// �����蔻��̌��ʂ�����\����
	MV1_COLL_RESULT_POLY* m_pPolyIndex[ColInfo::kMaxColHitPolyNum]{};	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����邽�߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pPoly;									// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^
	HITRESULT_LINE m_lineRes{};										// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
};

