#pragma once

class Input;
class StoryScene
{
public:
	StoryScene();
	~StoryScene();

	// ������
	void Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �V�[���̏I��
	void End();
	// �V�[�����I���������ǂ���
	bool IsSceneEnd();

private:
	/* �O���t�B�b�N*/
	// �X�g�[���[
	int m_storyHandle[8];
	// �X�L�b�v
	int m_skipHandle;
	// �{�^��
	int m_buttonHandle;

	/*BGM*/
	int m_bgmHandle;

	// �X�g�[���[�������t���[����
	int m_storyFrame;
	// �X�g�[���[�̃J�E���g
	int m_storyCount;
	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �V�[�����I���������ǂ���
	bool m_isSceneEnd;
};

