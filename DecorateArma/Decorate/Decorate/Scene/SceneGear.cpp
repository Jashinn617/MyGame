#include "SceneGear.h"
#include "SceneSelect.h"

#include "../Object/Player/Gear.h"

#include "../Utility/Pad.h"

#include "../Common/CsvLoad.h"

#include <cassert>

namespace
{
	constexpr int kGearNum = 15;					// 装備品の数
	constexpr int kMaxCost = 30;					// 最大コスト数
	constexpr int kAlpha = 100;						// 装備を外すの時に使う画像の不透明度

	/*ファイルパス関係*/
	const std::string kGearPath = "Data/Image/Gear/";	// 画像ファイルパス
	// テキスト画像パス
	const std::string kImgNamePath[kGearNum] =
	{
		 kGearPath + "Text/HPUPS.png",
		 kGearPath + "Text/HPUPM.png",
		 kGearPath + "Text/HPUPL.png",
		 kGearPath + "Text/MATKUPS.png",
		 kGearPath + "Text/MATKUPM.png",
		 kGearPath + "Text/MATKUPL.png",
		 kGearPath + "Text/SATKUPS.png",
		 kGearPath + "Text/SATKUPM.png",
		 kGearPath + "/Text/SATKUPL.png",
		 kGearPath + "Text/DEFUPS.png",
		 kGearPath + "Text/DEFUPM.png",
		 kGearPath + "Text/DEFUPL.png",
		 kGearPath + "Text/AllUPS.png",
		 kGearPath + "Text/AllUPM.png",
		 kGearPath + "Text/AllUPL.png",
	};
	// 数字画像パス
	const std::string kNumPath[10] =
	{
		 kGearPath + "Number/0.png",
		 kGearPath + "Number/1.png",
		 kGearPath + "Number/2.png",
		 kGearPath + "Number/3.png",
		 kGearPath + "Number/4.png",
		 kGearPath + "Number/5.png",
		 kGearPath + "Number/6.png",
		 kGearPath + "Number/7.png",
		 kGearPath + "Number/8.png",
		 kGearPath + "Number/9.png",
	};
	// 説明文画像名
	const std::string kExplainTextPath[kGearNum] =
	{
		 kGearPath + "ExplainText/HPS.png",
		 kGearPath + "ExplainText/HPM.png",
		 kGearPath + "ExplainText/HPL.png",
		 kGearPath + "ExplainText/MATKS.png",
		 kGearPath + "ExplainText/MATKM.png",
		 kGearPath + "ExplainText/MATKL.png",
		 kGearPath + "ExplainText/SATKS.png",
		 kGearPath + "ExplainText/SATKM.png",
		 kGearPath + "ExplainText/SATKL.png",
		 kGearPath + "ExplainText/DEFS.png",
		 kGearPath + "ExplainText/DEFM.png",
		 kGearPath + "ExplainText/DEFL.png",
		 kGearPath + "ExplainText/AllS.png",
		 kGearPath + "ExplainText/AllM.png",
		 kGearPath + "ExplainText/AllL.png",
	};
	// 装備中装備品UI画像パス
	const std::string kEquippedUIPath[kGearNum] =
	{
		 kGearPath + "EquippedUI/HPS.png",
		 kGearPath + "EquippedUI/HPM.png",
		 kGearPath + "EquippedUI/HPL.png",
		 kGearPath + "EquippedUI/MATKS.png",
		 kGearPath + "EquippedUI/MATKM.png",
		 kGearPath + "EquippedUI/MATKL.png",
		 kGearPath + "EquippedUI/SATKS.png",
		 kGearPath + "EquippedUI/SATKM.png",
		 kGearPath + "EquippedUI/SATKL.png",
		 kGearPath + "EquippedUI/DEFS.png",
		 kGearPath + "EquippedUI/DEFM.png",
		 kGearPath + "EquippedUI/DEFL.png",
		 kGearPath + "EquippedUI/AllS.png",
		 kGearPath + "EquippedUI/AllM.png",
		 kGearPath + "EquippedUI/AllL.png",
	};

