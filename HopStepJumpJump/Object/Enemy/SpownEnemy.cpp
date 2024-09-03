#include "SpownEnemy.h"

#include "EnemyBase.h"
#include "EnemyBee.h"
#include "EnemySkull.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"

#include <assert.h>

namespace
{
	constexpr float kHeightPos = 10.0f;	// ��������
}

SpownEnemy::SpownEnemy(const char* fileName, ObjectManager* pObjectManager):
	m_createNum(0),
	m_fileName(fileName),
	m_pObjectManager(pObjectManager)
{
	// �A�C�e���̐���
	Create();
}

SpownEnemy::~SpownEnemy()
{
	std::list<Data*>::iterator it = m_pData.begin();
	while (it != m_pData.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pData.erase(it);
	}
}

void SpownEnemy::Init()
{
}

void SpownEnemy::Spown()
{
	Appearance();
}

bool SpownEnemy::IsExist()
{
	// �A�C�e���̃f�[�^���Ȃ������ꍇ
	if (m_pData.size() == 0) return false;

	// �A�C�e���̑S�f�[�^�𒲂ׂ�
	for (auto& data : m_pData)
	{
		// �A�C�e�������݂��Ă����ꍇ
		if (data->pEnemy->GetInfo().isExist)
		{
			return true;
		}
	}

	return false;
}

void SpownEnemy::Create()
{
	// �t�@�C����
	std::ifstream ifs(m_fileName);

	while (getline(ifs, m_line))
	{
		// csv�f�[�^��1�s��','�ŕ����̕�����ɕ�������
		std::vector<std::string> strvec = Split(m_line, ',');

		// strvec[0]	: �o���ԍ�				int
		// strvec[1]	: �A�C�e���̎��		string
		// strvec[2]	: �A�C�e����X���W		float
		// strvec[3]	: �A�C�e����Y���W		float
		// strvec[4]	: �A�C�e����Z���W		float
		// strvec[5]	: �ړ������x�N�g��X		float
		// strvec[6]	: �ړ������x�N�g��Y		float
		// strvec[7]	: �ړ������x�N�g��Z		float
		// strvec[8]	: ���]����܂ł̎���	int
		// strvec[9]	: �ړ����x				float


		// �ǂݎ�����f�[�^�����W�ɕϊ�����
		VECTOR pos = VGet(stof(strvec[2]), stof(strvec[3]), stof(strvec[4]));
		VECTOR direction = VGet(stof(strvec[5]), stof(strvec[6]), stof(strvec[7]));
		int turnTime = stof(strvec[8]);
		float speed = stof(strvec[9]);

		// ��������
		pos.y += kHeightPos;

		// �f�[�^�ɍ����G�̒ǉ�
		Add(stoi(strvec[0]), strvec[1], pos, direction, turnTime, speed);
	}
}

void SpownEnemy::Appearance()
{
	for (auto& data : m_pData)
	{
		m_pObjectManager->AddObject(data->pEnemy);
		data->pEnemy->Init();
	}
}

void SpownEnemy::Add(int createNum, std::string enemyName, VECTOR pos, VECTOR direction, int turnTime, float speed)
{
	std::string enemyModelFile = "Data/Model/Enemy/" + enemyName + ".mv1";
	// ���f���t�@�C����
	const char* const modelFile = enemyModelFile.c_str();
	// ���f���n���h���̎擾
	int modelH = MV1LoadModel(modelFile);
	assert(modelH != -1);
	// itemName�ɍ����G�̒ǉ�
	if (enemyName == "Bee")
	{
		m_pData.push_back(new Data);
		m_pData.back()->pEnemy = new EnemyBee(pos, direction, turnTime, speed);
	}
	else if (enemyName == "Skull")
	{
		m_pData.push_back(new Data);
		m_pData.back()->pEnemy = new EnemySkull(pos, speed);
	}
	else
	{
		return;
	}

	m_pData.back()->pEnemy->SetModelHandle(modelH);
	m_pData.back()->index = createNum;
	m_pData.back()->name = enemyName;
}

std::vector<std::string> SpownEnemy::Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string filed;
	std::vector<std::string> result;

	while (getline(stream, filed, delimiter))
	{
		result.push_back(filed);
	}

	return result;
}
