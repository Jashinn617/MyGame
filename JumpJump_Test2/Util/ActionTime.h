#pragma once
class ActionTime
{
public:
	ActionTime(int maxTime);
	~ActionTime();

	/// <summary>
	/// �X�V
	/// </summary>
	bool Update();

	/// <summary>
	/// �^�C�����Z�b�g
	/// </summary>
	void Reset();

private:
	int m_time;			// �o�ߎ���
	int m_maxTime;		// �ő厞��
	bool m_isAction;	// �A�N�V���������s�������ǂ���
};

