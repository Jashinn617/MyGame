#pragma once
#include "DxLib.h"

#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class ObjectBase;
class ObjectManager;

class SpownEnemy
{
public:
	SpownEnemy(const char* fileName, ObjectManager* pObjectManager);
	virtual ~SpownEnemy();

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
	int GetEnemyNum()const { return static_cast<int>(m_pData.size()); }

private:	// �\����
	struct Data
	{
		ObjectBase* pEnemy = nullptr;
		int index = 0;
		std::string name{};
	};

private:	// �֐�
	/// <summary>
	/// �G�̐���
	/// </summary>
	void Create();

	/// <summary>
	/// �G�̏o��
	/// </summary>
	void Appearance();

	/// <summary>
	/// �G�̒ǉ�
	/// </summary>
	/// <param name="createNum"></param>
	/// <param name="fileName"></param>
	/// <param name="pos"></param>
	void Add(int createNum, std::string enemyName, VECTOR pos, VECTOR direction, int turnTime, float speed);

	/// <summary>
	/// ����̕��������o�����܂ŕ������v�b�V���o�b�N����
	/// </summary>
	/// <param name="input"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	std::vector<std::string> Split(std::string& input, char delimiter);

private:	// �ϐ�
	int m_createNum;	// �o���ԍ�
	const char* m_fileName;	// �t�@�C����
	std::list<Data*> m_pData;	// �G���
	std::string m_line;			// �t�@�C�����̕�����
	ObjectManager* m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�|�C���^
};

