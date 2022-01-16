#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

struct TransformComponent : public Component {
public:
	//int xpos, ypos;

	Vector2D position;
	Vector2D velocity;

	int height= 42;
	int width = 20;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}
	TransformComponent(int sc) {
		position.Zero();
		scale = sc;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
		//position.Zero();
	}
	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override {
		velocity.x = 0;
		velocity.y = 0;
		//position.Zero();
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};