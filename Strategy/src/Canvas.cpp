#include "../include/UI/Canvas.h"
#include <iostream>
Canvas::Canvas() {
	const float start_btn_pos = 300.0;
	const float interval = 15.0;

	sf::Font font;
	font.loadFromFile("./Assets/fonts/font.TTF");

	melee = new Button(start_btn_pos + interval, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79),
		sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee", font));
}

Canvas::~Canvas() {

}

void Canvas::drawButtons(sf::RenderWindow& window) {
	melee->drawButton(window);
}

void Canvas::Update(sf::RenderWindow& window) {
	melee->Update(window);
}
