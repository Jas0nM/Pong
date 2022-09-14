// Includes
#include "template.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetWindowAllowResize(0);
	agk::SetWindowTitle("Pong");
	VarGameState = gameState::startScreen;
}

int app::Loop (void)
{

	switch (VarGameState) {
		case gameState::startScreen:
		{
			updateStartScreen();
		} break;

		case gameState::gameScreen:
		{
			updateGameScreen();
		} break;

		case gameState::resultScreen:
		{
			updateResultScreen();
		}break;
	}

	agk::Sync();

	return 0; // return 1 to close app
}

void app::updateStartScreen() {
	agk::Print("Esta es la pantalla de inicio");

	if (agk::GetRawKeyPressed(AGK_KEY_SPACE)) {
		VarGameState = gameState::gameScreen;
	}
}

void app::updateGameScreen() {
	agk::Print("Esta es la pantalla de juego");

	if (agk::GetRawKeyPressed(AGK_KEY_SPACE)) {
		VarGameState = gameState::resultScreen;
	}
}

void app::updateResultScreen() {
	agk::Print("Esta es la pantalla de resultados");

	if (agk::GetRawKeyPressed(AGK_KEY_SPACE)) {
		VarGameState = gameState::startScreen;
	}
}

void app::End (void)
{

}
