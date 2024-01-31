#pragma once
#include"Engine/GameObject.h"
#include<vector>
class Trump:public GameObject
{
public:
	Trump(GameObject* parent);
	~Trump();
	void Update() override;
	void Draw() override;
private:
	int gHandle;

	struct Card
	{
		int mark;
		int number;
		bool moving;
		float x, y;
		float startX, startY;
		float endX, endY;
		float rate;//ˆÚ“®‚ÌŠ„‡

	};

	std::vector<Card>cards;//RD‚Ì–ğŠ„
	std::vector<Card>Player1;
	std::vector<Card>Player2;

	int counter;
	int playerID;

	bool lastN;
	bool lastM;
};

