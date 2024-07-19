#pragma once
#include "DxLib.h"
#include "../Util/CharacterData.h"

#include <array>
#include <memory>

class Model;

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
		Object,		// �I�u�W�F�N�g
		Item,		// �A�C�e��
	};

public:	// �֐�
	ObjectBase();

	virtual ~ObjectBase();

	virtual void Init() abstract;
	virtual void Update() abstract;

	virtual void Draw() abstract;

	virtual void Draw();

	virtual void Draw2D();

	/// <summary>
	/// ���݂������Ă���̃J�E���g
	/// (���݂������Ă�����|��鉉�o�ŏ����̊Ԃ������f����`�悳���邽��)
	/// </summary>
	/// <returns></returns>
	bool IsExistCount();

	/// <summary>
	/// �I�u�W�F�N�g���������̏���
	/// </summary>
	void End();

	// ���C���|�C���^�̐ݒ�

	// ���f���n���h���̐ݒ�

};

