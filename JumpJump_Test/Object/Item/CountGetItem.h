#pragma once

#include <memory>
#include <array>

class CountGetItem
{
public:
	CountGetItem(int maxCount);
	virtual ~CountGetItem();

	void Draw();
	void Add();

	bool IsCountMax();

	int GetGetItemCount()const { return m_count; }
	
private:
	int m_count;						// �J�E���g��
	int m_maxCount;						// �J�E���g�̍ő�l
	int m_H;							// �摜�n���h��
	std::array<int, 10>m_numberH{};		// �����̉摜�n���h��
};

