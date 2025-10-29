#pragma once

#include <SFML/Graphics.hpp>

sf::View view;//Обновили sfml объект "вид", который и является камерой. 
//---------------------------------------------------------------------------------------------
sf::View getPlayerCordinateForview(float x, float y)
{
	float tempX = x;
	float tempY = y;

	if (x < 320) tempX = 320;
	if (y < 240) tempY = 240;
	if (y > 554) tempY = 554;

	view.setCenter({ tempX, tempY });  // Следим за икроком, передовая его кординаты.
	return view; // Возвращаем нашу камеру что обновляет её.
}
//---------------------------------------------------------------------------------------------
sf::View viewmap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		view.move({0.1f * time, 0.f});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		view.move({0.f, 0.1f * time});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		view.move({-0.1f * time, 0.f});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		view.move({0.f, -0.1f * time});

	return view;
}
//---------------------------------------------------------------------------------------------
sf::View changeview()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		view.zoom(1.0100f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		view.rotate(sf::degrees(1.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		view.setSize({640, 480});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		view.setSize({540, 380});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		view.setViewport(sf::FloatRect({0, 0}, {0.5f, 1}));

	return view;
}
//---------------------------------------------------------------------------------------------