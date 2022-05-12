#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TemelFonksiyonlar.hpp"

class Raket
{
public:
	Raket();
	Raket(int pencereGenislik);
	void boyut(float genislik, float yukseklik, float duvarBoyutX);
	void konum(float x, float y);
	void renk(sf::Color renk);
	void hareket(const float gecenSure, const bool solMu);
	void ciz(sf::RenderWindow& window);
	sf::RectangleShape		raketGetir() const;
	sf::Vector2f			konumGetir() const;
	sf::Vector2f			boyutGetir() const;
private:
	void				kaplamaAyarla();
	sf::RectangleShape	m_sekil;
	float				m_hiz;
	int					m_pencereGenislik;
	float				m_maxX;
	float				m_minX;
	sf::Vector2f		m_boyut;
	sf::Vector2f		m_konum;
	sf::Texture			m_textArkaPlan[5];
	sf::Sprite			m_resArkaPlan;
};
