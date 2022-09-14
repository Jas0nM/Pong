#ifndef _H_AGK_TEMPLATE_
#define _H_AGK_TEMPLATE_

// Link to GDK libraries
#include "AGK.h"

#define DEVICE_WIDTH 1024
#define DEVICE_HEIGHT 768
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false

// used to make a more unique folder for the write path
#define COMPANY_NAME "My Company"

enum class gameState {
	startScreen,
	gameScreen,
	resultScreen
};

// Global values for the app
class app
{
	gameState VarGameState;

	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions - mike to experiment with a derived class for this..
		void Begin( void );
		int Loop( void );
		void End( void );

	private:
		void updateStartScreen();
		void updateGameScreen();
		void updateResultScreen();

};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif