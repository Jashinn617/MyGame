#pragma once

#include <vector>
#include <memory>
#include <functional>

class Stamina;
class Time;

class PlayerState
{
public:
	// ���
	enum class State
	{
		Idle,		// �ҋ@
		Walk,		// ����
		Run,		// ����
		Jump,		// �W�����v
		KnockBack,	// �m�b�N�o�b�N
	};

private:	// �\����

	// ��ԏ��
	struct StateData
	{

	};
};

