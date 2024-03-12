#pragma once

class Input;
class Tutorial00
{
public:
	enum NextScene
	{
		kTutorial1,
		kStage01
	};

public:
	Tutorial00();
	~Tutorial00();

	void  Init();
	void Update(Input& input);
	void Draw();

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const;


	// ���̃V�[���̐ݒ�
	NextScene IsNextScene()const { return m_nextScene; }

	NextScene GetStage01() const { return kStage01; }
	NextScene GetTutorial1() const { return kTutorial1; }

private:

	// �摜�n���h��
	int m_logo01;
	int m_logo02;
	int m_logo03;
	int m_cursor;

	// �J�[�\���̈ړ�
	int m_cursorCount;
	int m_cursorX;
	int m_cursorY;
	int m_cursorMove;

	// ���S�̃A�j���[�V����
	int m_logoY;

	// SE�̃n���h��
	int m_selectSeHandle;
	int m_startSeHandle;
	int m_landingLogoSeHandle;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;

	bool m_isOperation;

	bool m_isRingSe;

	// �V�[���I���t���O
	bool m_isSceneEnd;



	// ���̃V�[��
	NextScene m_nextScene;

};

