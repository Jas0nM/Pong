#include "Ball.h"
#include "Paddle.h"
#include "agk.h"

//Variable con la que se indica la velocidad que tendran los objetos de esta clase
const float Ball::moveSpeed = 600.0f;

//Constructor
Ball::Ball(Paddle* leftPaddle, Paddle* rightPaddle)
{
	//Variable a la que se le indica el archivo de imagen que tendra para el objeto
	sprite = agk::LoadSprite("media/ball.png");

	//Variable que guardara un archivo de audio tipo OGG
	bounceSound = agk::LoadSoundOGG("media/bounce.ogg");

	//Variables para posicionar al sprite
	x = agk::GetVirtualWidth() / 2.0f;
	y = agk::GetVirtualHeight() / 2.0f;

	//Función para actualizar la posición del sprite
	agk::SetSpritePositionByOffset(sprite, x, y);

	/* Variables que se usaran para darle dirección al sprite
	Se hace una conversion implicita con "static_cast" ya que las funciones "Random" devuelven valores tipo int */
	velX = static_cast<float>(agk::RandomSign(agk::Random(50, 100))) / 100.0f;
	velY = static_cast<float>(agk::RandomSign(agk::Random(0, 100))) / 100.0f;

	/* variable que guardara la longitud de la velocidad del objeto, se usa el teorema de pitagoras */
	const float length = agk::Sqrt((velX * velX) + (velY * velY));

	velX = (velX / length) * moveSpeed;
	velY = (velY / length) * moveSpeed;

	//Inicialización de arreglo de dos posiciones que guardara dos objetos de la clase Paddle
	paddles[0] = leftPaddle;
	paddles[1] = rightPaddle;

	//Variable tipo bool que indica si el objeto esta colisionando con otro objeto de la clase paddle
	collidingWithPaddle = false;
}

//Función con la que se actualizara el movimiento que tendra el objeto a lo largo de la ejecución
void Ball::update()
{
	//Variable que guarda el frame time
	const float frameTime = agk::GetFrameTime();
	x += velX * frameTime;
	y += velY * frameTime;

	//Variables de posición minima y maxima en el eje Y para los objetos de la clase
	const float minY = agk::GetSpriteHeight(sprite) / 2.0f;
	const float maxY = agk::GetVirtualHeight() - minY;

	//Condición con la que se cambia la dirección en Y en caso de que la posición del objeto sea menor o mayor a las variables indicadas
	if (y < minY || y > maxY)
	{
		agk::PlaySound(bounceSound);
		velY = -velY;
	}

	//Condición con la que se verifica si el objeto esta colisionando con la paleta del jugador o la IA
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

	//Función que actualiza la posición del sprite
	agk::SetSpritePositionByOffset(sprite, x, y);
}

//Función que devuelve la posición en Y del sprite
float Ball::getY() const
{
	return agk::GetSpriteYByOffset(sprite);
}
