#pragma once
class Paddle
{
	private:
		static const float moveSpeed;
		unsigned int sprite;
		float x, y;
		void move(float moveDirection);

	public:
		Paddle(unsigned int image, float startX);
		void moveUp();
		void moveDown();
		void reset();
		bool isCollidingWhithSprite(unsigned int otherSprite) const;
		float getY() const;
};
