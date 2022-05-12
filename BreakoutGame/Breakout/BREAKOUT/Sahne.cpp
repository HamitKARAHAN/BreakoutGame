#include "Sahne.hpp"

Sahne::Sahne()
{
	m_resimler[0] = "resimler/Walls/brick.png";
	m_resimler[1] = "resimler/Walls/brick_blue.png";
	m_resimler[2] = "resimler/Walls/brick_pink_side.png";
	m_resimler[3] = "resimler/Walls/brick_red.png";
	m_resimler[4] = "resimler/Bricks/brick_blue_small.png";
	m_resimler[5] = "resimler/Bricks/brick_blue_small_cracked.png";
	m_resimler[6] = "resimler/Bricks/brick_green_small.png";
	m_resimler[7] = "resimler/Bricks/brick_green_small_cracked.png";
	m_resimler[8] = "resimler/Bricks/brick_pink_small.png";
	m_resimler[9] = "resimler/Bricks/brick_pink_small_try.png";
	m_resimler[10] = "resimler/Bricks/brick_violet_small.png";
	m_resimler[11] = "resimler/Bricks/brick_violet_small_cracked.png";
	m_resimler[12] = "resimler/Bricks/brick_yellow_small.png";
	m_resimler[13] = "resimler/Bricks/brick_yellow_small_cracked.png";
	for (int i = 0; i < sizeof(m_resimler)/sizeof(m_resimler[0]); i++)
	{
		if (!m_textArkaPlan[i].loadFromFile(m_resimler[i]))
		{
			std::cout << "Kaplama Acilmadi" << std::endl;
		}
	}
}

void Sahne::kaplamaAyarla(bool blokMu, int rasgeleBlokIndeks, bool kirikBloklarmý)
{
	if(!blokMu)
	{
		int duvarIndeks = TemelFonksiyonlar::getRandomNumber(0, 3);
		resDuvarArkaPlan.setTexture(m_textArkaPlan[duvarIndeks]);
		auto duvarResimBoyutu = sf::Vector2f(174, 174);					 //Resim sabit olduðu için ve baþlangýç pikseli (0,0) 
		float sx = duvarBoyutGetir().x / duvarResimBoyutu.x;			 //olmadýðý için boyutunu manuel olarak almak zorunda kaldým
		float sy = duvarBoyutGetir().y / (duvarResimBoyutu.y);
		resDuvarArkaPlan.setTextureRect(sf::IntRect(43, 45, duvarResimBoyutu.x, duvarResimBoyutu.y));
		resDuvarArkaPlan.setScale(sx, sy);
	}
	else
	{	
		if (kirikBloklarmý)
		{
			resBlokArkaPlan.setTexture(m_textArkaPlan[rasgeleBlokIndeks+1]);
			auto blokResimBoyutu = sf::Vector2f(232, 100);
			float sx = blokBoyutGetir().x / blokResimBoyutu.x;
			float sy = blokBoyutGetir().y / (blokResimBoyutu.y);
			resBlokArkaPlan.setTextureRect(sf::IntRect(141, 178, blokResimBoyutu.x, blokResimBoyutu.y));
			resBlokArkaPlan.setScale(sx, sy);
		}
		else
		{
			resBlokArkaPlan.setTexture(m_textArkaPlan[rasgeleBlokIndeks]);
			auto blokResimBoyutu = sf::Vector2f(232, 100);
			float sx = blokBoyutGetir().x / blokResimBoyutu.x;
			float sy = blokBoyutGetir().y / (blokResimBoyutu.y);
			resBlokArkaPlan.setTextureRect(sf::IntRect(141, 178, blokResimBoyutu.x, blokResimBoyutu.y));
			resBlokArkaPlan.setScale(sx, sy);
		}
	}
}

void Sahne::sahneOlustur(int pencereGenislik, int pencereYukseklik)
{
	m_DuvarHucreBoyut = sf::Vector2f((pencereGenislik + pencereYukseklik) / 75, (pencereGenislik + pencereYukseklik) / 75);
	m_duvarSutunSayisi = (pencereGenislik / m_DuvarHucreBoyut.y) - 1;
	m_duvarSatirSayisi = (pencereYukseklik / m_DuvarHucreBoyut.x) - 1;
	for (int satir = 0; satir < m_duvarSatirSayisi; satir++)
	{
		for (int sutun = 0; sutun < m_duvarSutunSayisi; sutun++)
		{
			if (satir == 0 || satir == m_duvarSatirSayisi - 1 || sutun == 0 || sutun == m_duvarSutunSayisi - 1)
			{
				/*m_duvarým.setFillColor(color);
				m_duvarým.setOutlineColor(sf::Color::Black);		//Bu deðerleri atayýp hafýzayý yormaya gerek yok
				m_duvarým.setOutlineThickness(1.0f);*/
				boyut(false, m_DuvarHucreBoyut.x, m_DuvarHucreBoyut.y);
				konum(false, (m_DuvarHucreBoyut.x / 2.0f) + (m_DuvarHucreBoyut.x * static_cast<float>(sutun)),
							 (m_DuvarHucreBoyut.y / 2.0f) + (m_DuvarHucreBoyut.y * static_cast<float>(satir)));
				m_duvarlar.push_back(m_duvarým);
				kaplamaAyarla(false);
				m_resDuvarArkaplan.push_back(resDuvarArkaPlan);
			}
		}
	}
	blokOlustur(pencereGenislik,pencereYukseklik);
}

