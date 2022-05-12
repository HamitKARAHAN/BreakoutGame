#include "CarpismaKontrolu.hpp"

bool CarpismaKontrolu::raketCarpisma(Top& top, const Raket& raket)
{
	float raketXMin = raket.raketGetir().getGlobalBounds().left;
	float raketXMax = raketXMin + raket.raketGetir().getGlobalBounds().width;
	float raketYMin = raket.raketGetir().getGlobalBounds().top;
	float raketYMax = raketYMin + raket.raketGetir().getGlobalBounds().height;

	float topX = top.konumGetir().x;
	float topXMin = top.konumGetir().x + top.topGetir().getRadius() * 2;
	float toportaNoktaX = topX + top.topGetir().getRadius();
	float topY = top.konumGetir().y + top.topGetir().getRadius()*2;

	if ((topXMin >= raketXMin) && (topX <= raketXMax) && (topY >= raketYMin) && (topY <= raketYMax))
	{
		float raketOrtaNoktaX = raket.konumGetir().x + raket.boyutGetir().x/2;
		if (toportaNoktaX < raketOrtaNoktaX)
		{
			top.yatayYonAta(true);
			top.aciDegis(static_cast<double>(((raketOrtaNoktaX - topXMin) / (raketOrtaNoktaX - raketXMin))));
		}
		else if (toportaNoktaX > raketOrtaNoktaX)
		{
			top.yatayYonAta(false);
			top.aciDegis(static_cast<double>(((topX - raketOrtaNoktaX) / (raketXMax - raketOrtaNoktaX))));
		}
		else
			top.aciDegis(0.0);
		return true;
	}
	return false;
}

bool CarpismaKontrolu::blokCarpisma(Top& top, const sf::RectangleShape& blok)
{
	float blokSol = blok.getPosition().x;
	float blokSag = blokSol + blok.getSize().x;
	float blokUst = blok.getPosition().y;
	float blokAlt = blokUst + blok.getSize().y;
	
	sf::Vector2f topSolMerkez(top.konumGetir().x, top.konumGetir().y + top.topGetir().getRadius());
	sf::Vector2f topSagMerkez(top.konumGetir().x + (top.topGetir().getRadius()*2), top.konumGetir().y + top.topGetir().getRadius());
	sf::Vector2f topUstMerkez((top.konumGetir().x + top.topGetir().getRadius()), top.konumGetir().y);
	sf::Vector2f topAltMerkez((top.konumGetir().x + top.topGetir().getRadius()), (top.konumGetir().y) + (top.topGetir().getRadius() * 2));

	if (top.dikeyYonGetir() == true)
	{
		if ((topUstMerkez.x >= blokSol) && (topUstMerkez.x <= blokSag) && (topUstMerkez.y >= blokUst) && (topUstMerkez.y <= blokAlt))
		{
			top.dikeyYonAta(false);
			return true;
		}
	}
	else
	{
		if ((topAltMerkez.x >= blokSol) && (topAltMerkez.x <= blokSag) && (topAltMerkez.y >= blokUst) && (topAltMerkez.y <= blokAlt))
		{
			top.dikeyYonAta(true);
			return true;
		}
	}
	if (top.yatayYonGetir() == true)
	{
		if ((topSolMerkez.x >= blokSol) && (topSolMerkez.x <= blokSag) && (topSolMerkez.y >= blokUst) && (topSolMerkez.y <= blokAlt))
		{
			top.yatayYonAta(false);
			return true;
		}
	}
	else if ((topSagMerkez.x >= blokSol) && (topSagMerkez.x <= blokSag) && (topSagMerkez.y >= blokUst) && (topSagMerkez.y <= blokAlt))
	{
		top.yatayYonAta(true);
		return true;
	}
	return false;
}
