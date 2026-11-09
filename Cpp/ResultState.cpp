#include	"../h/ResultState.h"
#include	"../h/TitleState.h"

void ResultState::Enter() {
	m_images[0].SetImage("Lose2.png"); m_images[1].SetImage("Win2.png");
}

StateBase* ResultState::Loop() {
	DrawString(0, 0, "Result", 0xffffff);
	m_resultFlag ? Draw(m_resultFlag, Vector2(0, 0), Vector2(1.0, 0.8)) :
		Draw(m_resultFlag, Vector2(0, 0), Vector2(1.0, 0.8));

	m_player.GetInput().Update();
	if (m_player.GetInput().GetKeyDown(KEY_INPUT_ESCAPE)) return new TitleState;
	return this;
}

void ResultState::Exit() {

}

void ResultState::Draw(int index, Vector2 pos, Vector2 scale) { m_images[index].ExDraw(pos, scale); }