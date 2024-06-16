#include "DxLib.h"

#include "SceneMain.h"
#include "SceneTitle.h"
#include "Pad.h"

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{

}

SceneBase* SceneMain::update()
{
	// パッドのアップデート処理
	Pad::update();

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return (new SceneTitle);
	}

	return this;
}

void SceneMain::draw()
{
	DrawString(0, 0, "メイン画面", GetColor(255, 255, 255));
}