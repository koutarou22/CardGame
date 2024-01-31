#pragma once
#include"Engine/GameObject.h"
#include<vector>
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
		int erase; //Á‚¦‚éƒs[ƒX 0: < Á‚¦‚È‚¢ :>0:Á‚¦‚é
		float fallAdjust; //—‰º‚Ì•â³
	};
	//CŒ¾Œê‚Ìê‡Piece field[5][6];
	std::vector<std::vector<Piece>> field;//C++

	int selX, selY;
	int mouseX, mouseY;


	bool lastButton;
	float eraseTimer;//Á‚¦‚Ä‚¢‚­ŠÔ(•b)
	int eraseAlpha;

	//ó‘Ô‘JˆÚ
	enum State {

		S_IDLE,
		S_MOVE,
		S_ERASE,
		S_FALL,
		S_ATTACK,
	};
	State state;//ó‘Ô•Ï”

	void UpdateIdle();
	void UpdateMove();
	void UpdateErase();
	void UpdateFall();
	void UpdateAttack();

	bool CanErase();
	void PrepareFall();
};