	const std::string kEquipTextPath = kGearPath + "Text/Equip.png";				// 装備をするテキスト画像ファイルパス
	const std::string kRemoveEquipPath = kGearPath + "Text/RemoveEquip.png";		// 装備を外すテキスト画像ファイルパス
	const std::string kCostTextPath = kGearPath + "Text/Cost.png";					// コストテキスト画像ファイルパス
	const std::string kMulMarkPath = kGearPath + "MulMark.png";						// ×マーク画像ファイルパス
	const std::string kSlashPath = kGearPath + "Slash.png";							// スラッシュ画像ファイルパス
	const std::string kSelectCursorPath = kGearPath + "Box/SelectCursorBox.png";	// 選択時のカーソル画像ファイルパス
	const std::string kCursorPath = kGearPath + "Box/CursorBox.png";				// カーソル画像ファイルパス
	const std::string kRemoveCursorPath = kGearPath + "Box/RemoveCursorBox.png";	// 装備を外す時のカーソル画像ファイルパス
	const std::string kGearBoxPath = kGearPath + "Box/GearBox.png";					// 装備品ボックス画像ファイルパス
	const std::string kExplainBoxPath = kGearPath + "Box/GearExplainBox.png";		// 装備品説明文ボックス画像ファイルパス
	const std::string kEquippedBoxPath = kGearPath + "Box/EquippedBox.png";			// 装備中ボックス画像ファイルパス
	const std::string kStatusBoxPath = kGearPath + "Box/StatusBox.png";				// ステータスボックス画像ファイルパス
	const std::string kStatusHpTextPath = kGearPath + "Text/HP.png";				// ステータスボックス内HPテキスト画像ファイルパス
	const std::string kStatusMAtkTextPath = kGearPath + "Text/MATK.png";			// ステータスボックス内近接攻撃テキスト画像ファイルパス
	const std::string kStatusSAtkTextPath = kGearPath + "Text/SATK.png";			// ステータスボックス内遠距離攻撃テキスト画像ファイルパス
	const std::string kStatusDefTextPath = kGearPath + "Text/Def.png";				// ステータスボックス内防御力テキスト画像ファイルパス
	const std::string kAddPath = kGearPath + "Add.png";								// プラス記号画像ファイルパス

	/*座標関係*/
	constexpr int kGearLeftPosX = 150;							// 装備品名左側座標
	constexpr int kGearRightPosX = kGearLeftPosX + 600;			// 装備品名右側座標
	constexpr int kGearStartPosY = 175;							// 装備品名Y座標の最初の位置
	constexpr int kGearIntervalPosY = 80;						// 装備品名Y座標の間隔
	constexpr int kEquipTextPosX = 380;							// 装備をするテキストX座標
	constexpr int kRemoveTextPosX = kEquipTextPosX + 400;		// 装備を外すテキストX座標
	constexpr int kEquipTextPosY = 50;							// 装備をするテキストY座標
	constexpr int kExplainTextPosX = 450;						// 説明文画像X座標
	constexpr int kExplainTextPosY = 880;						// 説明文画像Y座標
	constexpr int kExplainCostPosX = kExplainTextPosX + 60	;	// 説明文コストX座標
	constexpr int kExplainCostPosY = kExplainTextPosY + 50;		// 説明文コストY座標
	constexpr int kSecondCostNumPosX = kExplainCostPosX + 150;	// 説明文コスト数十の位X座標
	constexpr int kFirstCostNumPosX = kSecondCostNumPosX + 30;	// 説明文コスト数一の位X座標
	constexpr int kCostNumPosY = kExplainCostPosY;				// 説明文コスト数のY座標
	constexpr int kCostTextPosX = 1500;							// コストテキストX座標
	constexpr int kCostTextPosY = 70;							// コストテキストY座標
	constexpr int kMaxCostSecondPosX = kCostTextPosX + 300;		// 最大コスト数十の位X座標
	constexpr int kMaxCostFirstPosX = kMaxCostSecondPosX + 25;	// 最大コスト数一の位X座標
	constexpr int kCostSecondPosX = kCostTextPosX + 200;		// 現在コスト数十の位X座標
	constexpr int kCostFirstPosX = kCostSecondPosX + 25;		// 現在コスト数一の位X座標
	constexpr int kCostPosY = kCostTextPosY;					// 最大コスト数Y座標
	constexpr int kSlashPosX = kCostFirstPosX + 30;				// スラッシュX座標
	constexpr int kSlashPosY = kCostPosY;						// スラッシュY座標
	constexpr int kMulMarkPosX = 400;							// ×マーク座標
	constexpr int kMulMarkPosY = 10;							// ×マークY座標調整
	constexpr int kNumSecondPosX = kMulMarkPosX + 50;			// 十の位数字座標
	constexpr int kNumFirstPosX = kNumSecondPosX + 30;			// 一の位数字座標
	constexpr int kSelectCursorLeftPosX = kEquipTextPosX - 10;	// 選択カーソルX座標左
	constexpr int kSelectCursorRightPosX = kRemoveTextPosX - 10;// 選択カーソルX座標右
	constexpr int kSelectCursorPosY = kEquipTextPosY - 15;		// 選択カーソルY座標
	constexpr int kEquipCursorPosX = -25;						// 装備を着けるカーソルY座標
	constexpr int kEquipCursorPosY = -20;						// 装備を着けるカーソルY座標
	constexpr int kGearBoxPosX = 100;							// 装備品ボックスX座標
	constexpr int kGearBoxPosY = 125;							// 装備品ボックスY座標
	constexpr int kExplainBoxPosX = kGearBoxPosX + 35;			// 説明文ボックスX座標
	constexpr int kExplainBoxPosY = 830;						// 説明文ボックスY座標
	constexpr int kEquippedBoxPosX = 1400;						// 装備中ボックスX座標
	constexpr int kEquippedBoxPosY = kGearBoxPosY;				// 装備中ボックスY座標
	constexpr int kStatusBoxPosX = kEquippedBoxPosX - 80;		// ステータスボックスX座標
	constexpr int kStatusBoxPosY = kEquippedBoxPosY + 580;		// ステータスボックスY座標
	constexpr int kEquippedUIPosX = 1410;						// 装備品中装備品X座標
	constexpr int kEquippedUIStartPosY = 150;					// 装備品中装備品初期Y座標
	constexpr int kEquippedUIIntervalPosY = 40;					// 装備品中装備品Y座標間隔
	constexpr int kStatusTextPosX = kStatusBoxPosX + 20;		// ステータスボックス内テキストX座標
	constexpr int kHpTextPosY = 725;							// HPテキストY座標
	constexpr int kMAtkTextPosY = kHpTextPosY + 70;				// 近接攻撃テキストY座標
	constexpr int kSAtkTextPosY = kMAtkTextPosY + 70;			// 遠距離攻撃テキストY座標
	constexpr int kDefTextPosY = kSAtkTextPosY + 70;			// 防御テキストY座標
	constexpr int kStatusFourthPosX = kStatusTextPosX + 225;	// ステータス千の位X座標
	constexpr int kStatusThirdPosX = kStatusFourthPosX + 25;	// ステータス百の位X座標
	constexpr int kStatusSecondPosX = kStatusThirdPosX + 25;	// ステータス十の位X座標
	constexpr int kStatusFirstPosX = kStatusSecondPosX + 25;	// ステータス一の位X座標
	constexpr int kAddPosX = kStatusFirstPosX + 30;				// プラスマークX座標
	constexpr int kAddStatusFourthPosX = kAddPosX + 90;			// 追加ステータス千の位X座標
	constexpr int kAddStatusThirdPosX = kAddStatusFourthPosX + 25;	// 追加ステータス百の位X座標
	constexpr int kAddStatusSecondPosX = kAddStatusThirdPosX + 25;	// 追加ステータス十の位X座標
	constexpr int kAddStatusFirstPosX = kAddStatusSecondPosX + 25;	// 追加ステータス一の位X座標
	constexpr int kStatusNumPosY = 5;							// ステータスY座標調整用
}

