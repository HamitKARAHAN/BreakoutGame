#include "Oyun.hpp"

Oyun::Oyun()
{
	m_pencereBaslik = "BreakOut";
	/*1. Çözünürlük : Default olarak tam ekran*/
	m_window.create(sf::VideoMode::getDesktopMode(), m_pencereBaslik, sf::Style::Fullscreen);
	
	/*2. Çözünürlük : ekran boyutunu kendimiz seçmek istersek yorum satýrýný açmamýz yeterli*/
	//m_window.create(sf::VideoMode(960,540), m_pencereBaslik);

	/*3. Çözünürlük : ekran boyutunu kendimiz seçmek istersek yorum satýrýný açmamýz yeterli*/
	//m_window.create(sf::VideoMode(900, 975), m_pencereBaslik);

	m_pencereGenislik = m_window.getSize().x;
	m_pencereYukseklik = m_window.getSize().y;
	m_window.setFramerateLimit(60);
	bilesenOlustur();
}

void Oyun::bilesenOlustur()
{
	//SAHNE OLUÞTUR (Duvar ve Blok)
	m_sahne.sahneOlustur(m_pencereGenislik, m_pencereYukseklik);

	//RAKET OLUÞTUR
	m_raket = Raket(m_pencereGenislik);
	m_raket.renk(sf::Color::Black);
	m_raket.boyut(((m_pencereGenislik + m_pencereYukseklik) / 25), ((m_pencereYukseklik) / 54), (m_sahne.duvarBoyutGetir().x));
	m_raket.konum((m_pencereGenislik / 2.0f) - (m_raket.boyutGetir().x / 2), (m_pencereYukseklik)-(5 * m_raket.boyutGetir().y));
	raketCarpismaZaman = time(0) - 1.0;

	//TOP OLUÞTUR
	m_top = Top((m_pencereGenislik + m_pencereYukseklik) / 5);
	m_top.renk(sf::Color::Blue);
	m_top.boyut((m_pencereGenislik + m_pencereYukseklik) / 200);
	m_top.konum((m_raket.konumGetir().x) + (m_raket.boyutGetir().x / 2) - (m_top.topGetir().getRadius()), (m_raket.konumGetir().y) - (2 * m_top.topGetir().getRadius()));
	topIlkHareket = true;
}

void Oyun::oyunuBaslat()
{
	
	while (!bittimi())
	{
		olayKontrol();
		sahneGuncelle();
		sahneCiz();
	}
}

bool Oyun::bittimi()
{
	return !m_window.isOpen();
}

void Oyun::olayKontrol()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_window.close();
	}
}

void Oyun::sahneGuncelle()
{
	m_gecenSure = m_saat.restart().asSeconds();
	
	/*Raket - Top Hareket*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (topIlkHareket)
		{
			m_raket.hareket(m_gecenSure, false);
			m_top.hareket(m_gecenSure, topIlkHareket, m_raket.konumGetir(), m_raket.boyutGetir());
		}
		else
			m_raket.hareket(m_gecenSure, false);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{		
		if (topIlkHareket)
		{
			m_raket.hareket(m_gecenSure, true);
			m_top.hareket(m_gecenSure, topIlkHareket, m_raket.konumGetir(), m_raket.boyutGetir());
		}
		else
			m_raket.hareket(m_gecenSure, true);
	}
	if (topIlkHareket)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			topIlkHareket = false;
			m_top.hareket(m_gecenSure);
		}
	}
	else
	{
 		m_top.hareket(m_gecenSure);
	}
	
	/*Top ve Duvarlar Çarpýþma Kontrolü*/
	//Top duvarýn içine geçiyor gibi görünmemesi için yarýçapýn yarýsý kadar bir koruma payý býraktým
	if ((m_top.konumGetir().x - m_top.topGetir().getRadius()/2) < (m_sahne.duvarBoyutGetir().x) * 3 / 2)
	{
		m_top.yatayYonAta(false);
	}
	else if ((m_top.konumGetir().x + m_top.topGetir().getRadius() * 5 / 2) > (m_pencereGenislik)-((m_sahne.duvarBoyutGetir().x) * 3 / 2))
	{
		m_top.yatayYonAta(true);
	}
	else if ((m_top.konumGetir().y - m_top.topGetir().getRadius() / 2) < (m_sahne.duvarBoyutGetir().y) * 3 / 2)
	{
		m_top.dikeyYonAta(false);
	}
	else if ((m_top.konumGetir().y + m_top.topGetir().getRadius() * 2) > (m_pencereYukseklik) - ((m_sahne.duvarBoyutGetir().y) * 1 / 2))
	{
		m_window.close();			//Top sahnenin alt sýnýrýný geçtiyse oyunu bitir
	}

	/*Top Raket Çarpýþma Kontrolü*/
	//Raketle topun çarpýþma anýndaki beklenmedik hareketleri önlemek için zaman kullandým
	if (difftime(time(0), raketCarpismaZaman))
	{	//Top ilk defa hareket ediyorsa boþluk tuþuna basmadan çarpýþma kontrolü yapma
		if (!topIlkHareket)
		{
			if (carpismaKontrol.raketCarpisma(m_top, m_raket))
			{
				m_top.dikeyYonTersle();
				raketCarpismaZaman = time(0);
			}
		}
	}

	/*Blok Çarpýþma Kontrolü*/
	normalBloklar = m_sahne.normalBloklariGetir();
	kirikBloklar = m_sahne.kirikBloklariGetir();	
	//Top henüz fýrlatýlmamýþsa boþu boþuna çarpýþma kontrolü yapma
	if (!topIlkHareket)
	{	//Top henüz bloklarýn olduðu bölgeye gelmemiþse boþu boþuna çarpýþma kontrolü yapma
		if (m_top.konumGetir().y < m_sahne.blokBoyutGetir().y * 8)
		{
			//Normal Blok çarpýþma kontrolü
			if (normalBloklar.size() > 0)
			{
				for (int i = 0; i < static_cast<int>(normalBloklar.size()); ++i)
				{
					if (carpismaKontrol.blokCarpisma(m_top, normalBloklar[i]))
					{
						m_sahne.blokSil(i, false);		//Çarpýþma Durumunda Bloðu Sil
						return;
					}
				}
			}
			//Kýrýk Blok Çarpýþma kontrolü
			if (kirikBloklar.size() > 0)
			{
				for (int i = 0; i < static_cast<int>(kirikBloklar.size()); ++i)
				{
					if (carpismaKontrol.blokCarpisma(m_top, kirikBloklar[i]))
					{
						m_sahne.blokSil(i, true);		//Çarpýþma Durumunda Bloðu Sil
						break;
					}
				}
			}
			else
				m_window.close();		//Kýrýlacak Blok kalmamýþsa oyunu bitir.
		}
	}
}

void Oyun::sahneCiz()
{
	m_window.clear(sf::Color(89, 89, 89));
	m_raket.ciz(m_window);
	m_sahne.ciz(m_window);
	m_top.ciz(m_window);
	m_window.display();
}