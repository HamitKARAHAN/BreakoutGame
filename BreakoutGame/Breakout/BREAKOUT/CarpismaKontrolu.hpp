#pragma once
#include "Raket.hpp"
#include "Top.hpp"

class CarpismaKontrolu
{
public:
	CarpismaKontrolu(){}
	bool raketCarpisma(Top& top, const Raket& raket);
	bool blokCarpisma(Top& top, const sf::RectangleShape& blok);
private:
};
