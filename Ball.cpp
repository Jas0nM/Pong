#include "Ball.h"
#include "Paddle.h"
#include "agk.h"

const float Ball::moveSpeed = 200.0f;

Ball::Ball(Paddle* leftPaddle, Paddle* rightPaddle)
{
	sprite = agk::LoadSprite("media/ball.png");
	bounceSound = agk::LoadSoundOGG("media/bounce.ogg");
	x = agk::GetVirtualWidth() / 2.0f;
	y = agk::GetVirtualHeight() / 2.0f;
	agk::SetSpritePositionByOffset(sprite, x, y);

	velX = static_cast<float>(agk::RandomSign(agk::Random(50, 100))) / 100.0f;
	velY = static_cast<float>(agk::RandomSign(agk::Random(0, 100))) / 100.0f;
	const float length = agk::Sqrt((velX * velX) + (velY * velY));
	velX = (velX / length) * moveSpeed;
	velY = (velY / length) * moveSpeed;

	paddles[0] = leftPaddle;
	paddles[1] = rightPaddle;
	collidingWithPaddle = false;
}

void Ball::update()
{
	const float frameTime = agk::GetFrameTime();
	x += velX * frameTime;
	y += velY * frameTime;

	const float minY = agk::GetSpriteHeight(sprite) / 2.0f;
	const float maxY = agk::GetVirtualHeight() - minY;
	if (y < minY || y > maxY)
	{
		agk::PlaySound(bounceSound);
		velY = -velY;
	}

	if (paddles[0]->isCollidingWhithSprite(sprite) || paddles[1]->isCollidingWhithSprite(sprite))
	{
		if (!collidingWithPaddle)
		{
			agk::PlaySound(bounceSound);
			velX = -velX;
			collidingWithPaddle = true;
		}
	}
	else
	{
		collidingWithPaddle = false;
	}

	agk::SetSpritePositionByOffset(sprite, x, y);
}
