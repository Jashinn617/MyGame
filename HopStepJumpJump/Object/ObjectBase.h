#pragma once
#include "DxLib.h"
#include "../Util/CharacterData.h"

#include <array>
#include <memory>

class Model;
class ObjectManager;
class Time;
class Player;
class Circle;
class ToonShader;
class ShadowMapShader;

namespace ColInfo
{
	// �ő哖���蔻��|���S����
	constexpr int kMaxColHitPolyNum = 2000;
	// �ǉ����o�������̍ő厎�s��
	constexpr int kMaxColHitTryNum = 16;
	// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kColHitSlideLength = 1.0f;
}

class ObjectBase
{
public:	// �񋓑�

	// ���̂̕���
	enum class ColType
	{
		None,		// ����
		Player,		// �v���C���[
		Enemy,		// �G�l�~�[
		Field,		// �t�B�[���h
		Item,		// �A�C�e��
	};

public:	// �֐�
	ObjectBase();

	virtual ~ObjectBase();

	virtual void Init();
	virtual void Update();

	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	/// <summary>
	/// �e�̕`��
	/// </summary>
	/// <param name="pShadoeMapShader"></param>
	virtual void ShadowMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader);

	/// <summary>
	/// 2D�̕`��
	/// </summary>
	virtual void Draw2D();

	/// <summary>
	/// �X�e�[�W�N���A��
	/// </summary>
	virtual void StageClear();

	/// <summary>
	///	�Q�[���I����
	/// </summary>
	virtual void GameEnd();

	/// <summary>
	/// �U��������������
	/// </summary>
	virtual void OnAttack();

	/// <summary>
	/// ���C���|�C���^�̐ݒ�
	/// </summary>
	/// <param name="objectManager"></param>
	void SetMain(ObjectManager* objectManager) { m_pObjectManager = objectManager; }

	/// <summary>
	/// ���f���n���h���̐ݒ�
	/// </summary>
	/// <param name="handle"></param>
	void SetModelHandle(int handle) { m_modelH = handle; }

	/// <summary>
	/// ���݂������Ă���̃J�E���g
	/// (���݂������Ă�����|��鉉�o�ŏ����̊Ԃ������f����`�悳���邽��)
	/// </summary>
	/// <returns></returns>
	bool IsExistCount();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// ���f���N���X�̎擾
	/// </summary>
	/// <returns>���f���N���X</returns>
	const std::shared_ptr<Model> GetModel() const { return m_pModel;}

	/// <summary>
	/// �L�����N�^�[���̎擾
	/// </summary>
	/// <returns>�L�����N�^�[���</returns>
	const CharacterData::CharacterInfo GetInfo() const { return m_info; }

	/// <summary>
	/// ���M�̓����蔻��̏��
	/// </summary>
	/// <returns>�����蔻����</returns>
	virtual ColType GetColType() const { return ColType::None; }


	bool IsGameEnd()const { return m_isGameEnd; }

	bool IsDamage() const { return m_isDamage; }


	/// <summary>
	/// �ړ��A�b�v�f�[�g
	/// </summary>
	/// <param name="pField"></param>
	void MoveCollFieldUpdate(ObjectBase* pField);

protected:	// �ϐ�
	std::shared_ptr<Model> m_pModel;	// ���f���N���X
	CharacterData::CharacterInfo m_info;	// �L�����N�^�[���	
	float m_objSize;	// �I�u�W�F�N�g�T�C�Y
	float m_angle;		// �L�����N�^�[�̌���
	float m_moveSpeed;	// �ړ��X�s�[�h
	int m_modelH;		// ���f���n���h��
	bool m_isDamage;	// �U�����󂯂���
	bool m_isGameEnd;	// �Q�[���I���������ǂ���

	ObjectManager* m_pObjectManager = nullptr;

private:	// �֐�
	// �`�F�b�N�����|���S�����ǃ|���S�������|���S�����𔻒f���ۑ�����
	void CheckWallAndFloor();
	// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
	void FixPosWithWall();
	void FixPosWithWallInternal();
	// ���|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
	void FixPosWithFloor();

private:	// �ϐ�
	bool m_isMove;	// �ړ��������ǂ���
	bool m_isHit;	// �|���S���ɓ����������ǂ���
	int m_wallNum;	// �ǂƔ��f���ꂽ�|���S����
	int m_floorNum;	// ���Ɣ��f���ꂽ�|���S����

	MV1_COLL_RESULT_POLY_DIM m_hitDim;		// �����蔻�茋�ʍ\����
	MV1_COLL_RESULT_POLY* m_pWallPoly[ColInfo::kMaxColHitPolyNum];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pFloorPoly[ColInfo::kMaxColHitPolyNum];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pPoly;	// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^
	HITRESULT_LINE m_lineRes;					// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����

	VECTOR m_oldPos;		// �ړ��O�̍��W
	VECTOR m_nextPos;		// �ړ���̍��W

	// ���݂������Ă���̎���
	std::shared_ptr<Time> m_pExistCountTime;
};

