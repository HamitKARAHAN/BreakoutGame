#include "Oyun.hpp"

Oyun::Oyun()
{
	m_pencereBaslik = "BreakOut";
	/*1. ��z�n�rl�k : Default olarak tam ekran*/
	m_window.create(sf::VideoMode::getDesktopMode(), m_pencereBaslik, sf::Style::Fullscreen);
	
	/*2. ��z�n�rl�k : ekran boyutunu kendimiz se�mek istersek yorum sat�r�n� a�mam�z yeterli*/
	//m_window.create(sf::VideoMode(960,540), m_pencereBaslik);

	/*3. ��z�n�rl�k : ekran boyutunu kendimiz se�mek istersek yorum sat�r�n� a�mam�z yeterli*/
	//m_window.create(sf::VideoMode(900, 975), m_pencereBaslik);

	m_pencereGenislik = m_window.getSize().x;
	m_pencereYukseklik = m_window.getSize().y;
	m_window.setFramerateLimit(60);
	bilesenOlustur();
}

void Oyun::bilesenOlustur()
{
	//SAHNE OLU�TUR (Duvar ve Blok)
	m_sahne.sahneOlustur(m_pencereGenislik, m_pencereYukseklik);

	//RAKET OLU�TUR
	m_raket = Raket(m_pencereGenislik);
	m_raket.renk(sf::Color::Black);
	m_raket.boyut(((m_pencereGenislik + m_pencereYukseklik) / 25), ((m_pencereYukseklik) / 54), (m_sahne.duvarBoyutGetir().x));
	m_raket.konum((m_pencereGenislik / 2.0f) - (m_raket.boyutGetir().x / 2), (m_pencereYukseklik)-(5 * m_raket.boyutGetir().y));
	raketCarpismaZaman = time(0) - 1.0;

	//TOP OLU�TUR
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
	
	/*Top ve Duvarlar �arp��ma Kontrol�*/
	//Top duvar�n i�ine ge�iyor gibi g�r�nmemesi i�in yar��ap�n yar�s� kadar bir koruma pay� b�rakt�m
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
		m_window.close();			//Top sahnenin alt s�n�r�n� ge�tiyse oyunu bitir
	}

	/*Top Raket �arp��ma Kontrol�*/
	//Raketle topun �arp��ma an�ndaki beklenmedik hareketleri �nlemek i�in zaman kulland�m
	if (difftime(time(0), raketCarpismaZaman))
	{	//Top ilk defa hareket ediyorsa bo�luk tu�una basmadan �arp��ma kontrol� yapma
		if (!topIlkHareket)
		{
			if (carpismaKontrol.raketCarpisma(m_top, m_raket))
			{
				m_top.dikeyYonTersle();
				raketCarpismaZaman = time(0);
			}
		}
	}

	/*Blok �arp��ma Kontrol�*/
	normalBloklar = m_sahne.normalBloklariGetir();
	kirikBloklar = m_sahne.kirikBloklariGetir();	
	//Top hen�z f�rlat�lmam��sa bo�u bo�una �arp��ma kontrol� yapma
	if (!topIlkHareket)
	{	//Top hen�z bloklar�n oldu�u b�lgeye gelmemi�se bo�u bo�una �arp��ma kontrol� yapma
		if (m_top.konumGetir().y < m_sahne.blokBoyutGetir().y * 8)
		{
			//Normal Blok �arp��ma kontrol�
			if (normalBloklar.size() > 0)
			{
				for (int i = 0; i < static_cast<int>(normalBloklar.size()); ++i)
				{
					if (carpismaKontrol.blokCarpisma(m_top, normalBloklar[i]))
					{
						m_sahne.blokSil(i, false);		//�arp��ma Durumunda Blo�u Sil
						return;
					}
				}
			}
			//K�r�k Blok �arp��ma kontrol�
			if (kirikBloklar.size() > 0)
			{
				for (int i = 0; i < static_cast<int>(kirikBloklar.size()); ++i)
				{
					if (carpismaKontrol.blokCarpisma(m_top, kirikBloklar[i]))
					{
						m_sahne.blokSil(i, true);		//�arp��ma Durumunda Blo�u Sil
						break;
					}
				}
			}
			else
				m_window.close();		//K�r�lacak Blok kalmam��sa oyunu bitir.
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