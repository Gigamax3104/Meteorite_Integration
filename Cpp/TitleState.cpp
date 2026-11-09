#include	"../h/TitleState.h"
#include	"../h/GameState.h"

void TitleState::Enter() {

}

StateBase* TitleState::Loop() {
	DrawString(0, 0, "Title", 0xffffff);

	m_player.GetInput().Update();
	if (m_player.GetInput().GetKeyDown(KEY_INPUT_SPACE)) return new GameState;

	return this;
}

void TitleState::Exit() {

}