SceneGear::SceneGear() :
	m_cursorCount(0),
	m_isSelectLeft(true),
	m_pGear(std::make_shared<Gear>()),
	m_cursorKind(CursorKind::Select),
	m_nextScene(nullptr)
{
	// 画像のロード
	for (int i = 0; i < kGearNum; i++)
	{
		m_gearH.push_back(LoadGraph(kImgNamePath[i].c_str()));
		// 画像が無ければ止める
		assert(m_gearH[i] != -1);
	}
	for (int i = 0; i < 10; i++)
	{
		m_numH.push_back(LoadGraph(kNumPath[i].c_str()));
		assert(m_numH[i] != -1);
	}
	for (int i = 0; i < kGearNum; i++)
	{
		m_explainH.push_back(LoadGraph(kExplainTextPath[i].c_str()));
		assert(m_explainH[i]);
	}
	for (int i = 0; i < kGearNum; i++)
	{
		m_equippedUIH.push_back(LoadGraph(kEquippedUIPath[i].c_str()));
		assert(m_equippedUIH[i]);
	}

	m_mulMarkH = LoadGraph(kMulMarkPath.c_str());
	assert(m_mulMarkH != -1);
	m_slashH = LoadGraph(kSlashPath.c_str());
	assert(m_slashH != -1);
	m_cursorH = LoadGraph(kCursorPath.c_str());
	assert(m_cursorH != -1);
	m_selectCursorH = LoadGraph(kSelectCursorPath.c_str());
	assert(m_selectCursorH != -1);
	m_removeCursorH = LoadGraph(kRemoveCursorPath.c_str());
	assert(m_removeCursorH != -1);
	m_gearBoxH = LoadGraph(kGearBoxPath.c_str());
	assert(m_gearBoxH != -1);
	m_explainBoxH = LoadGraph(kExplainBoxPath.c_str());
	assert(m_explainBoxH != -1);
	m_equipTextH = LoadGraph(kEquipTextPath.c_str());
	assert(m_equipTextH != -1);
	m_removeEquipTextH = LoadGraph(kRemoveEquipPath.c_str());
	assert(m_removeEquipTextH != -1);
	m_costTextH = LoadGraph(kCostTextPath.c_str());
	assert(m_costTextH != -1);
	m_equippedBoxH = LoadGraph(kEquippedBoxPath.c_str());
	assert(m_equippedBoxH != -1);
	m_statusBoxH = LoadGraph(kStatusBoxPath.c_str());
	assert(m_statusBoxH != -1);
	m_hpTextH = LoadGraph(kStatusHpTextPath.c_str());
	assert(m_hpTextH != -1);
	m_mAtkTextH = LoadGraph(kStatusMAtkTextPath.c_str());
	assert(m_mAtkTextH != -1);
	m_sAtkTextH = LoadGraph(kStatusSAtkTextPath.c_str());
	assert(m_sAtkTextH != -1);
	m_defTextH = LoadGraph(kStatusDefTextPath.c_str());
	assert(m_defTextH != -1);
	m_addH = LoadGraph(kAddPath.c_str());
	assert(m_addH != -1);

	// プレイヤーのステータス取得
	CsvLoad::GetInstance().StatusLoad(m_statusData, "Player");
}

