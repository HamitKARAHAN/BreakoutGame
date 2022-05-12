#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Raket.hpp"
#include "Sahne.hpp"
#include "Top.hpp"
#include "CarpismaKontrolu.hpp"

class Oyun
{
public:
	Oyun();	
	void oyunuBaslat();
private:
	void bilesenOlustur();
	void olayKontrol();
	void sahneGuncelle();
	void sahneCiz();
	bool bittimi();
	sf::RenderWindow	m_window;
	sf::Clock			m_saat;
	time_t				raketCarpismaZaman;
	sf::String			m_pencereBaslik;
	float				m_gecenSure;
	float				m_pencereGenislik;
	float				m_pencereYukseklik;
	bool				topIlkHareket;
	Sahne				m_sahne;
	Raket				m_raket;
	Top					m_top;
	CarpismaKontrolu	carpismaKontrol;
	std::vector<sf::RectangleShape> normalBloklar;
	std::vector<sf::RectangleShape> kirikBloklar;
};