#pragma once
class Time
{
public:
	Time(int rimitTime);
	~Time();

	/// <summary>
	/// �^�C�����Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	/// �^�C���X�V
	/// </summary>
	/// <returns>���~�b�g���Ԃ𒴂��Ă��邩�ǂ���</returns>
	bool Update();

private:	// �ϐ�
	int m_time;			// �o��������
	int m_rimitTime;	// ���~�b�g����

};

