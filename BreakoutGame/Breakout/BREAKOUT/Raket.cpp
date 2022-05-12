#include "Raket.hpp"

Raket::Raket()
{
	//Programýn uyarý vermememesi için ilk deðer atadýk
	m_hiz = 0;
	m_pencereGenislik = 0;
	m_maxX = 0;
	m_minX = 0;
}

Raket::Raket(int pencereGenislik) :m_pencereGenislik(pencereGenislik)
{
	m_hiz = pencereGenislik / 150;
}

void Raket::hareket(const float gecenSure, const bool solMu)
{
	if (gecenSure > 0.0f)
	{
		if (!solMu)
		{
			m_konum.x += m_hiz;
			konum(m_konum.x, m_konum.y);
		}
		else
		{
			m_konum.x -= m_hiz;
			konum(m_konum.x, m_konum.y);
		}
	}
}

void Raket::ciz(sf::RenderWindow& window)
{
	//window.draw(m_sekil);
	window.draw(m_resArkaPlan);
}

void Raket::kaplamaAyarla()
{
	int batsIndex = TemelFonksiyonlar::getRandomNumber(0, 4);
	if (!m_textArkaPlan[0].loadFromFile("resimler/bats/bat_black.png")) {
		std::cout << "Kaplama Acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[1].loadFromFile("resimler/bats/bat_blue.png")) {
		std::cout << "Kaplama Acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[2].loadFromFile("resimler/bats/bat_orange.png")) {
		std::cout << "Kaplama Acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[3].loadFromFile("resimler/bats/bat_pink.png")) {
		std::cout << "Kaplama Acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[4].loadFromFile("resimler/bats/bat_yellow.png")) {
		std::cout << "Kaplama Acilmadi" << std::endl;
	}
	else
	{
		m_resArkaPlan.setTexture(m_textArkaPlan[batsIndex]);
		auto raketKaplamaBoyut = sf::Vector2f(462, 101);							 //Resim sabit olduðu için ve baþlangýç pikseli (0,0) olmadýðý 
		float sx = m_sekil.getSize().x / raketKaplamaBoyut.x;						 //için boyutunu manuel olarak almak zorunda kaldým
		float sy = m_sekil.getSize().y / (raketKaplamaBoyut.y);
		m_resArkaPlan.setTextureRect(sf::IntRect(25, 179, raketKaplamaBoyut.x, raketKaplamaBoyut.y));
		m_resArkaPlan.setScale(sx, sy);
	}
}

void Raket::boyut(float genislik, float yukseklik, float duvarBoyutX)
{
	m_boyut = sf::Vector2f(genislik, yukseklik);
	m_sekil.setSize(m_boyut);
	m_minX = duvarBoyutX *3/2;
	m_maxX = m_pencereGenislik - (duvarBoyutX * 3 / 2) - m_sekil.getGlobalBounds().width;
	kaplamaAyarla();
}

void Raket::konum(float x, float y)
{
	m_konum = sf::Vector2f(x, y);
	if (m_konum.x <= m_minX)
	{
		m_konum.x = m_minX;
	}
	else if (m_konum.x >= m_maxX)
	{
		m_konum.x = m_maxX;

	}
	m_sekil.setPosition(m_konum);
	m_resArkaPlan.setPosition(m_konum);
}

sf::RectangleShape Raket::raketGetir() const
{
	return m_sekil;
}

sf::Vector2f Raket::boyutGetir() const
{
	return m_boyut;
}

void Raket::renk(sf::Color renk)
{
	m_sekil.setFillColor(renk);
}

sf::Vector2f Raket::konumGetir() const
{
	return m_konum;
}