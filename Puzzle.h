#pragma once
#include"Engine/GameObject.h"
#include<vector>
/// <summary>
/// パズドラのプレイ画面
/// 　　　　　Sato Kotaro
/// </summary>
class Puzzle
	:public GameObject
{
public:
	Puzzle(GameObject* parent);
	~Puzzle();
	void Update() override;
	void Draw() override;

private:
	struct Piece
	{
		int color;
		//bool selected;
		int erase; //消えるピース 0: < 消えない :>0:消える
		float fallAdjust; //落下の補正
	};
	//C言語の場合Piece field[5][6];
	std::vector<std::vector<Piece>> field;//C++

	int selX, selY;
	int mouseX, mouseY;


	bool lastButton;
	float eraseTimer;//消えていく時間(秒)
	int eraseAlpha;

	//状態遷移
	enum State {

		S_IDLE,
		S_MOVE,
		S_ERASE,
		S_FALL,
		S_ATTACK,
	};
	State state;//状態変数

	void UpdateIdle();
	void UpdateMove();
	void UpdateErase();
	void UpdateFall();
	void UpdateAttack();



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool CanErase();
	void PrepareFall();

	int soundErase;
	int soundFall;

	bool fallSoundRequested;
};