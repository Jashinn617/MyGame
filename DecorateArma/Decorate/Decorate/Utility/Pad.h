#pragma once

/// <summary>
/// �p�b�h�������s��namespace
/// </summary>
namespace Pad
{
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ������������
	/// </summary>
	/// <param name="button">�����Ă���{�^��</param>
	/// <param name="padNo">�R���g���[���[�ԍ�(��l�v���C������������g��)</param>
	/// <returns>���{�^���������Ă��邩�ǂ���</returns>
	bool IsPress(int button, int padNo = 0);

	/// <summary>
	/// �g���K�[����
	/// </summary>
	/// <param name="button">�����Ă���{�^��</param>
	/// <param name="padNo">�R���g���[���[�ԍ�(��l�v���C������������g��)</param>
	/// <returns>�{�^�����������u�Ԃ��ǂ���</returns>
	bool IsTrigger(int button, int padNo = 0);

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="button">�����Ă���{�^��</param>
	/// <param name="padNo">�R���g���[���[�ԍ�(��l�v���C������������g��)</param>
	/// <returns>�{�^���𗣂����u�Ԃ��ǂ���</returns>
	bool IsRelase(int button, int padNo = 0);

	/// <summary>
	/// ���O�L�^�J�n
	/// </summary>
	void StartRecordLog();

	/// <summary>
	/// ���O�L�^�I��
	/// </summary>
	void EndRecordLog();

	/// <summary>
	/// ���O�Đ��J�n
	/// </summary>
	void StartPlayLog();

	/// <summary>
	/// ���O�Đ��I��
	/// </summary>
	void EndPlayLog();
}