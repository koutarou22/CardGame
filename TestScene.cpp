#include "TestScene.h"
#include"Trump.h"
#include"Puzzle.h"
//コンストラクタ
TestScene::TestScene(GameObject * parent)
	:GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{

	//Instantiate<Trump>(this)//トランプ配るやつ
	Instantiate<Puzzle>(this);
	
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
