#pragma once
#include "../Utility/CharacterData.h"

#include <memory>
#include <vector>

class Model;
class VertexShader;
class ObjectManager;

class ToonShader;
class ShadowMapShader;

namespace ColInfo
{
	constexpr int kMaxColHitPolyNum = 2000;		// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;		// �ǉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;	// �ǉ����o�����ɃX���C�h�����鋗��
}

/// <summary>
/// �I�u�W�F�N�g�̊��N���X
/// </summary>
class ObjectBase
{
public:	// �񋓌^
	/// <summary>
	/// �����蔻��̎��
	/// </summary>
	enum class ColType
	{
		None,	// ����
		Player,	// �v���C���[
		Enemy,	// �G�l�~�[
		Field,	// �t�B�[���h
		Item,	// �A�C�e��
	};

public:	// �p���p�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ObjectBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ObjectBase();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pToonShader">�g�D�[���V�F�[�_�|�C���^</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) = 0;

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// �e�̕`��
	/// </summary>
	/// <param name="pShadowMapShader">�V���h�E�}�b�v�V�F�[�_�|�C���^</param>
	virtual void ShaderMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader);

	/// <summary>
	/// 2D�̕`��
	/// </summary>
	virtual void Draw2D() {/*��������*/ };

	/// <summary>
	/// �X�e�[�W�N���A������
	/// </summary>
	virtual void StageClear() {/*��������*/ };

	/// <summary>
	/// �U������
	/// </summary>
	virtual void OnAttack() {/*��������*/ };

	/// <summary>
	/// ���g�̓����蔻��̏��̎擾
	/// </summary>
	/// <returns>�����蔻����</returns>
	virtual ColType GetColType() const { return ColType::None; }

public:	// �p���p�ȊO�̃p�u���b�N�֐�

	/// <summary>
	/// �I�u�W�F�N�g�}�l�[�W���[�̐ݒ�
	/// </summary>
	/// <param name="objectManager">�I�u�W�F�N�g�}�l�[�W���[�|�C���^</param>
	void SetObjectManager(ObjectManager* objectManager) { m_pObjectManager = objectManager; }

	/// <summary>
	/// ���f���n���h���̐ݒ�
	/// </summary>
	/// <param name="handle">���f���n���h��</param>
	void SetModelHandle(int handle) { m_modelH = handle; }

	/// <summary>
	/// ���f���N���X�̎擾
	/// </summary>
	/// <returns>���f���N���X</returns>
	const std::shared_ptr<Model> GetModel()const { return m_pModel; }

	/// <summary>
	/// �L�����N�^�[���̎擾
	/// </summary>
	/// <returns>�L�����N�^�[���</returns>
	const CharacterData::CharacterInfo GetInfo()const { return m_characterInfo; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const VECTOR& GetPos()const { return m_characterInfo.pos; }

	/// <summary>
	/// �_���[�W���󂯂Ă��邩
	/// </summary>
	/// <returns>�_���[�W���󂯂Ă��邩�ǂ���</returns>
	bool IsDamage() const { return m_isDamage; }

	/// <summary>
	/// �t�B�[���h�Ƃ̓����蔻����l�������ړ�
	/// </summary>
	/// <param name="pField">�t�B�[���h�|�C���^</param>
	void MoveCollField(ObjectBase* pField);

protected:	// �ϐ�
	int m_modelH;									// ���f���n���h��
	float m_objSize;								// �I�u�W�F�N�g�T�C�Y
	float m_angle;									// �L�����N�^�[�̌���
	float m_moveSpeed;								// �ړ��X�s�[�h
	bool m_isDamage;								// �U�����󂯂����ǂ���
	std::shared_ptr<Model> m_pModel;				// ���f���N���X�|�C���^
	std::shared_ptr<VertexShader> m_pVertexShader;	// ���_�V�F�[�_�|�C���^
	std::vector<int> m_vertexShaderType;			// ���_�V�F�[�_�^�C�v
	std::vector<int> m_vertexShaderH;				// ���_�V�F�[�_�n���h��
	ObjectManager* m_pObjectManager;				// �I�u�W�F�N�g�}�l�[�W���[�|�C���^
	CharacterData::CharacterInfo m_characterInfo;	// �L�����N�^�[���

private:	 // �֐�
	/// <summary>
	/// �`�F�b�N�����|���S�����ǃ|���S�������|���S������
	/// ���f���ĕۑ�����
	/// </summary>
	void CheckWallAndFloor();

	/// <summary>
	/// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���Ĉړ�������
	/// </summary>
	void FixPosWithWall();

	/// <summary>
	/// �ǂ���̉����o������������
	/// </summary>
	void FixPosWithWallInternal();

	/// <summary>
	/// ���|���S���Ƃ̓����蔻����`�F�b�N���Ĉړ�������
	/// </summary>
	void FixPosWithFloor();

private:	// �ϐ�
	int m_wallNum;			// �ǂƔ��f���ꂽ�|���S���̐�
	int m_floorNum;			// ���Ɣ��f���ꂽ�|���S���̐�
	bool m_isMove;			// �ړ������ǂ���
	bool m_isPolyHit;		// �|���S���ɓ����������ǂ���
	VECTOR m_prevPos;		// �ړ��O�̍��W
	VECTOR m_nextPos;		// �ړ���̍��W
	
	MV1_COLL_RESULT_POLY_DIM m_hitDin{};								// �����蔻�茋�ʑ���p�|���S���\����
	MV1_COLL_RESULT_POLY* m_pWallPoly[ColInfo::kMaxColHitPolyNum]{};	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pFloorPoly[ColInfo::kMaxColHitPolyNum]{};	// ���|���S���Ɣ��f���ꂽ�|���S���̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_pPoly;										// �|���S���̍\���̂ɃA�N�Z�X����ׂɎg�p����|�C���^
	HITRESULT_LINE m_lineRes{};											// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
};

