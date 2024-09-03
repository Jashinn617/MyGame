#pragma once

#include <memory>
#include <array>

class CountTime
{
public:
	CountTime();
	virtual ~CountTime();

	void Update(int time);
	void Draw();

private:
	int m_time;	// ���݂̕b��
	int m_H;	// �摜�n���h��
	std::array<int, 10> m_numberH{};	// �����̉摜�n���h��
};