SceneGear::~SceneGear()
{
	// 画像のデリート
	for (auto& text : m_gearH)
	{
		DeleteGraph(text);
	}
	for (auto& num : m_numH)
	{
		DeleteGraph(num);
	}
	for (auto& text : m_explainH)
	{
		DeleteGraph(text);
	}
	for (auto& UI : m_equippedUIH)
	{
		DeleteGraph(UI);
	}
	DeleteGraph(m_mulMarkH);
	DeleteGraph(m_slashH);
	DeleteGraph(m_cursorH);
	DeleteGraph(m_selectCursorH);
	DeleteGraph(m_removeCursorH);
	DeleteGraph(m_gearBoxH);
	DeleteGraph(m_explainBoxH);
	DeleteGraph(m_equipTextH);
	DeleteGraph(m_removeEquipTextH);
	DeleteGraph(m_costTextH);
	DeleteGraph(m_equippedBoxH);
	DeleteGraph(m_statusBoxH);
	DeleteGraph(m_hpTextH);
	DeleteGraph(m_mAtkTextH);
	DeleteGraph(m_sAtkTextH);
	DeleteGraph(m_defTextH);
	DeleteGraph(m_addH);
}

void SceneGear::Init()
{
}

std::shared_ptr<SceneBase> SceneGear::Update()
{
	m_nextScene = shared_from_this();

	// カーソルの種類によって動きを変える
	switch (m_cursorKind)
	{
	case SceneGear::CursorKind::Select:
		// 選択
		UpdateSelectCursor();
		break;
	case SceneGear::CursorKind::Equip:
		// 装備を着ける
		UpdateEquipCursor();
		break;
	case SceneGear::CursorKind::Remove:
		// 装備を外す
		UpdateRemoveCursor();
		break;
	default:
		break;
	}

	

	return m_nextScene;
}

void SceneGear::Draw()
{
	// テキスト描画
	DrawGearText();
	// 装備品数描画
	DrawGearNum();
	// ボックス描画
	DrawBoxes();
	// 装備中装備描画
	DrawEquippedGear();
	// コスト描画
	DrawCost();
	// HP描画
	DrawHp();
	// 近接攻撃力描画
	DrawMAtk();
	// 遠距離攻撃力描画
	DrawSAtk();
	// 防御力描画
	DrawDef();
	// カーソル描画
	DrawCursor();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "装備画面");
#endif // _DEBUG
}

void SceneGear::End()
{
	// 装備情報の保存
	m_pGear->SaveGear();
}

void SceneGear::UpdateSelectCursor()
{
	// 左右ボタンを押されたらカーソルが移動する
	if (Pad::IsTrigger(PAD_INPUT_LEFT) ||
		Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		m_isSelectLeft = !m_isSelectLeft;
	}

	// Aボタンが押された場合はカーソルの種類を変える
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		if (m_isSelectLeft)
		{
			// 装備を付ける
			m_cursorKind = CursorKind::Equip;
			// カーソルカウントを0にする
			m_cursorCount = 0;

		}
		else
		{
			
				// 装備を外す
				m_cursorKind = CursorKind::Remove;
				// カーソルカウントを0にする
				m_cursorCount = 0;
		
		
		}
	}

	// Bボタンが押された場合はステージセレクトに戻る
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_nextScene = std::make_shared<SceneSelect>();
	}
}

