#include "DxLib.h"
#include "Pad.h"

#include <vector>

namespace
{
	/*�萔*/
	constexpr int kLogNum = 16;	// ���O���L�^����t���[����
	constexpr int kMaxPad = 2;	// �p�b�h�̍ő吔

	/*�g���p�b�h�̃f�[�^*/
	constexpr int kUsePadData[kMaxPad] =
	{
		DX_INPUT_KEY_PAD1,
		DX_INPUT_PAD2
	};

	/*�ϐ�*/
	int padLog[kMaxPad][kLogNum];	// ���̓��O(0���ŐV�̏��)

	/*�L�[���O*/
	int playLogNo = -1;			// �L�[���O�̍Đ��t���[����
	bool isRecordLog = false;	// ���O���L�^�����ǂ���
	std::vector<int> keyLog;	// �L�[���O
}

namespace Pad
{
	void Update()
	{
		// �p�b�h�̐������J��Ԃ�
		for (int padNo = 0; padNo < kMaxPad; padNo++)
		{
			// ���݂̃p�b�h�̏�Ԃ̎擾
			int padState = GetJoypadInputState(kUsePadData[padNo]);

			if ((playLogNo >= 0) && (padNo == 0)) // ���O�̃T�C�Y��0�ȏ�Ńp�b�h���擪�̃p�b�h�������ꍇ
			{				
				if (keyLog.size() > playLogNo) // ���O�̃T�C�Y�������O�̃t���[������������������
				{
					// �p�b�h�̏�ԍX�V
					padState = keyLog[playLogNo];
					// ���O�𑝂₷
					playLogNo++;
				}
				else // ���O�̃T�C�Y�������O�̃t���[�������傫��������
				{
					// ���O�����Z�b�g����
					playLogNo = -1;
				}
			}

			for (int i = kLogNum - 1; i >= 1; i--)
			{
				// ���O�̍X�V
				// �ߋ��̓��̓��O������ɂ��Ă���
				padLog[padNo][i] = padLog[padNo][i - 1];
			}
			// �ŐV�̏�Ԃɂ���
			padLog[padNo][0] = padState;

			/*�L�[���O*/
			if (isRecordLog) // ���O���L�^����������
			{
				// �p�b�h���擪�̃p�b�h��������
				if (padNo == 0)
				{
					// ���O�̒ǉ�
					keyLog.push_back(padState);
				}
			}
		}
	}

	bool IsPress(int button, int padNo)
	{
		// ���݂̏��(�r�b�g���Z)
		// ���݂̃t���[���ŉ����Ă��邩�ǂ���
		return (padLog[padNo][0] & button);
	}

	bool IsTrigger(int button, int padNo)
	{
		bool isNow = (padLog[padNo][0] & button);	// ���݂̏��(�r�b�g���Z)
		bool isLast = (padLog[padNo][1] & button);	// �O�t���[���̏��(�r�b�g���Z)

		// ���݂̃t���[���ŉ����Ă��āA�O�̃t���[���ł͉����Ă��Ȃ����ǂ���
		return isNow && !isLast;
	}

	bool IsRelase(int button, int padNo)
	{
		bool isNow = (padLog[padNo][0] & button);	// ���݂̏��(�r�b�g���Z)
		bool isLast = (padLog[padNo][1] & button);	// �O�t���[���̏��(�r�b�g���Z)

		// ���݂̃t���[���ŉ����Ă��Ȃ��āA�O�̃t���[���ł͉�����Ă������ǂ���
		return !isNow && isLast;
	}

	void StartRecordLog()
	{
		// �L�^�̊J�n
		isRecordLog = true;
		// ���O�̃N���A
		keyLog.clear();
	}

	void EndRecordLog()
	{
		// �L�^�̏I��
		isRecordLog = false;
	}

	void StartPlayLog()
	{
		// ���O�̏�����
		playLogNo = 0;
	}

	void EndPlayLog()
	{
		// ���O�̃��Z�b�g
		playLogNo = -1;
	}
}