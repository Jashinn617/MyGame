#pragma once
class SaveData
{
public:
	~SaveData();

	static SaveData& GetInstance()
	{
		// �B��̎���
		static SaveData instance;

		// ���Ԃ̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �f�[�^�̓ǂݍ���
	/// </summary>
	void Load();

	/// <summary>
	/// �f�[�^�̏�������
	/// </summary>
	void Write();

	/// <summary>
	/// BGM�̉��ʕύX
	/// </summary>
	/// <param name="BGMVol"></param>
	void ChangeBGMVol(int BGMVol);

	/// <summary>
	/// SE�̉��ʕύX
	/// </summary>
	/// <param name="SEVol"></param>
	void ChangeSEVol(int SEVol);

	/*�R���t�B�O*/

	int GetBGMVol() const;
	
	int GetSEVol() const;

	/// <summary>
	/// �Z�[�u�f�[�^�̏㏑��(�V�K�ۑ�)
	/// </summary>
	void CreateNewSaveData();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���p�^�[���Ȃ̂�
	/// �R���X�g���N�^��private�ɒu��
	/// </summary>
	SaveData();
	
	// �R�s�[���֎~����
	SaveData(const SaveData&) = delete;	
	// ������֎~����
	void operator = (const SaveData&) = delete;

private:	// �֐�
	/// <summary>
	///	�f�[�^�̃N���A
	/// </summary>
	void ClearSaveData();

private:	// �\����
	struct Data
	{
		int version = 0;		// �f�[�^�̃o�[�W����
		unsigned int flag = 0;	// �e��t���O

		// �R���t�B�O
		int volBGM = 2;		// BGM����
		int volSE = 2;		// SE����
	};

	Data m_data;	// �Z�[�u�f�[�^
};