void SceneGear::UpdateEquipCursor()
{
	// 右ボタンを押したらカーソルカウントが増える
	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		m_cursorCount++;

	}
	// 左ボタンを押したらカーソルカウントが減る
	if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		m_cursorCount--;

	}

	// カーソルがループするようにする
	if (m_cursorCount > kGearNum - 1)
	{
		m_cursorCount = 0;
	}
	if (m_cursorCount < 0)
	{
		m_cursorCount = kGearNum - 1;
	}

	// Aボタンが押された場合は選ばれている装備をセットする
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		int addCost = m_pGear->GetGearNum(m_cursorCount).cost;

		// 選ばれている装備品の数が1以上だった場合かつ
		// 装備品を足した時の現コストが最大数を超えいなかった場合
		if (m_pGear->GetGearNum(m_cursorCount).num > 0 &&
			UpdateCost() + addCost <= kMaxCost)
		{
			// 装備数を減らす
			m_pGear->DecreaseGear(m_cursorCount);
			// 装備中の装備品にそのデータを追加する
			m_pGear->AddEquippedGear(m_pGear->GetGearNum(m_cursorCount).name);
		}
		else
		{
			// 装備できないよSEを鳴らす

		}
	}

	// Bボタンが押された場合は選択に戻る
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_cursorKind = CursorKind::Select;
	}
	
}

void SceneGear::UpdateRemoveCursor()
{
	// 上ボタンを押したらカーソルカウントが減る
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_cursorCount--;
	}
	// 下ボタンを押したらカーソルカウントが増える
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_cursorCount++;
	}

	// カーソルがループしないようにする
	if (m_cursorCount < 0)
	{
		m_cursorCount = m_pGear->GetEquippedGearSize() - 1;
	}
	if (m_cursorCount > m_pGear->GetEquippedGearSize() - 1)
	{
		m_cursorCount = 0;
	}

	// Aボタンが押された場合は装備を外す
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// 装備中装備数が0以下でなかった場合
		if (m_pGear->GetEquippedGearSize() > 0)
		{
			// 装備を外す
			m_pGear->RemoveGear(m_cursorCount);
		}
		else
		{
			// 選べないよSEを鳴らす
		}

	}

	// Bボタンが押された場合は選択に戻る
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_cursorKind = CursorKind::Select;
	}
}

int SceneGear::UpdateCost()
{
	int cost = 0;	// コスト
	int equippedGearNum = m_pGear->GetEquippedGearSize();	// 装備中装備数
	// 現在のコストを確認する
	for (int i = 0; i < equippedGearNum; i++)
	{
		cost += m_pGear->GetEquippedNum(i).cost;
	}
	return cost;
}

void SceneGear::DrawCost()
{
	// 最大コスト数
	int maxFirst = kMaxCost % 10;	// 一の位
	int maxSecond = kMaxCost / 10;	// 十の位
	// 現在のコスト数
	int cost = UpdateCost();		// 現在のコスト数取得
	int costFirst = cost % 10;		// 一の位
	int costSecond = cost / 10;		// 十の位

	// 最大コスト数描画
	// 一の位
	DrawGraph(kMaxCostFirstPosX, kCostPosY, m_numH[maxFirst], true);
	// 十の位
	DrawGraph(kMaxCostSecondPosX, kCostPosY, m_numH[maxSecond], true);

	// スラッシュ表示
	DrawGraph(kSlashPosX, kSlashPosY, m_slashH, true);

	// 現在コスト数描画
	// 一の位
	DrawGraph(kCostFirstPosX, kCostPosY, m_numH[costFirst], true);
	// 十の位
	DrawGraph(kCostSecondPosX, kCostPosY, m_numH[costSecond], true);
}

