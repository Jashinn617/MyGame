#include "DxLib.h"
#include "Pad.h"
#include <vector>

namespace
{
	constexpr int kLogNum = 16;	// ログ記録フレーム数
	constexpr int kMaxPad = 2;	// パッド最大数

	/*使うパッドのデータ*/
	constexpr int kUsePadData[kMaxPad] =
	{
		DX_INPUT_KEY_PAD1,
		DX_INPUT_PAD2
	};

	int padLog[kMaxPad][kLogNum];	// 入力ログ(0が最新の状態)

	/*キーログ*/
	bool				isRecordLog = false;	// ログを記録中か
	int					playLogNo = -1;			// キーログの再生フレーム数
	std::vector<int>	keyLog;					// ログ
}

namespace Pad
{
	// パッド入力の状態取得
	void Update()
	{
		for (int padNo = 0; padNo < kMaxPad; padNo++)
		{
			// 現在のパッドの状態を取得
			int padState = GetJoypadInputState(kUsePadData[padNo]);
			if ((playLogNo >= 0) && (padNo == 0))
			{
				// ログのサイズよりもログのフレーム数が小さかったら
				if (keyLog.size() > playLogNo)
				{
					padState = keyLog[playLogNo];
					// ログを増やす
					playLogNo++;
				}
				else // 大きかったら
				{
					// ログのリセット
					playLogNo = -1;
				}
			}

			// ログの更新
			for (int i = kLogNum - 1; i >= 1; i--)
			{
				padLog[padNo][i] = padLog[padNo][i - 1];
			}
			// 最新の状態にする
			padLog[padNo][0] = padState;

			// キーログ
			if (isRecordLog)
			{
				if (padNo == 0)
				{
					keyLog.push_back(padState);
				}
			}
		}
	}

	// 押し下げ判定
	bool IsPress(int button, int padNo)
	{
		return (padLog[padNo][0] & button);
	}
	// トリガー判定
	bool IsTrigger(int button, int padNo)
	{
		bool isNow = (padLog[padNo][0] & button);	// 現在の状態
		bool isLast = (padLog[padNo][1] & button);	// １フレーム前の状態
		return (isNow && !isLast);
	}
	//離した判定
	bool IsRelase(int button, int padNo) {
		bool isNow = (padLog[padNo][0] & button);	//現在の状態
		bool isLast = (padLog[padNo][1] & button);	//1フレーム前の状態
		return (!isNow && isLast);
	}
	
	void StartRecordLog()
	{
		isRecordLog = true;
		keyLog.clear();
	}

	void EndRecordLog()
	{
		isRecordLog = false;
	}
	
	void StartPlayLog()
	{
		playLogNo = 0;
	}
	
	void EndPlayLog()
	{
		playLogNo = -1;
	}
}