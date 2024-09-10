#include "DxLib.h"
#include "Vec2.h"
#include "Ranking.h"

// �萔
namespace
{
	// �h���C����
	const char* kDomainName = "jashinkunn.catfood.jp";
	// �e�X�g�pURI
	const char* kTestCreateUri = "/HopRank/NetTest/createRanking.php";				// �쐬
	const char* kTestUpdateUri = "/HopRank/NetTest/updateRanking.php?clearTime=";  // �X�V
	const char* kTestGetUri = "/HopRank/NetTest/getRanking.php";					// �擾
	// �X�e�[�W1URI
	const char* kStage1CreateUri = "/HopRank/Stage1/createRanking.php";				// �쐬
	const char* kStage1UpdateUri = "/HopRank/Stage1/updateRanking.php?clearTime=";  // �X�V
	const char* kStage1GetUri = "/HopRank/Stage1/getRanking.php";					// �擾
	// �X�e�[�W2URI
	const char* kStage2CreateUri = "/HopRank/Stage2/createRanking.php";					// �쐬
	const char* kStage2UpdateUri = "/HopRank/Stage2/updateRanking.php?clearTime=";		// �X�V
	const char* kStage2GetUri = "/HopRank/Stage2/getRanking.php";						// �擾
	constexpr int kPortNum = 80;		// �|�[�g�ԍ�
	constexpr int kMaxRankNum = 10;		// �\�����郉���L���O��

	// �����L���O�\��
	constexpr float kRankingIntervalAdj = 28.0f;		// �\���ʒu����
	constexpr int kTextColor = 0xffffff;				// �e�L�X�g�̐F
	constexpr float kRankingIntervalWidth = 400.0f;		// ���̕\���Ԋu
	// �X�e�[�W�I����
	const Vec2 kStageSlectRankPos = { 900, 320 };		// �\���ʒu
	constexpr float kStageSlectRankInterval = 60.0f;	// �c�̕\���Ԋu
	// �N���A��
	const Vec2 kRankingPos = { 1000.0f, 550.0f };		// �\���ʒu
	constexpr float kClearRankInterval = 80.0f;			// �c�̕\���Ԋu

}

Ranking::Ranking() :
	m_pos(0),
	m_lineCount(0)
{
	m_rankingList.resize(kMaxRankNum);
}


Ranking::~Ranking()
{
}

void Ranking::CreateRanking(Game::Stage stageKind)
{
	// �X�e�[�W�ɂ����URI��ύX����
	switch (stageKind)
	{
	case Game::Stage::Test:
		createRank = HttpGet(kDomainName, kTestCreateUri);
		break;
	case Game::Stage::Stage1:
		createRank = HttpGet(kDomainName, kStage1CreateUri);
		break;
	case Game::Stage::Stage2:
		createRank = HttpGet(kDomainName, kStage2CreateUri);
		break;
	}
}

void Ranking::UpdateRanking(Game::Stage stageKind, int clearTime)
{
	// �X�e�[�W�ɂ����URI��ύX����
	switch (stageKind)
	{
	case Game::Stage::Test:
		uri = kTestUpdateUri + std::to_string(clearTime);
		break;
	case Game::Stage::Stage1:
		uri = kStage1UpdateUri + std::to_string(clearTime);
		break;
	case Game::Stage::Stage2:
		uri = kStage2UpdateUri + std::to_string(clearTime);
		break;
	}

	std::string getRank = HttpGet(kDomainName, uri.c_str());
}

std::vector<int> Ranking::GetRanking(Game::Stage stageKind)
{
	// �X�e�[�W�ɂ����URI��ύX����
	switch (stageKind)
	{
	case Game::Stage::Test:
		getRank = HttpGet(kDomainName, kTestGetUri);
		break;
	case Game::Stage::Stage1:
		getRank = HttpGet(kDomainName, kStage1GetUri);
		break;
	case Game::Stage::Stage2:
		getRank = HttpGet(kDomainName, kStage2GetUri);
		break;
	}

	m_lineCount = 0;  // �����L���O�J�E���g�����Z�b�g
	size_t m_pos = 0;

	// 1�ʁ`10�ʂ܂Ŏ擾����
	// MEMO:clearTime�����𒊏o����BclearTime��������Ȃ��ꍇ��npos��Ԃ�
	while (m_lineCount < kMaxRankNum && (m_pos = getRank.find("\"clearTime\":")) != std::string::npos)
	{
		m_pos += strlen("\"clearTime\":");
		int clearTime = 0;
		int numChars = 0;

		if (sscanf_s(getRank.c_str() + m_pos, "%d%n", &clearTime, &numChars) == 1)
		{
			if (m_lineCount < kMaxRankNum)
			{
				m_rankingList[m_lineCount] = clearTime;  // �����L���O���X�g�ɕۑ�
				m_lineCount++;
			}

			// ���̗v�f�ɐi��
			m_pos += numChars;				  // �ǂݎ�����������������i�߂�
			getRank = getRank.substr(m_pos);  // �c��̕�����������擾
		}
		else
		{
			break;  // sscanf_s�����s�����ꍇ�̓��[�v���I��
		}
	}

	return m_rankingList;
}

std::string Ranking::HttpGet(const char* domain, const char* uri)
{
	char HttpCmd[128] = ""; 	// Http�ʐM���쐬���邽�߂̕ϐ�

	// DxLib�̕s�v�ȋ@�\��off�ɂ���
	SetUseDXNetWorkProtocol(false);

	// DNS����h���C������IP�A�h���X���擾
	GetHostIPbyName(domain, &m_ip);

	// �ʐM���m��
	m_netH = ConnectNetWork(m_ip, kPortNum);

	// �m�������������ꍇ�̂ݒ��̏���������
	if (m_netH != -1)
	{
		//Http���߂̍쐬
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
#ifdef _DEBUG
		//DrawFormatString(0, 60, 0xffffff, "HttpCmd:\n%s", HttpCmd);
#endif // _DEBUG

		// �f�[�^���M(http���߂𑗂�)
		NetWorkSend(m_netH, HttpCmd, strlen(HttpCmd));

		// �f�[�^������̂�҂�
		while (!ProcessMessage())
		{
			// �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
			m_dataLength = GetNetWorkDataLength(m_netH);

			// �擾���ĂȂ���M�f�[�^�ʂ�-1����Ȃ��ꍇ�̓��[�v�𔲂���
			if (m_dataLength != -1)
			{
				break;
			}
		}

		// �f�[�^��M
		NetWorkRecv(m_netH, m_strBuf, kDataSize);    // �f�[�^���o�b�t�@�Ɏ擾

		// �ڑ���f��
		CloseNetWork(m_netH);
	}

	return m_strBuf;
}