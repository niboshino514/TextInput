#pragma once
#include "DxLib.h"
#include <list>
#include <ctype.h> 

struct MOJI_DATA
{
	char moji[3];
};

std::list<MOJI_DATA>	g_fonts;		// 文字データ
int g_InputHandle;						// インプットハンドル

void dataUpdate(void);					// データを更新
void drawData(void);					// データ表示

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);
	SetMainWindowText("文字列分割てすと");
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	g_InputHandle = MakeKeyInput(30, FALSE, FALSE, FALSE);

	// 作成したキー入力ハンドルをアクティブにする
	SetActiveKeyInput(g_InputHandle);

	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ループ
	while (!ProcessMessage())
	{
		bool isUpdateData = false;

		// 入力が終了している場合は終了
		if (CheckKeyInput(g_InputHandle) != 0) break;

		// 画面のクリア
		ClearDrawScreen();

		// 入力モードを描画
		DrawKeyInputModeString(640, 480);

		// 入力途中の文字列を描画
		DrawKeyInputString(0, 0, g_InputHandle);

		dataUpdate();

		drawData();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	// 用済みのインプットハンドルを削除する
	DeleteKeyInput(g_InputHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}


void dataUpdate()
{
	char String[256];

	// 入力された文字列を取得
	GetKeyInputString(String, g_InputHandle);

	g_fonts.clear();

	// 細かく作りこむのが面倒だった為に邪道処理。
	for (int j = 0; j < strlen(String); j++)
	{
		MOJI_DATA add_data;

		if (isalnum((int)String[j]) != 0)
		{
			// 半角
			//sprintf(add_data.moji, "%c", String[j]);
		}
		else
		{
			// 全角。邪道処理。よい子は真似しちゃ駄目。
			//sprintf(add_data.moji, "%c%c", String[j], String[j + 1]);
			j++;
		}
		g_fonts.push_back(add_data);
	}
}

void drawData()
{
	int ypos = 14;
	int count = 0;
	::std::list<MOJI_DATA>::iterator ite;
	for (ite = g_fonts.begin(); ite != g_fonts.end(); ite++)
	{
		DrawFormatString(0, ypos, GetColor(255, 255, 255), "%02d:%s", count, ite->moji);
		ypos += 14;
		count++;
	}
}