#include "TestScene.h"
#include"Trump.h"
#include"Puzzle.h"
//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	:GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{

	//Instantiate<Trump>(this)//�g�����v�z����
	Instantiate<Puzzle>(this);
	
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