void SceneGear::DrawGearText()
{
	int leftPosY = kGearStartPosY;	// 左側Y座標
	int rightPosY = kGearStartPosY;	// 右側Y座標

	// テキスト描画
	for (int i = 0; i < m_gearH.size(); i++)
	{
		// iが偶数だった場合
		if (i % 2 == 0)
		{
			// 左に描画
			DrawGraph(kGearLeftPosX, leftPosY, m_gearH[i], true);
			// ×マーク描画
			DrawGraph(kGearLeftPosX + kMulMarkPosX, leftPosY + kMulMarkPosY,
				m_mulMarkH, true);
			// Y座標を足す
			leftPosY += kGearIntervalPosY;
		}
		// iが奇数だった場合
		else
		{
			// 右に描画
			DrawGraph(kGearRightPosX, rightPosY, m_gearH[i], true);
			// ×マーク描画
			DrawGraph(kGearRightPosX + kMulMarkPosX, rightPosY + kMulMarkPosY,
				m_mulMarkH, true);
			// Y座標を足す
			rightPosY += kGearIntervalPosY;
		}
	}

	int cost = 0;		// コスト
	int numFirst = 0;	// 一の位
	int numSecond = 0;	// 十の位
	int number = 0;
	/*説明文描画*/
	switch (m_cursorKind)
	{
	case SceneGear::CursorKind::Select:
		// 何も描画しない
		break;
	case SceneGear::CursorKind::Equip:
		// 説明文描画
		DrawGraph(kExplainTextPosX, kExplainTextPosY, m_explainH[m_cursorCount], true);
		// 説明文コスト描画
		DrawGraph(kExplainCostPosX, kExplainCostPosY, m_costTextH, true);
		// コスト取得
		cost = m_pGear->GetGearNum(m_cursorCount).cost;
		numFirst = cost % 10;	// 一の位
		numSecond = cost / 10;	// 十の位
		// コスト数一の位描画
		DrawGraph(kFirstCostNumPosX, kCostNumPosY, m_numH[numFirst], true);
		// コスト数十の位描画
		DrawGraph(kSecondCostNumPosX, kCostNumPosY, m_numH[numSecond], true);
		break;
	case SceneGear::CursorKind::Remove:
		// 装備中装備数が0以下でなかった場合
		if (m_pGear->GetEquippedGearSize() > 0)
		{
			// 装備品番号の取得
			number = m_pGear->GetGearNum(m_pGear->GetEquippedNum(m_cursorCount).name).number;
			// 説明文描画
			DrawGraph(kExplainTextPosX, kExplainTextPosY, m_explainH[number], true);
			// 説明文コスト描画
			DrawGraph(kExplainCostPosX, kExplainCostPosY, m_costTextH, true);
			// コスト取得
			cost = m_pGear->GetGearNum(number).cost;
			numFirst = cost % 10;	// 一の位
			numSecond = cost / 10;	// 十の位
			// コスト数一の位描画
			DrawGraph(kFirstCostNumPosX, kCostNumPosY, m_numH[numFirst], true);
			// コスト数十の位描画
			DrawGraph(kSecondCostNumPosX, kCostNumPosY, m_numH[numSecond], true);
		}
		break;
	default:
		break;
	}

	// コストテキスト描画
	DrawGraph(kCostTextPosX, kCostTextPosY, m_costTextH, true);

	// 装備をする、外すテキスト描画
	DrawGraph(kEquipTextPosX, kEquipTextPosY, m_equipTextH, true);
	DrawGraph(kRemoveTextPosX, kEquipTextPosY, m_removeEquipTextH, true);	

	// ステータスボックス内テキスト描画
	// HP
	DrawGraph(kStatusTextPosX, kHpTextPosY, m_hpTextH, true);
	// 近接攻撃
	DrawGraph(kStatusTextPosX, kMAtkTextPosY, m_mAtkTextH, true);
	// 遠距離攻撃
	DrawGraph(kStatusTextPosX, kSAtkTextPosY, m_sAtkTextH, true);
	// 防御
	DrawGraph(kStatusTextPosX, kDefTextPosY, m_defTextH, true);
}

void SceneGear::DrawGearNum()
{
	int leftPosY = kGearStartPosY;	// 左側Y座標
	int rightPosY = kGearStartPosY;	// 右側Y座標

	// 数字描画
	for (int i = 0; i < m_gearH.size(); i++)
	{
		// 数取得
		int gearNum = m_pGear->GetGearNum(i).num;

		int numFirst = gearNum % 10;	// 一の位
		int numSecond = gearNum / 10;	// 十の位

		// iが偶数だった場合
		if (i % 2 == 0)
		{
			// 左に描画
			// 一の位
			DrawGraph(kGearLeftPosX + kNumFirstPosX,
				leftPosY, m_numH[numFirst], true);
			// 十の位
			DrawGraph(kGearLeftPosX + kNumSecondPosX,
				leftPosY, m_numH[numSecond], true);
			// Y座標を足す
			leftPosY += kGearIntervalPosY;
		}
		// i が奇数だった場合
		else
		{
			// 右に描画
				// 一の位
			DrawGraph(kGearRightPosX + kNumFirstPosX,
				rightPosY, m_numH[numFirst], true);
			// 十の位
			DrawGraph(kGearRightPosX + kNumSecondPosX,
				rightPosY, m_numH[numSecond], true);

			// Y座標を足す
			rightPosY += kGearIntervalPosY;
		}
	}
}

void SceneGear::DrawEquippedGear()
{
	// Y座標を決める
	int posY = kEquippedUIStartPosY;

	// 装備中のアイテムの数だけ繰り返す
	for (int i = 0; i < m_pGear->GetEquippedGearSize(); i++)
	{

		DrawGraph(kEquippedUIPosX,posY,
			m_equippedUIH[m_pGear->GetEquippedNum(i).number],
			true);

		posY += kEquippedUIIntervalPosY;
	}
}

