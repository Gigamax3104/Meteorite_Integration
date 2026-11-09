#include	"../h/ResultState.h"
#include	"../h/GameState.h"

#include	"../Itou/ContentCreation2026_10_19/Temp.h"

#include	"../Matsunaga/Collision/Collision.h"

void GameState::Enter() {
	ptr_class_time->GetNowTime();
	m_turret.InitTurretPosition();
}

StateBase* GameState::Loop() {
	ptr_class_time->GetNowTime();

	DrawString(0, 0, "Game", 0xffffff);

	m_turret.InputTurretPosition();
	m_turret.InputTurretShoot();
	m_turret.UpdateTurretPosition();
	m_ammo.SetAmmoPosition();
	m_turret.RenderTurretAndTurretCenterPoint();
	m_ammo.SetAmmoPosition();

	m_system.Update();

	for (int i = 0; i < AMMO_DATA_SIZE; i++) {
		Vector2 pos = m_ammo.Position(i);
		double radius = m_ammo.Radius();
		bool flag = m_ammo.Flag(i);

		//ptr_class_ammo->GiveAmmoInfo(&pos.x, &pos.y, i, &radius, &flag);
		if (!flag) continue;

		for (int j = 0; j < m_system.GetMeteorite().size(); j++) {
			if (Collision::CircleAndCircle(pos, radius, m_system.GetMeteorite()[j]->Position(), m_system.GetMeteorite()[j]->Radius())) {
				m_ammo.DestroyAmmo(i);
				continue;
			}
		}
	}

	if (m_player.GetInput().GetKeyDown(KEY_INPUT_RETURN)) return new ResultState(false);

	return this;
}

void GameState::Exit() {

}