#include "Vector2D.h"
#include "Ball.h"
#include "Racket.h"
#include <iostream>

using namespace std;

	//sets size
	void Racket:: setSize(unsigned int s) { 
		size = s; 
	}

	//sets position
	void Racket:: setPosition (const Vector2D& pos) { 
		position = pos; 
	}

	//returns size
	unsigned int Racket:: getSize() { 
		return size; 
	}

	//returns position
	Vector2D Racket:: getPosition() {
		return position; 
	}