void SceneGear::DrawCursor()
{
	switch (m_cursorKind)
	{
	case SceneGear::CursorKind::Select:
		// 選択
		DrawSelectCursor();
		break;
	case SceneGear::CursorKind::Equip:
		// 装備を着ける
		DrawEquipCursor();
		break;
	case SceneGear::CursorKind::Remove:
		// 装備を外す
		DrawRemoveCursor();
		break;
	default:
		break;
	}
}

void SceneGear::DrawSelectCursor()
{
	if (m_isSelectLeft)
	{
		// カーソル左
		DrawGraph(kSelectCursorLeftPosX, kSelectCursorPosY, m_selectCursorH, true);
	}
	else
	{
		// カーソル右
		DrawGraph(kSelectCursorRightPosX, kSelectCursorPosY, m_selectCursorH, true);
	}
}

void SceneGear::DrawEquipCursor()
{
	// Y座標を決める
	int posY = kGearStartPosY;
	for (int i = 0; i < m_cursorCount; i++)
	{
		// iが奇数の時のみY座標を追加する
		if (i % 2 == 1)
		{
			posY += kGearIntervalPosY;
		}
	}

	// カーソルカウントが偶数だった場合
	if (m_cursorCount % 2 == 0)
	{
		// 左側にカーソルを描画する
		DrawGraph(kGearLeftPosX + kEquipCursorPosX,
			posY + kEquipCursorPosY, m_cursorH, true);
	}
	else
	{
		// 右側にカーソルを描画する
		DrawGraph(kGearRightPosX + kEquipCursorPosX,
			posY + kEquipCursorPosY, m_cursorH, true);
	}
}

