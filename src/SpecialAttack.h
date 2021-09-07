#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Classe abstraite permettant d'impl�menter les diff�rentes attaques sp�ciales (touche Tab)
/// du h�ro en utilisant le design pattern Strat�gie
/// </summary>
class SpecialAttack
{
public:
	virtual void action(float x, float y, int dir) { return; };
	sf::Clock get_Timer() { return buff_timer; };
	float get_buff_duration() { return buff_duration; };

protected:
	sf::Clock buff_timer;
	int buff_duration;
};