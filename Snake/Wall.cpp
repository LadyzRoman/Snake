#include "Snake.h"


Stone* Wall::addNewStone()
{
	Stone* temp = new Stone[stoneCount + 1];
	memcpy(temp, stones, stoneCount * sizeof(Stone));
	temp[stoneCount] = Stone();
	stones = temp;
	stoneCount++;
	return &stones[stoneCount - 1];
}

Wall::Wall()
{
	stoneCount = 0;
	stones = nullptr;
}

void Wall::deleteWall()
{
	delete[] stones;
}