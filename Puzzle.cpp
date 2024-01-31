#include "Puzzle.h"

static const int R = 35; //半径
static const int OFF_X = 400;
static const int OFF_Y = 200;

static const int HEIGET = 5;
static const int WIDTH = 6;
static const unsigned int COLORS[] =
{
	GetColor(250,0,0),//赤
	GetColor(0,255,0),//緑
	GetColor(0,0,255),//青
	GetColor(250,255,0),//黄色
};

static const int ColorNum = sizeof(COLORS) / sizeof(COLORS[0]);

Puzzle::Puzzle(GameObject* parent)
{
	////C言語の書き方
	//for (int y = 0; y < 5; y++)
	//{
	//	for (int x = 0; x < 6; x++)
	//	{
	//		field[y][x].color = rand() % ColorNum;
	//	}
	//}
	for (int y = 0; y < 5; y++) {
		std::vector<Piece> tmp;

		for (int x = 0; x < 6; x++)
		{
			Piece p;
			p.color = rand() % ColorNum;
		//	p.selected = false;

			p.erase = 0;
			p.fallAdjust = 0;
			tmp.push_back(p);
		}
		field.push_back(tmp);
	}
	selX = -1;
	selY = -1;
	state = S_IDLE;
}

Puzzle::~Puzzle()
{
}

void Puzzle::Update()
{
	//field[0][0].selected = true;

	switch (state)
	{
	case S_IDLE:
		UpdateIdle();
		break;
	case S_MOVE:
		UpdateMove();
		break;
	case S_ERASE:
		UpdateErase();
		break;
	case S_FALL:
		UpdateFall();
		break;
	case S_ATTACK:
		UpdateAttack();

	}
}

	void Puzzle::UpdateIdle()
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)//マウスの左ボタンをクリックした
		{
			if (lastButton == false) {

			
			//int mouseX, mouseY;
				GetMousePoint(&mouseX, &mouseY);//マウスポインターの座標が入る
			  for (int y = 0; y < 5; y++)
			  {
				for (int x = 0; x < 6; x++)
				{
					int cx = x * R*2 + OFF_X;
					int cy = y * R*2 + OFF_Y;
					if (mouseX >= cx - R && mouseX < cx + R &&
						mouseY >= cy - R && mouseY < cy + R)
					{
						//field[y][x].selected = true;
						selX = x;
						selY = y;
						state = S_MOVE;
					}
			  	}
              }

			}
			lastButton = true;
		}
	    else
	    {
		  lastButton = false;
	    }
    }

void Puzzle::Draw()
{
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 6; x++){
			int xpos = x * R * 2 + OFF_X;
			int ypos = y * R * 2 + OFF_Y;
			bool alphaSet = false;
			if (x == selX && y == selY)
			{
				alphaSet = true;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			}
			if (state == S_ERASE && field[y][x].erase > 0)
			{
				alphaSet = true;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, eraseAlpha);
			}

			DrawCircle(xpos, ypos, R, GetColor(255, 255, 255));
			int r = field[y][x].color;
			DrawCircle(xpos, ypos, (R - 4), COLORS[r]);

			if (alphaSet)
			{
				alphaSet = false;
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			DrawFormatString(xpos,ypos,GetColor(255, 255, 255), "%d",field[y][x].erase);


			if (selX >= 0)
			{
				DrawCircle(mouseX, mouseY, R + 4, GetColor(255, 255, 255));
				int r = field[selY][selX].color;
				DrawCircle(mouseX, mouseY, R, COLORS[r]);
			}
		}
		


		//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);//半透明にする
		//DrawCircle(300, 150, 50, COLORS[0]);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す

		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d %d",
			mouseX, mouseY);
	}
}

void Puzzle::UpdateMove()
{
	GetMousePoint(&mouseX, &mouseY);

	int newX = -1;
	int newY = -1;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			int cx = x * R * 2 + OFF_X;
			int cy = y * R * 2 + OFF_Y;
			if (mouseX >= cx - R && mouseX < cx + R &&
				mouseY >= cy - R && mouseY < cy + R)
			{
				newX = x;
				newY = y;
				state = S_MOVE;
			}
		}
	}
	if (newX >= 0 && (newX != selX || newY != selY))
	{
		Piece tmp = field[newY][newX];
		field[newY][newX] = field[selY][selX];
		field[selY][selX] = tmp;
		selX = newX;
		selY = newY;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
	{
		selX = -1;

		if (CanErase())
		{
			eraseTimer = 0;
			state = S_ERASE;
		}
		else
		{
			state = S_IDLE;
		}
		/*
		もし、三つ以上並んだブロックがあるなら
		state = S_ERASE;
		ないなら
		state = S_IDLE;
		*/
		state = S_IDLE;
	}
}

void Puzzle::UpdateErase()
{
	eraseTimer += 1.0f / 60.0f;
	//eraseTimer < 0.1fまでに消える
	eraseAlpha = 255 - 255 * eraseTimer / 1.0f;

	if (eraseAlpha < 0.0f)
		eraseAlpha < 0.0f;

	if (eraseTimer >= 1.0f)
	{
		PrepareFall();
		state = S_FALL;
	}
}

void Puzzle::UpdateFall()
{
	bool fallEnd = true;//全部が落ちた
	for (int y = 0; y < HEIGET; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (field[y][x].fallAdjust < 0)
			{
				fallEnd = false;
				field[y][x].fallAdjust += 1.0f;
				if (field[y][x].fallAdjust > 0)
				{
					field[y][x].fallAdjust = 0;
				}
			}
		}
	}

	if (fallEnd)
	{
		if (CanErase())
		{
			eraseTimer = 0;
			state = S_ERASE;
		}
		else
		{
			state = S_IDLE;
		}
	}
	//state = S_IDLE;
}

void Puzzle::UpdateAttack()
{
}

bool Puzzle::CanErase()
{
	//ぜんぶのPeace:Eraseを0ニスル
	//3つ並んでる場合は、そこのEraseを1に
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			field[y][x].erase = 0;
		}
	}

	int eraseNumber = 1;
	for (int y = 0; y < HEIGET; y++)
	{
		for (int x = 0; x < WIDTH-2; x++)
		{
			if (field[y][x + 0].color == field[y][x + 1].color && field[y][x + 0].color == field[y][x + 2].color) {
				field[y][x + 0].erase = eraseNumber;
				field[y][x + 1].erase = eraseNumber;
				field[y][x + 2].erase = eraseNumber;
				eraseNumber++;
			}

		}
	}
	for (int y = 0; y < HEIGET-2; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (field[y+0][x].color == field[y+1][x].color && field[y+0][x].color == field[y+2][x].color) {
				field[y+0][x].erase = eraseNumber;
				field[y+1][x].erase = eraseNumber;
				field[y+2][x].erase = eraseNumber;
				eraseNumber++;
			}

		}
	}

	if (eraseNumber >= 1)
	{
		return true;
	}

		return false;
	
	
}

void Puzzle::PrepareFall()
{
	for (int x = 0; x < WIDTH; x++)
	{
		int erased = 0;
		for (int y = HEIGET - 1; y >= 0; y--)
		{
			if (field[y][x].erase > 0)
			{
				erased++;
			}
			else
			{
				field[y + erased][x] = field[x][y];
				field[y + erased][x].fallAdjust = -R * 2 * erased;
			}
		}
		for (int y = 0; y < erased; y++)
		{
			field[y][x].color = rand() % ColorNum;
			field[y][x].erase = 0;
			field[y][x].fallAdjust = -R * 2 * erased;
		}
	}
}
