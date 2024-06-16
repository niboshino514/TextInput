#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"


SceneTitle::SceneTitle() :
	m_isEnd(false)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{


	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	// パッドのアップデート処理
	Pad::update();
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Mainに切り替え
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));
}