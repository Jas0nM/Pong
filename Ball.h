#pragma once

class Paddle;

class Ball
{
	private:
		static const float moveSpeed;
		unsigned int sprite, bounceSound;
		float x, y, velX, velY;
		Paddle* paddles[2];
		bool collidingWithPaddle;

	public:
		Ball(Paddle* leftPaddle, Paddle* rightPaddle);
		void update();
		float getY() const;
};