void SceneGear::DrawRemoveCursor()
{
	// 半透明の箱を選択中のUIに重ねる
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawGraph(kEquippedUIPosX,
		kEquippedUIStartPosY + (kEquippedUIIntervalPosY * m_cursorCount), 
		m_removeCursorH, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void SceneGear::DrawBoxes()
{
	// 装備品ボックス
	DrawGraph(kGearBoxPosX, kGearBoxPosY, m_gearBoxH, true);
	// 説明文ボックス
	DrawGraph(kExplainBoxPosX, kExplainBoxPosY, m_explainBoxH, true);
	// 装備中ボックス
	DrawGraph(kEquippedBoxPosX, kEquippedBoxPosY, m_equippedBoxH, true);
	// ステータスボックス
	DrawGraph(kStatusBoxPosX, kStatusBoxPosY, m_statusBoxH, true);
}

void SceneGear::DrawHp()
{
	int posY = kHpTextPosY + kStatusNumPosY;	// Y座標
	int hp = m_statusData.hp;					// HP
	int first = hp % 10;						// 一の位
	int second = (hp / 10) % 10;				// 十の位
	int third = ((hp / 10) / 10) % 10;			// 百の位
	int fourth = (((hp / 10) / 10) / 10) % 10;	// 千の位
	// 千の位
	DrawGraph(kStatusFourthPosX, posY, m_numH[fourth], true);
	// 百の位
	DrawGraph(kStatusThirdPosX, posY, m_numH[third], true);
	// 十の位
	DrawGraph(kStatusSecondPosX, posY, m_numH[second], true);
	// 一の位
	DrawGraph(kStatusFirstPosX, posY, m_numH[first], true);
	// プラス記号
	DrawGraph(kAddPosX, posY + kStatusNumPosY, m_addH, true);

	int addHp = m_pGear->GetAddHp();			// 追加HP
	first = addHp % 10;							// 一の位
	second = (addHp / 10) % 10;					// 十の位
	third = ((addHp / 10) / 10) % 10;			// 百の位
	fourth = (((addHp / 10) / 10) / 10) % 10;	// 千の位
	// 追加千の位
	DrawGraph(kAddStatusFourthPosX, posY, m_numH[fourth], true);
	// 追加百の位
	DrawGraph(kAddStatusThirdPosX, posY, m_numH[third], true);
	// 追加十の位
	DrawGraph(kAddStatusSecondPosX, posY, m_numH[second], true);
	// 追加一の位
	DrawGraph(kAddStatusFirstPosX, posY, m_numH[first], true);
}

void SceneGear::DrawMAtk()
{
	int posY = kMAtkTextPosY + kStatusNumPosY;	// Y座標
	int atk = m_statusData.meleeAtk;			// 近接攻撃力
	int first = atk % 10;						// 一の位
	int second = (atk / 10) % 10;				// 十の位
	int third = ((atk / 10) / 10) % 10;			// 百の位
	int fourth = (((atk / 10) / 10) / 10) % 10;	// 千の位
	// 千の位
	DrawGraph(kStatusFourthPosX, posY, m_numH[fourth], true);
	// 百の位
	DrawGraph(kStatusThirdPosX, posY, m_numH[third], true);
	// 十の位
	DrawGraph(kStatusSecondPosX, posY, m_numH[second], true);
	// 一の位
	DrawGraph(kStatusFirstPosX, posY, m_numH[first], true);
	// プラス記号
	DrawGraph(kAddPosX, posY + kStatusNumPosY, m_addH, true);

	int addAtk = m_pGear->GetAddMAtk();			// 追加近接攻撃力
	first = addAtk % 10;						// 一の位
	second = (addAtk / 10) % 10;				// 十の位
	third = ((addAtk / 10) / 10) % 10;			// 百の位
	fourth = (((addAtk / 10) / 10) / 10) % 10;	// 千の位
	// 追加千の位
	DrawGraph(kAddStatusFourthPosX, posY, m_numH[fourth], true);
	// 追加百の位
	DrawGraph(kAddStatusThirdPosX, posY, m_numH[third], true);
	// 追加十の位
	DrawGraph(kAddStatusSecondPosX, posY, m_numH[second], true);
	// 追加一の位
	DrawGraph(kAddStatusFirstPosX, posY, m_numH[first], true);
}

void SceneGear::DrawSAtk()
{
	int posY = kSAtkTextPosY + kStatusNumPosY;	// Y座標
	int atk = m_statusData.shotAtk;				// 遠距離攻撃力
	int first = atk % 10;						// 一の位
	int second = (atk / 10) % 10;				// 十の位
	int third = ((atk / 10) / 10) % 10;			// 百の位
	int fourth = (((atk / 10) / 10) / 10) % 10;	// 千の位
	// 千の位
	DrawGraph(kStatusFourthPosX, posY, m_numH[fourth], true);
	// 百の位
	DrawGraph(kStatusThirdPosX, posY, m_numH[third], true);
	// 十の位
	DrawGraph(kStatusSecondPosX, posY, m_numH[second], true);
	// 一の位
	DrawGraph(kStatusFirstPosX, posY, m_numH[first], true);
	// プラス記号
	DrawGraph(kAddPosX, posY + kStatusNumPosY, m_addH, true);

	int addAtk = m_pGear->GetAddSAtk();			// 追加遠距離攻撃力
	first = addAtk % 10;						// 一の位
	second = (addAtk / 10) % 10;				// 十の位
	third = ((addAtk / 10) / 10) % 10;			// 百の位
	fourth = (((addAtk / 10) / 10) / 10) % 10;	// 千の位
	// 追加千の位
	DrawGraph(kAddStatusFourthPosX, posY, m_numH[fourth], true);
	// 追加百の位
	DrawGraph(kAddStatusThirdPosX, posY, m_numH[third], true);
	// 追加十の位
	DrawGraph(kAddStatusSecondPosX, posY, m_numH[second], true);
	// 追加一の位
	DrawGraph(kAddStatusFirstPosX, posY, m_numH[first], true);
}

void SceneGear::DrawDef()
{
	int posY = kDefTextPosY + kStatusNumPosY;	// Y座標
	int atk = m_statusData.def;					// 防御力
	int first = atk % 10;						// 一の位
	int second = (atk / 10) % 10;				// 十の位
	int third = ((atk / 10) / 10) % 10;			// 百の位
	int fourth = (((atk / 10) / 10) / 10) % 10;	// 千の位
	// 千の位
	DrawGraph(kStatusFourthPosX, posY, m_numH[fourth], true);
	// 百の位
	DrawGraph(kStatusThirdPosX, posY, m_numH[third], true);
	// 十の位
	DrawGraph(kStatusSecondPosX, posY, m_numH[second], true);
	// 一の位
	DrawGraph(kStatusFirstPosX, posY, m_numH[first], true);
	// プラス記号
	DrawGraph(kAddPosX, posY + kStatusNumPosY, m_addH, true);

	int addAtk = m_pGear->GetAddDef();			// 追加防御力
	first = addAtk % 10;						// 一の位
	second = (addAtk / 10) % 10;				// 十の位
	third = ((addAtk / 10) / 10) % 10;			// 百の位
	fourth = (((addAtk / 10) / 10) / 10) % 10;	// 千の位
	// 追加千の位
	DrawGraph(kAddStatusFourthPosX, posY, m_numH[fourth], true);
	// 追加百の位
	DrawGraph(kAddStatusThirdPosX, posY, m_numH[third], true);
	// 追加十の位
	DrawGraph(kAddStatusSecondPosX, posY, m_numH[second], true);
	// 追加一の位
	DrawGraph(kAddStatusFirstPosX, posY, m_numH[first], true);
}
