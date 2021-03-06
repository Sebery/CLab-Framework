#include "Ball.h"
#include "Padding.h"

SDL_Rect Ball::GetCenter() const {
	return { pos.x + radius, pos.y + radius };
}

void Ball::Init(int radius, int speed, const SDL_Color& color) {
	soundChannel = 2;
	sound = clf::Asset::LoadSound("assets/sfx/pongSound.ogg");
	this->radius = radius;
	this->color = color;
	this->speed = speed;
	diameter = radius * 2;
	dir = { 0, 0, 0, 0 };
	startPos = pos = { (clf::Engine::HalfScreenWidth() - radius), (clf::Engine::HalfScreenHeight() - radius) };
	
	//Evaluate (minX, minY, maxX, maxY)
	minMaxPos = { Padding::GetSize(), Padding::GetSize(), clf::Engine::ScreenWidth() - Padding::GetSize(), clf::Engine::ScreenHeight() - Padding::GetSize() };
}

void Ball::Draw() {
	clf::Render::DrawFillCircle(pos, radius, color);
}

void Ball::Move(float deltaTime, const SDL_Rect& p1, const SDL_Rect& p2) {
	pos.x += static_cast<int>(speed * deltaTime * dir.x);
	pos.y += static_cast<int>(speed * deltaTime * dir.y);

	//Check if the ball is out of bounds
	if (pos.y + diameter >= minMaxPos.h) {
		dir.y *= -1;
		pos.y = minMaxPos.h - diameter;
	}

	if (pos.y <= minMaxPos.y) {
		dir.y *= -1;
		pos.y = minMaxPos.y;
	}

	//Check Collision With Players
	if (IsColliding(p1)) {
		clf::Sound::PlayChannel(soundChannel, sound, 1);
		dir.x *= -1;
		pos.x = p1.x + p1.w;
	}

	if (IsColliding(p2)) {
		clf::Sound::PlayChannel(soundChannel, sound, 1);
		dir.x *= -1;
		pos.x = p2.x - diameter;
	}

}

bool Ball::Reset() {
	if (pos.x + diameter >= minMaxPos.w || pos.x + diameter <= minMaxPos.x) {
		dir.x = 0;
		dir.y = 0;
		pos.x = startPos.x;
		pos.y = startPos.y;
		
		return true;
	}

	return false;
}

bool Ball::IsColliding(const SDL_Rect& rect) const {
	return (
		rect.x + rect.w >= pos.x &&
		pos.x + diameter >= rect.x &&
		rect.y + rect.h >= pos.y &&
		pos.y + diameter >= rect.y);
}

void Ball::SetDir(int x, int y) {
	dir.x = x;
	dir.y = y;
}

void Ball::Finish() {
	clf::Asset::FreeSound(sound);
}

