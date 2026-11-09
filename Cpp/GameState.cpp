#include	"../h/ResultState.h"
#include	"../h/GameState.h"

void GameState::Enter() {

}

StateBase* GameState::Loop() {
	DrawString(0, 0, "Game", 0xffffff);

	m_player.GetInput().Update();
	if (m_player.GetInput().GetKeyDown(KEY_INPUT_RETURN)) return new ResultState(false);

	return this;
}

void GameState::Exit() {

}