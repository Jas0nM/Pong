#include "Paddle.h"
#include "agk.h"

const float Paddle::moveSpeed = 350.0f;

Paddle::Paddle(unsigned int image, float startX)
{
	sprite = agk::CreateSprite(image);
	x = startX;
	y = agk::GetVirtualHeight() / 2.0f;
	agk::SetSpritePositionByOffset(sprite, x, y);
}

void Paddle::moveUP() 
{
	move(-1.0f);
}

void Paddle::moveDown() 
{
	move(1.0f);
}

void Paddle::move(float moveDirection)
{
	const float moveY = (moveSpeed * moveDirection) * agk::GetFrameTime();
	const float newY = y + moveY;
	const float minY = agk::GetSpriteHeight(sprite) / 2.0f;
	const float maxY = agk::GetVirtualHeight() - minY;

	if (newY < minY)
	{
		y = minY;
	}
	else if (newY > maxY)
	{
		y = maxY;
	}
	else
	{
		y = newY;
	}

	agk::SetSpritePositionByOffset(sprite, x, y);
}

void Paddle::reset()
{
	agk::SetSpritePositionByOffset(sprite, x, agk::GetVirtualHeight()/2.0f);
}

bool Paddle::isCollidingWhithSprite(unsigned int otherSprite) const
{
	return 1 == agk::GetSpriteCollision(sprite, otherSprite);
}
