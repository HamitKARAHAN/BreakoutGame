#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include "TemelFonksiyonlar.hpp"

class Sahne
{
public:
	Sahne();
	void sahneOlustur(int pencereGenislik, int pencereYukseklik);
	void konum(bool blokMu, float x, float y);
	void boyut(bool blokMu, float genislik, float yukseklik);
	void ciz(sf::RenderWindow& pencere);
	void blokSil(int silinecekblokIndeks, bool kirikBlokMu);
	sf::Vector2f					duvarBoyutGetir();
	sf::Vector2f					blokBoyutGetir();
	std::vector<sf::RectangleShape> normalBloklariGetir();
	std::vector<sf::RectangleShape> kirikBloklariGetir();
private:
	void blokOlustur(int pencereGenislik, int pencereYukseklik);
	void kaplamaAyarla(bool blokMu, int rasgeleBlokIndeks=0, bool kirikBloklarMi=false);
	sf::RectangleShape			   m_duvarým,  m_blok;
	std::vector<sf::RectangleShape>m_duvarlar, m_normalBloklar, m_kirikBloklar;
	sf::Sprite					   resDuvarArkaPlan,   resBlokArkaPlan;
	std::vector<sf::Sprite>		   m_resDuvarArkaplan, m_resNormalBlokArkaPlan, m_resKirikBlokArkaPlan;
	sf::Vector2f				   m_DuvarHucreBoyut, m_blokHucreBoyut;
	sf::Vector2f				   m_DuvarHucreKonum, m_blokHucreKonum;
	sf::Texture					   m_textArkaPlan[14];
	std::string					   m_resimler[14];
	int							   m_duvarSatirSayisi;
	int							   m_duvarSutunSayisi;
};