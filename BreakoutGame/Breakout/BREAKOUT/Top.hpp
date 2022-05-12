#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include "TemelFonksiyonlar.hpp"
class Top
{
public:
	Top();
	Top(const float hiz, 
		const double minAci = 30.0, 
		const double maxAci = 75.0);
	void renk(sf::Color renk);
	void konum(float x, float y);
	void boyut(float yaricap);
	void hareket(const float gecenSure, 
				const bool ilkHareketMi = false, 
				sf::Vector2f raketKonum = sf::Vector2f(0, 0), 
				sf::Vector2f raketBoyut = sf::Vector2f(0, 0));
	void ciz(sf::RenderWindow& window);
	void aciDegis(const double aciDegisimOraný);
	void dikeyYonAta(const bool yukariMi);
	void yatayYonAta(const bool solaMi);
	void dikeyYonTersle();
	bool yatayYonGetir();
	bool dikeyYonGetir();
	sf::CircleShape			topGetir() const;
	sf::Vector2f			konumGetir() const;
private:
	void rasgeleYon();
	void kaplamaAyarla();
	sf::CircleShape		m_top;
	float				m_hiz;
	float				m_yaricap;
	double				m_minAci;
	double				m_maxAci;
	double				maxMinFark;
	double				m_aciDegisimOraný;
	bool				m_yukariMi = true;
	bool				m_solaMi;
	sf::Vector2f		m_konum;
	sf::Texture			m_textArkaPlan[6];
	sf::Sprite			m_resArkaPlan;
};
