#include "game_state_manager.h"
Game_state_manager::~Game_state_manager()
{
	for (int i = 0; i < m_game_state.size(); i++) {
		if (m_game_state[i] != nullptr) {
			delete m_game_state[i];
			m_game_state[i] = nullptr;
		}
	}
}
void Game_state_manager::push(Game_state* state)
{
	//if (!m_game_state.empty() && m_game_state.back()->get_state_ID() == m_game_state[m_game_state.size() - 1]->get_state_ID()) return;
	try {
		m_game_state.push_back(state);
		if (!state->on_start()) throw - 1;
		
	}
	catch (int ) {
		delete m_game_state.back();
		m_game_state.pop_back();
		exit(EXIT_FAILURE);
	}
}

void Game_state_manager::replace(Game_state* state)
{
	if (!m_game_state.empty())
	{
		if (m_game_state.back()->on_exit())
		{
			//delete m_game_state.back();
			m_game_state.pop_back();
		}
	}
	try {
		m_game_state.push_back(state);
		if (!state->on_start()) throw - 1;

	}
	catch (int) {
		delete m_game_state.back();
		m_game_state.pop_back();
		exit(EXIT_FAILURE);
	}
}

void Game_state_manager::pop()
{
	if (!m_game_state.empty()) {
		if (m_game_state.back()->on_exit()) {
			delete m_game_state.back();
			m_game_state.pop_back();
		}
	}
}

void Game_state_manager::render()
{
	if (!m_game_state.empty()) {
		m_game_state.back()->render();
	}
}

void Game_state_manager::update()
{
	if (!m_game_state.empty()) {
		m_game_state.back()->update();
	}
}