void Sahne::blokOlustur(int pencereGenislik, int pencereYukseklik)
{
	m_blokHucreBoyut.x = pencereGenislik / 12.8;
	m_blokHucreBoyut.y = pencereYukseklik / 21.6;
	for (int satir = 0; satir < 5; satir++)
	{
		for (int sutun = 0; sutun < 10; sutun++)
		{
			//m_blok.setFillColor(sf::Color::Green);
			//m_blok.setOutlineColor(sf::Color::Black);			//Bu deðerleri atayýp hafýzayý yormaya gerek yok
			//m_blok.setOutlineThickness(1.0f);
			boyut(true,m_blokHucreBoyut.x, m_blokHucreBoyut.y);
			konum(true, (m_blokHucreBoyut.x*4/3) + (m_blokHucreBoyut.x * static_cast<float>(sutun)),
					60.0f + (m_blokHucreBoyut.y) + (m_blokHucreBoyut.y * static_cast<float>(satir)));
			m_normalBloklar.push_back(m_blok);
			m_kirikBloklar.push_back(m_blok);
			int rasgeleBlokIndeks;
			do
			{
				rasgeleBlokIndeks = TemelFonksiyonlar::getRandomNumber(4, 13);
			} while (!(rasgeleBlokIndeks % 2 == 0));
			kaplamaAyarla(true, rasgeleBlokIndeks, true);
			m_resKirikBlokArkaPlan.push_back(resBlokArkaPlan);
			kaplamaAyarla(true, rasgeleBlokIndeks);
			m_resNormalBlokArkaPlan.push_back(resBlokArkaPlan);
		}
	}
}

void Sahne::ciz(sf::RenderWindow& pencere)
{
	//Duvarý çizmeye gerek yok
	//for (sf::RectangleShape duvar: m_duvarlar)
	//{
	//	pencere.draw(duvar);
	//}

	//Duvar Kaplamalarý çiz
	for (sf::Sprite arkaplan : m_resDuvarArkaplan)
	{
		pencere.draw(arkaplan);
	}
	//Normal Bloklarý çizmeye gerek yok
	//for (sf::RectangleShape blok: m_normalBloklar)
	//{
	//	pencere.draw(blok);
	//}
	//Kýrýk Bloklarý çizmeye gerek yok
	//for (sf::RectangleShape blok : m_kirikBloklar)
	//{
	//	pencere.draw(blok);
	//}

	//Kirik Blok Kaplamalarý çiz
	for (sf::Sprite kirikBlok : m_resKirikBlokArkaPlan)
	{
		pencere.draw(kirikBlok);
	}

	//Normal Blok Kaplamalarý çiz
	for (sf::Sprite normalBlok : m_resNormalBlokArkaPlan)
	{
		pencere.draw(normalBlok);
	}
}

void Sahne::konum(bool blokMu, float x, float y)
{
	if (!blokMu)
	{
		m_DuvarHucreKonum.x = x;
		m_DuvarHucreKonum.y = y;
		m_duvarým.setPosition(m_DuvarHucreKonum);
		resDuvarArkaPlan.setPosition(m_DuvarHucreKonum);
	}
	else
	{
		m_blokHucreKonum.x = x;
		m_blokHucreKonum.y = y;
		m_blok.setPosition(m_blokHucreKonum);
		resBlokArkaPlan.setPosition(m_blokHucreKonum);
	}
}

void Sahne::boyut(bool blokMu, float genislik, float yukseklik)
{
	if (!blokMu)
	{
		m_duvarým.setSize(sf::Vector2f(genislik, yukseklik));
	}
	else
	{
		m_blok.setSize(sf::Vector2f(genislik, yukseklik));
	}
}

void Sahne::blokSil(int silinecekblokIndeks, bool kirikBlokMu)
{
	if (!kirikBlokMu)
	{
		m_resNormalBlokArkaPlan.erase(m_resNormalBlokArkaPlan.begin() + silinecekblokIndeks);
		m_normalBloklar.erase(m_normalBloklar.begin() + silinecekblokIndeks);
	}
	else
	{
		m_resKirikBlokArkaPlan.erase(m_resKirikBlokArkaPlan.begin() + silinecekblokIndeks);
		m_kirikBloklar.erase(m_kirikBloklar.begin() + silinecekblokIndeks);
	}
}

sf::Vector2f Sahne::duvarBoyutGetir()
{
	return m_DuvarHucreBoyut;
}

sf::Vector2f Sahne::blokBoyutGetir()
{
	return m_blokHucreBoyut;
}

std::vector<sf::RectangleShape> Sahne::normalBloklariGetir()
{
	return m_normalBloklar;
}

std::vector<sf::RectangleShape> Sahne::kirikBloklariGetir()
{
	return m_kirikBloklar;
}
