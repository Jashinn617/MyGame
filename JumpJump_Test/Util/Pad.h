#pragma once

// �p�b�h����
namespace Pad
{
	// �p�b�h�̓��͏�Ԏ擾
	void Update();

	// ������������
	bool isPress(int button, int padNo = 0);
	// �g���K�[����
	bool isTrigger(int button, int padNo = 0);
	//����������
	bool isRelase(int button, int padNo = 0);

	// ���O�L�^�J�n�A�I��
	void startRecordLog();
	void endRecordLog();

	// ���O�Đ��J�n�A�I��
	void startPlayLog();
	void endPlayLog();
}
