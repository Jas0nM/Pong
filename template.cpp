// Includes
#include "template.h"
#include "Paddle.h"
#include "Ball.h"

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 20,20,20 );
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);

	//Funciuón para cambiat titulo de la ventana de ejecución
	agk::SetWindowTitle("Pong");

	//Función que permite o elimina la posibilidad de redimensionar la pantalla de ejecución
	agk::SetWindowAllowResize(0);

	//Inicialización de variable tipo gameState
	screens = gameState::gameScreen;

	//Creación y posicionamiento del sprite que mostrara la red
	const unsigned int net = agk::LoadSprite("media/net.png");
	agk::SetSpritePositionByOffset(net, agk::GetVirtualWidth()/2, agk::GetVirtualHeight()/2);

	//Creación de variables para pasar como argumentos al constructor de los objetos de la clase Paddle
	const unsigned int image = agk::LoadImage("media/paddle.png");
	const float space = 20.0f;
	const float xPlayer = (agk::GetImageWidth(image) / 2.0f) + space;
	const float xAi = (agk::GetVirtualWidth() - agk::GetImageWidth(image) / 2.0f) - space;
	
	//Creación de objetos de la clase Paddle
	playerPaddle = new Paddle(image, xPlayer);
	aiPaddle = new Paddle(image, xAi);

	//Creación de objeto de la clase Ball
	ballOne = new Ball(playerPaddle, aiPaddle);
}

int app::Loop (void)
{
	//Sentencia switch con la que se indica en que pantalla se encuentra el juego
	switch (screens)
	{
		case gameState::startScreen:
		{
			updateStartScreen();
		} break;
		case gameState::gameScreen:
		{
			updateGameScreen();
		}break;
		case gameState::resultScreen:
		{
			updateResultScreen();
		}break;
	}

	agk::Sync();

	return 0; // return 1 to close app
}

//Función para el control de la pantalla de inicio
void app::updateStartScreen()
{
	agk::Print("Pantalla de inicio");
	if (agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		screens = gameState::gameScreen;
	}
}

//Función para el control de la pantalla de juego
void app::updateGameScreen()
{
	agk::Print("Pantalla de juego");
	if (agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		screens = gameState::resultScreen;
	}

	//Control Jugador
	if (agk::GetRawKeyState(AGK_KEY_UP) || agk::GetRawKeyState(AGK_KEY_W))
	{
		playerPaddle->moveUp();
	}
	if (agk::GetRawKeyState(AGK_KEY_DOWN) || agk::GetRawKeyState(AGK_KEY_S))
	{
		playerPaddle->moveDown();
	}

	//Control IA
	if (ballOne->getY() < aiPaddle->getY())
	{
		aiPaddle->moveUp();
	}
	if (ballOne->getY() > aiPaddle->getY())
	{
		aiPaddle->moveDown();
	}

	ballOne->update();
}

//Función para el control de la pantalla de resultados
void app::updateResultScreen()
{
	agk::Print("Pantalla de resultados");
	if (agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		screens = gameState::startScreen;
	}
}

void app::End (void)
{

}
