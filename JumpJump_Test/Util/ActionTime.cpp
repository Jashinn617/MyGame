#include "ActionTime.h"

ActionTime::ActionTime(int maxTime):
	m_time(0),
	m_maxTime(0),
	m_isAction(false)
{
}

ActionTime::~ActionTime()
{
	/*��������*/
}

bool ActionTime::Update()
{
	// �A�N�V���������s����Ă�����false
	if (m_isAction) return false;

	// ���~�b�g���Ԃ𒴂�����t���O��true�ɂ���
	if (m_time >= m_maxTime)
	{
		m_isAction = true;
		return true;
	}
	m_time++;

	return false;
}

void ActionTime::Reset()
{
	// �t���O�̃��Z�b�g
	m_isAction = false;
	// �^�C���̃��Z�b�g
	m_time = 0;
}
