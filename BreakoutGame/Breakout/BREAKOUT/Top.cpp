#include "Top.hpp"
#define PI 3.14159265

void Top::rasgeleYon()
{
	m_solaMi = TemelFonksiyonlar::getRandomNumber(0, 1) != 0;
}

Top::Top()
{
	m_hiz = 0.0f;
	m_minAci = 30.0;
	maxMinFark = 45.0;
}

Top::Top(const float hiz, const double minAci, const double maxAci) :  m_hiz(hiz), m_minAci(minAci), m_maxAci(maxAci)
{
	rasgeleYon();
	if (m_hiz < 0.0f)
		m_hiz = 0.0f;
	if (m_minAci < 30.0)
		m_minAci = 30.0;
	else if (m_minAci > 75.0)
		m_minAci = 75.0;
	if (m_maxAci < 30.0)
		m_maxAci = 30.0;
	else if (m_maxAci > 75.0)
		m_maxAci = 75.0;
	if (m_minAci > m_minAci)
	{
		double temp = m_minAci;
		m_minAci = m_maxAci;
		m_maxAci = m_minAci;
	}
	maxMinFark = m_maxAci - m_minAci;
	m_aciDegisimOran� = 0;
}

void Top::aciDegis(const double aciDegisimOran�)
{
	if ((aciDegisimOran� >= 0.0) && (aciDegisimOran� <= 1.0))
	{
		m_aciDegisimOran� = aciDegisimOran�;
	}
}

void Top::hareket(const float gecenSure, const bool ilkHareketMi, sf::Vector2f raketKonum, sf::Vector2f raketBoyut)
{
	if (gecenSure > 0)
	{	//�lk hareketse top raketle beraber hareket etsin
		if (ilkHareketMi==true)
		{
			konum((raketKonum.x) + (raketBoyut.x / 2) - (m_top.getRadius()), raketKonum.y - (2 * m_top.getRadius()));
		}
		else
		{
			float xYon = (m_solaMi ? -1.0f : 1.0f);
			float yYon = (m_yukariMi ? -1.0f : 1.0f);
			float cosX = static_cast<float>(cos(((m_aciDegisimOran� * maxMinFark) + m_minAci) * PI / 180.0));
			float sinY = static_cast<float>(sin(((m_aciDegisimOran� * maxMinFark) + m_minAci) * PI / 180.0));
			float x = xYon * m_hiz * cosX / 50;
			float y = yYon * m_hiz * sinY / 50;
			konum(konumGetir().x + x, konumGetir().y + y);
		}
	}
}

void Top::kaplamaAyarla()
{
	int ballsIndex = TemelFonksiyonlar::getRandomNumber(0, 5);
	if (!m_textArkaPlan[0].loadFromFile("resimler/Balls/ball_blue.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[1].loadFromFile("resimler/Balls/ball_green.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[2].loadFromFile("resimler/Balls/ball_orange.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[3].loadFromFile("resimler/Balls/ball_red.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[4].loadFromFile("resimler/Balls/ball_silver.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	if (!m_textArkaPlan[5].loadFromFile("resimler/Balls/ball_yellow.png")) {
		std::cout << "kaplama acilmadi" << std::endl;
	}
	else {
		m_resArkaPlan.setTexture(m_textArkaPlan[ballsIndex]);
		auto topKaplamaBoyut = sf::Vector2f(367, 367);										 //Resim sabit oldu�u i�in ve ba�lang�� pikseli (0,0) olmad��� 
		float sXY = m_top.getRadius() * 2 / (topKaplamaBoyut.y);							 //i�in boyutunu manuel olarak almak zorunda kald�m
		m_resArkaPlan.setTextureRect(sf::IntRect(72, 74, topKaplamaBoyut.x, topKaplamaBoyut.y));
		m_resArkaPlan.setScale(sXY, sXY);
	}
}

void Top::ciz(sf::RenderWindow& window)
{
	//window.draw(m_top);
	window.draw(m_resArkaPlan);
}

void Top::renk(sf::Color renk)
{
	m_top.setFillColor(renk);
}

void Top::konum(float x, float y)
{
	m_konum.x = x;
	m_konum.y = y;
	m_top.setPosition(m_konum);
	m_resArkaPlan.setPosition(m_konum);
}

void Top::boyut(float yaricap)
{
	m_yaricap = yaricap;
	m_top.setRadius(yaricap);
	kaplamaAyarla();
}

sf::CircleShape Top::topGetir() const
{
	return m_top;
}

void Top::dikeyYonAta(const bool yukariMi)
{
	m_yukariMi = yukariMi;
}

void Top::yatayYonAta(const bool solaMi)
{
	m_solaMi = solaMi;
}

void Top::dikeyYonTersle()
{
	m_yukariMi = !m_yukariMi;
}

bool Top::dikeyYonGetir()
{
	return m_yukariMi;
}

sf::Vector2f Top::konumGetir() const
{
	return m_konum;
}

bool Top::yatayYonGetir()
{
	return m_solaMi;
}