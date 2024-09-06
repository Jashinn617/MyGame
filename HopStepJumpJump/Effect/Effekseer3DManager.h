#pragma once
#include "EffekseerForDXLib.h"
#include "../Util/CsvLoad.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <list>

class ObjectBase;

class Effekseer3DManager
{
public:	// enum�N���X
	enum class PlayType
	{
		LoopFollow,	// ���[�v�A�Ǐ]
		Loop,		// ���[�v�̂�
		Follow,		// �Ǐ]�̂�
		Normal,		// ���̑�
	};
public:		// �N���X
	class EffectBehavior
	{
	public:
		virtual ~EffectBehavior() {};
		virtual void Update() {};
		virtual bool IsEnd() { return m_isEnd; }

		/// <summary>
		/// �G�t�F�N�g�f�[�^�̎擾
		/// </summary>
		/// <returns></returns>
		LoadData::EffectData GetData() const { return m_data; }

		void SetData(const char* FileName)
		{
			m_data = GetInstance().m_dataTable[FileName];
		}

	protected:	// �֐�
		// �Đ�
		virtual void Play() {};

	protected:	// �ϐ�
		bool m_isEnd;	// �G�t�F�N�g�̍Đ��I��
		LoadData::EffectData m_data;	// �G�t�F�N�g�f�[�^
	};

public:
	~Effekseer3DManager();

	static Effekseer3DManager& GetInstance()
	{
		// �B��̎���
		static Effekseer3DManager instance;

		// ���Ԃ̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �G�t�F�N�g�̒ǉ�
	/// </summary>
	/// <param name="fileName">�t�@�C���p�X</param>
	/// <param name="type">�G�t�F�N�g�̃^�C�v</param>
	/// <param name="pObject">�I�u�W�F�N�g�|�C���^</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">�p�x</param>
	void Add(const char* fileName, PlayType type, 
		ObjectBase* pObject = nullptr,
		VECTOR pos = VGet(0.0f, 0.0f, 0.0f), 
		VECTOR rot = VGet(0.0f, 0.0f, 0.0f));

	/// <summary>
	/// �G�t�F�N�g�̏���
	/// </summary>
	void Delete();

private:	// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���p�^�[���Ȃ̂�
	/// �R���X�g���N�^��private�ɒu��
	/// </summary>
	Effekseer3DManager();

	// �R�s�[���֎~����
	// �R�s�[�R���X�g���N�^
	Effekseer3DManager(const Effekseer3DManager&) = delete;
	// ������֎~����
	void operator=(const Effekseer3DManager&) = delete;

private:	// �ϐ�
	// �G�t�F�N�g�̃f�[�^�e�[�u��
	std::unordered_map<std::string, LoadData::EffectData> m_dataTable;

	// �G�t�F�N�g�̊Ǘ����X�g
	std::list<std::shared_ptr<EffectBehavior>> m_pEffect;
};

