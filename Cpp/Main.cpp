#include	"DxLib.h"
#include	"../h/TitleState.h"
#include	"../h/ErrorMessage.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1080, 720, 32);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	try {
		StateBase* state = new TitleState;
		state->Enter();

		while (1) {
			ClearDrawScreen();

			StateBase* next = state->Loop();

			if (state != next) {
				state->Exit();
				delete state;

				state = next;
				state->Enter();
			}

			ScreenFlip();
			if (CheckHitKey(KEY_INPUT_0) == 1) break;
			if (ProcessMessage() == -1) break;
		}
	}
	catch (ErrorMassage massage) {
		while (1) {
			ClearDrawScreen();

			massage.Show();

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_0) == 1) break;
			if (ProcessMessage() == -1) break;
		}
	}

	DxLib_End();
	return 0;
}