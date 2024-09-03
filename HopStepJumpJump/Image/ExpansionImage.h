#pragma once
#include "ImageBase.h"
class ExpansionImage : public ImageBase
{
public:
	ExpansionImage();
	virtual ~ExpansionImage();

	void Update() override final;
	void Draw() override final;

	/// <summary>
	/// �g�又�����I���������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsExpandionEnd()const { return m_isChangeEnd; }

private:
	void FadeInUpdate();
	void NormalUpdate();

private:	// �ϐ�
	int m_alpha;	// �����x
	double m_size;	// �摜�T�C�Y
	double m_changeSizeSpeed;	// �T�C�Y�̕ύX���x
	bool m_isExpanding;	// �g�咆���ǂ���
	bool m_isChangeEnd;	// �g�又�����I���������ǂ���

	void (ExpansionImage::* m_updateFunc)();	// �����o�֐��|�C���^


};

