#include "Trump.h"
#include <assert.h>

Trump::Trump(GameObject* parent)
{
	gHandle = LoadGraph("Assets/trump.png");
	//失敗すると、gHandle < 0 になる
	assert(gHandle >= 0);
	/*mark = 0;
	number = 1*/
	int i = 0;
	for (int m = 0; m < 4; m++)
	{
		for (int n = 1; n <= 13; n++)
		{
			Card c;
			c.mark = m;
			c.number = n;
			c.rate = 0;
			c.moving = false;
			cards.push_back(c);
			
		}
	}

	for (int rgt = 0; rgt < cards.size(); rgt++)
	{
		int lft = rand() % cards.size();
		Card tmp = cards[rgt];
		cards[rgt] = cards[lft];
		cards[lft] = tmp;
	
	}
	counter = 0;
	playerID = 0;
}

Trump::~Trump()
{

}

void Trump::Update()
{
	counter -= 1;//+= 1;この書き方でもプログラムとしては間違っていないが
	if (counter <= 0)// >= 10　『　引く考えを持て　』
	{
		counter = 10;
          if (cards.size() > 0)
	      {
		     Card c = cards[0];
		     cards.erase(cards.begin());
			 c.moving = true;
			 c.startX = 0;
			 c.startY = 300;
			 c.rate = 0.0;
			 c.x = c.startX;
			 c.y = c.startY;


			 if (playerID == 0)
			 {
				 c.endX = Player1.size()*20;
				 c.endY = 50;
				 Player1.push_back(c);
				 playerID = 1;
			 }
			 else
			 {
				 c.endX = Player2.size()*20;
				 c.endY = 550;
				 Player2.push_back(c);
				 playerID = 0;
			 }
	      }
	}
	for (Card& c : Player1)
	{
		if (c.moving)
		{
			c.rate += 0.01f;
			float r = sinf(c.rate * DX_PI/2.0);
			c.x = (c.endX - c.startX) * r + c.startX;
			c.y = (c.endY - c.startY) * r + c.startY;
			if (c.rate >= 1.0f)
			{
				c.moving = false;
			}
		}
	}
	for (Card& c : Player2)
	{
		if (c.moving)
		{
			c.rate += 0.01f;
			float r = sinf(c.rate * DX_PI / 2.0);
			c.x = (c.endX - c.startX) * r + c.startX;
			c.y = (c.endY - c.startY) * r + c.startY;
			if (c.rate >= 1.0f)
			{
				c.moving = false;
			}
		}
	}
	
#if 0
    if (CheckHitKey(KEY_INPUT_N) > 0)
	{
		if (lastN == false)
		{
			number += 1;

			if (number > 13);
			{
				number = 1;
			}
		}
		lastN = true;
	}
	else
	{
		lastN = false;
	}
	

	if (CheckHitKey(KEY_INPUT_M) > 0)
	{
		mark += 1;
		if (mark > 3)
		{
			mark = 1;
		}
	}
	else
	{
		lastN = false;
	}


#endif
}

void Trump::Draw()
{

	//52枚並べて表示・山札
	for (int i = 0; i < cards.size(); i++)
	{
		//cardsのデータの通りに表示する
		DrawRectGraph(0 + i * 20, 300, 56 * cards[i].number, 80 * cards[i].mark, 56, 80, gHandle, TRUE);
	}

	//プレイヤー１
	for (int i = 0; i < Player1.size(); i++)
	{
		if (Player1[i].moving)
		{
			DrawRectGraph(Player1[i].x,Player1[i].y, 56 * Player1[i].number, 80 * Player1[i].mark, 56, 80, gHandle, TRUE);
		}
		else
		{
			DrawRectGraph(0 + i * 20, 50, 56 * Player1[i].number, 80 * Player1[i].mark, 56, 80, gHandle, TRUE);
		}
		
	}

	//プレイヤー2
	for (int i = 0; i < Player2.size(); i++)
	{
		if (Player2[i].moving)
		{
			DrawRectGraph(Player2[i].x, Player2[i].y, 56 * Player2[i].number, 80 * Player2[i].mark, 56, 80, gHandle, TRUE);
		}
		else
		{
			DrawRectGraph(0 + i * 20, 550, 56 * Player2[i].number, 80 * Player2[i].mark, 56, 80, gHandle, TRUE);
		}
		
	}
}
	
