#pragma once
#include "DxLib.h"

#include "ObjectBase.h"

#include <memory>

class Sphere;

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Camera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Camera();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="playerPos">�v���C���[���W</param>
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
	/// <param name="Field">�t�B�[���h�|�C���^</param>
	void ColUpdate(ObjectBase* Field);

	/// <summary>
	/// �J�����̐����p�x�̎擾
	/// </summary>
	/// <returns>�J���������p�x</returns>
	float GetCameraAngleX() { return m_angleH; }

	/// <summary>
	/// �����蔻��̋��̎擾
	/// </summary>
	/// <returns>�J�����̓����蔻��̋��|�C���^</returns>
	const std::shared_ptr<Sphere> GetCircle() const { return m_pSphere; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>�J�������W</returns>
	const VECTOR& GetPos() const { return m_nextPos; }

	/// <summary>
	/// �J�������W�̐ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPos(VECTOR pos) { m_nextPos = pos; }

	/// <summary>
	/// �O�t���[���̃J�����̍��W�̎擾
	/// </summary>
	/// <returns>�O�t���[���J�������W</returns>
	const VECTOR& GetPrevPos()const { return m_prevPos; }

private:	// �֐�
	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// �ʏ펞�̍X�V
	/// </summary>
	/// <param name="targetPos">�^�[�Q�b�g���W</param>
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
	float m_angleH;						// �����p�x
	float m_angleV;						// �����p�x
	float m_cameraToTargetLenght;		// �J��������^�[�Q�b�g�܂ł̋���
	VECTOR m_pos;						// ���W
	VECTOR m_nextPos;					// ���̍��W
	VECTOR m_prevPos;					// �O�̍��W
	VECTOR m_targetPos;					// �J��������^�[�Q�b�g�̍��W
	MATRIX m_rotX;						// ��]�p�s��X
	MATRIX m_rotY;						// ��]�p�s��Y
	std::shared_ptr<Sphere> m_pSphere;	// �����蔻��|�C���^

private:	// �����蔻��p�ϐ�
	bool m_isMove;		// �ړ��������ǂ���
	bool m_isPolyHit;	// �|���S���ɓ����������ǂ���

	MV1_COLL_RESULT_POLY_DIM m_hitDim{};									// �����蔻�茋�ʑ���p�|���S���\����
	MV1_COLL_RESULT_POLY* m_pPolyIndex[ColInfo::kMaxColHitPolyNum]{};	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pPoly;											// �|���S���̍\���̂ɃA�N�Z�X����ׂɎg�p����|�C���^
	HITRESULT_LINE m_lineRes{};												// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
};