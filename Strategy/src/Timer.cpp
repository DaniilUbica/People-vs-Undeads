#include "../include/UI/Timer.h"

Timer::Timer(float time, float coordX, float coordY, float width, float height) {
	max_time = time;
	this->width = width;
	this->height = height;

	//sprite.setTexture(texture);
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(255, 255, 255, 127));

	frame_size = height / time;

	sprite.setPosition(coordX, coordY);
	rect.setPosition(coordX, coordY + height);
}

void Timer::Update(float time) {
	if (time < max_time) {
		rect.setSize(sf::Vector2f(width, -height + frame_size * time));
		if (rect.getSize().y <= 0) {
			is_end = true;
		}
		else {
			is_end = false;
		}
	}
}

bool Timer::getEnd() {
	return is_end;
}

sf::RectangleShape Timer::getRect() {
	return rect;
}

sf::Sprite Timer::getSprite() {
	return sprite;
}
