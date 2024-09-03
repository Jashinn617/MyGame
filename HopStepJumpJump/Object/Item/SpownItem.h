#pragma once
#include "DxLib.h"

#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class ObjectBase;
class ObjectManager;

class SpownItem
{
public:
	SpownItem(const char* fileName, ObjectManager* pObjectManager);
	virtual ~SpownItem();

	void Init();

	void Spown();

	/// <summary>
	/// ���݂��Ă��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsExist();

	/// <summary>
	/// �A�C�e�����̎擾
	/// </summary>
	/// <returns></returns>
	int GetItemNum()const { return static_cast<int>(m_pData.size()); }

private:	// �\����
	struct Data
	{
		ObjectBase* pItem = nullptr;
		int index = 0;
		std::string name{};
	};

private:	// �֐�

	/// <summary>
	/// �A�C�e���̐���
	/// </summary>
	void Create();

	/// <summary>
	/// �A�C�e���̏o��
	/// </summary>
	void Appearance();

	/// <summary>
	/// �A�C�e���̒ǉ�
	/// </summary>
	/// <param name="createNum"></param>
	/// <param name="fileName"></param>
	/// <param name="pos"></param>
	void Add(int createNum, std::string fileName, VECTOR pos);

	/// <summary>
	/// ����̕��������o�����܂ŕ������v�b�V���o�b�N����
	/// </summary>
	/// <param name="input"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	std::vector<std::string> Split(std::string& input, char delimiter);

private:
	int m_createNum;					// �o���ԍ�
	const char* m_fileName;				// �t�@�C����
	std::list<Data*> m_pData;			// �A�C�e�����
	std::string m_line;					// �t�@�C�����̕�����
	ObjectManager* m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�|�C���^
};

