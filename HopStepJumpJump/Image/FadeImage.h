#pragma once
#include "ImageBase.h"
class FadeImage : public ImageBase
{
public:
	FadeImage();
	virtual ~FadeImage();

	void Update() override;
	void Draw() override;

	void SetMaxAlpha(int maxAlpha) { m_maxAlpha = maxAlpha; }

	/// <summary>
	/// �t�F�[�h���I���������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsFadeEnd() { return m_alpha == m_maxAlpha; }

private:
	int m_alpha;	// �����x
	int m_maxAlpha;	// �ő哧���x
};

