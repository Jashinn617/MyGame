#pragma once
#include "Game.h"
#include <string>
#include <vector>

/// <summary>
/// �����L���O�����X�V����
/// </summary>
class Ranking
{
public:
	Ranking();
	~Ranking();
	void CreateRanking(Game::Stage stageKind);			  // �����L���O�쐬
	void UpdateRanking(Game::Stage stageKind, int clearTime); // �����L���O�X�V
	std::vector<int> GetRanking(Game::Stage stageKind);						  // �����L���O�擾

private:
	std::string HttpGet(const char* domain, const char* url); // Http�ʐM��Get���߂𑗂�

private:	// �萔
	static const int kDataSize = 2560;	// �f�[�^�T�C�Y

private:	// �ϐ�
	int m_netH;						// �l�b�g���[�N�n���h��
	int m_dataLength;						// ��M�f�[�^�ʕۑ��p�ϐ�
	int m_lineCount;					// �\������s�����J�E���g����
	char m_strBuf[kDataSize] = "";		// �f�[�^�o�b�t�@

	std::vector<int> m_rankingList;		// �N���A�^�C����ۑ�����
	std::string uri;
	std::string createRank;
	std::string getRank;

	IPDATA m_ip;							// �ڑ��p�h�o�A�h���X�f�[�^
	size_t m_pos;						// �����̒������擾����


};

