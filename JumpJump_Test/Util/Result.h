#pragma once
#include "../Util/Game.h"
#include "../Util/Vec2.h"

#include <memory>
#include <array>
#include <string>

class ExpansionImage;
class FadeImage;
class Time;
class ActionTime;

class Result
{
public:
	// �����N
	enum class Rank
	{
		S,
		A,
		B,
		C,
		RankNum,
	};

public:
	Result(int stageClearTime, Game::Stage stage);
	~Result();

	void Update();

	void Draw();

	/// <summary>
	/// ���U���g���I���������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool IsEnd()const { return m_isEnd; }

private:	// �֐�
	/// <summary>
	/// �����N�v�Z
	/// </summary>
	void CalcRank();

private:	// �ϐ�
	int m_timeImageH;		// ���U���g�̉摜�n���h��
	std::array<int, 10> m_timeNumH{};	// �b���̉摜�n���h��
	std::array<int, 4> m_rankH{};

	int m_clearTime;		// �X�e�[�W�̃N���A����

	bool m_isEnd;			// ���U���g���I�����邩�ǂ���
	
	std::string m_clearMinutesTimeStr;	// �N���A����(��)
	std::string m_clearSecondTimeStr;	// �N���A����(�b)

	Vec2 m_clearTimePos;	// �N���A���Ԃ̕\���ʒu
	Vec2 m_rankPos;			// �����N�̈ʒu

	Rank m_rank;			// �����N

	std::shared_ptr<Time> m_pResultTime;			// ��ʂ��o��������܂ł̎���
};

