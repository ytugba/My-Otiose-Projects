#include "Vector2D.h"
#include "Ball.h"
#include <iostream>

using namespace std;

	// sets position
	void Ball:: setPosition(const Vector2D& pos) { 
		position = pos; 
	}

	// sets normalized direction
	void Ball:: setDirection(Vector2D& dir) { 
		direction = dir; 
	}

	// sets velocity
	void Ball:: setVelocity(float vel) {
		velocity = vel; 
	}
	
	// sets radious 
	void Ball:: setRadious(float rad) { 
		radius = rad; 
	}
	
	// sets color components: R for color_r, G for color_g, B for color_b
	void Ball:: setColor(float R, float G, float B) { 
		color_r = R; 
		color_g = G;
		color_b = B; 
	}

	// returns position
	Vector2D Ball:: getPosition() { 
		return position;
	}
	
	// returns direction
	Vector2D Ball:: getDirection() {
		return direction;
	}

	// returns velocity
	float Ball:: getVelocity() {
		return velocity;
	}

	// returns radius
	float  Ball:: getRadious()
		{return radius;}

	// returns R,G,B color components of the ball
	float Ball:: getRed() {
		return color_r;
	}

	float Ball:: getGreen() {
		return color_g;
	}	

	float Ball:: getBlue() {
		return color_b;
	}

	// updates and returns the position of the ball using the formula:
	// pos = pos + velocity*normalized_direction;

	Vector2D Ball:: updatePosition() { 
			position = position + velocity * direction;
		return position;
	}