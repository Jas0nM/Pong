// Includes
#include "template.h"
#include "Paddle.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 20,20,20 );
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetWindowTitle("Pong");
	agk::SetWindowAllowResize(0);

	screens = gameState::gameScreen;

	const unsigned int net = agk::LoadSprite("media/net.png");
	agk::SetSpritePositionByOffset(net, agk::GetVirtualWidth()/2, agk::GetVirtualHeight()/2);

	const unsigned int image = agk::LoadImage("media/paddle.png");
	const float space = 20.0f;
	const float xPlayer = (agk::GetImageWidth(image) / 2.0f) + space;
	const float xAi = (agk::GetVirtualWidth() - agk::GetImageWidth(image) / 2.0f) - space;
	playerPaddle = new Paddle(image, xPlayer);
	aiPaddle = new Paddle(image, xAi);
}

int app::Loop (void)
{
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

void app::updateStartScreen()
{
	agk::Print("Pantalla de inicio");
	if (agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		screens = gameState::gameScreen;
	}
}

void app::updateGameScreen()
{
	agk::Print("Pantalla de juego");
	if (agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		screens = gameState::resultScreen;
	}

	if (agk::GetRawKeyState(AGK_KEY_UP) || agk::GetRawKeyState(AGK_KEY_W))
	{
		playerPaddle->moveUP();
	}
	if (agk::GetRawKeyState(AGK_KEY_DOWN) || agk::GetRawKeyState(AGK_KEY_S))
	{
		playerPaddle->moveDown();
	}
}

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

