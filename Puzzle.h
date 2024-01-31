#pragma once
#include"Engine/GameObject.h"
#include<vector>
/// <summary>
/// �p�Y�h���̃v���C���
/// �@�@�@�@�@Sato Kotaro
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
		int erase; //������s�[�X 0: < �����Ȃ� :>0:������
		float fallAdjust; //�����̕␳
	};
	//C����̏ꍇPiece field[5][6];
	std::vector<std::vector<Piece>> field;//C++

	int selX, selY;
	int mouseX, mouseY;


	bool lastButton;
	float eraseTimer;//�����Ă�������(�b)
	int eraseAlpha;

	//��ԑJ��
	enum State {

		S_IDLE,
		S_MOVE,
		S_ERASE,
		S_FALL,
		S_ATTACK,
	};
	State state;//��ԕϐ�

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