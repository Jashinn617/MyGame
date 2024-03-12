#pragma once

class Input;
class ClearScene
{
public:
	ClearScene();
	~ClearScene();

	// ������
	void Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �O�i�̂т傤��
	void ForeDraw();
	// �V�[���I�����̏���
	void End();

	// �V�[�����I���������ǂ���
	bool IsSceneEnd();

private:
	/*�O���t�B�b�N*/
	// �w�i
	int m_bgHandle;
	// �O�i
	int m_fgHandle;
	// �I�u�W�F�N�g
	int m_objHandle0;
	int m_objHandle1;
	int m_objHandle2;
	int m_objHandle3;
	/*BGM*/
	int m_bgmHandle;
	// �X�N���[��
	float m_scrollX;
	// �T�C�Y
	int m_fgW;
	int m_fgH;
	// �V�[���I���t���O
	bool m_isSceneEnd;

};

