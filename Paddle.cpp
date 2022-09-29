#include "Paddle.h"
#include "agk.h"

//Variable con la que se indica la velocidad que tendran los objetos de esta clase
const float Paddle::moveSpeed = 360.0f;

//Constructor
Paddle::Paddle(unsigned int image, float startX)
{
	//Variable que guardar la imagen que tendra el sprite
	sprite = agk::CreateSprite(image);

	//Variables para posicionar al sprite
	x = startX;
	y = agk::GetVirtualHeight()/2.0f;

	//Función para actualizar la posición del sprite
	agk::SetSpritePositionByOffset(sprite, x, y);
}

//Función para indicar un movimiento hacia arriba
void Paddle::moveUp() 
{
	move(-1.0f);
}

//Función para indicar un movimiento hacia abajo
void Paddle::moveDown() 
{
	move(1.0f);
}

//Función con la que se calcula el movimiento que tendran los objetos de la clase
void Paddle::move(float moveDirection)
{
	//Variable regulada que indica el movimiento que tendran los objetos
	const float moveY = (moveSpeed * moveDirection) * agk::GetFrameTime();
	
	//Variable que contiene el valor actualizado que se le dara a la posición en Y
	const float newY = y + moveY;

	//Variables de posición minima y maxima en el eje Y para los objetos de la clase
	const float minY = agk::GetSpriteHeight(sprite) / 2.0f;
	const float maxY = agk::GetVirtualHeight() - minY;

	//Condición con la que se evita que los objetos salgan de la pantalla de ejecución
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

	//Función para actualizar la posición del sprite
	agk::SetSpritePositionByOffset(sprite, x, y);
}

//Función para posicionar a los objetos como al inicio de la ejecución
void Paddle::reset()
{
	agk::SetSpritePositionByOffset(sprite, x, agk::GetVirtualHeight()/2.0f);
}

//Función que verifica si el objeto esta colisionando con el sprite indicado como parametro
bool Paddle::isCollidingWhithSprite(unsigned int otherSprite) const
{
	return 1 == agk::GetSpriteCollision(sprite, otherSprite);
}

//Función que devuelve la posición en Y del sprite
float Paddle::getY() const
{
	return agk::GetSpriteYByOffset(sprite);
}
