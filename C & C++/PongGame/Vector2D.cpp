#include "math.h"
#include "Vector2D.h"
#include <iostream>


	// use r for x, s for y 
	Vector2D& Vector2D:: Set(float r, float s) { 
		x=r;
		s=y; 
	}

	// adds v to *this and returns reference to *this
	Vector2D& Vector2D:: operator +=(const Vector2D& v) { 
			x = x + v.x;
			y = y + v.y;
		return *this; 
	}

	// subtracts v to *this and returns reference to *this
	Vector2D& Vector2D:: operator -=(const Vector2D& v) { 
			x = x - v.x;
			y = y - v.y;
		return *this; 
	}
	
	// multiplies *this with scalar t and returns reference to *this
	Vector2D& Vector2D:: operator *=(float t) { 
			x = x * t ;
			y = y * t;
		return *this; 
	}

	// divides *this with scalar t and returns reference to *this
	Vector2D& Vector2D:: operator /=(float t) { 
			x = x / t ;
	  		y = y / t;
		return *this; 
	}	

	// returns a negated form of *this as a new vector 
	Vector2D Vector2D:: operator -(void) const {
		Vector2D vec1;
			vec1.x = - this -> x;
			vec1.y = - this -> y;
		return vec1;
	}

	// returns sum of *this and v as a new vector
	Vector2D Vector2D:: operator +(const Vector2D& v) const {
		Vector2D vec2;
			vec2.x = this -> x + v.x;
			vec2.y = this -> y + v.y;
		return vec2;
	}

	// returns the difference between *this and v as a new vector
	Vector2D Vector2D:: operator -(const Vector2D& v) const {
		Vector2D vec3;
			vec3.x = this -> x - v.x;
			vec3.y = this -> y - v.y;
		return vec3;
	}

	// returns the multiplication of *this and t as a new vector
	Vector2D Vector2D:: operator *(float t) const { 
		Vector2D vec4;
			vec4.x = this -> x * t;
			vec4.y = this -> y * t;
		return vec4;
	}

	// returns the division of *this and t as a new vector
	Vector2D Vector2D:: operator /(float t) const { 
		Vector2D vec5;
			vec5.x = this -> x / t;
			vec5.y = this -> y / t;
		return vec5;
	}

	// returns true if *this is equal to v
	bool Vector2D:: operator ==(const Vector2D& v) const { 
		if( (this -> x == v.x) && (this -> y == v.y) )
	return true;
	}

	// returns true if *this is not equal to v
	bool Vector2D:: operator !=(const Vector2D& v) const {
			if( (this -> x != v.x)  && (this -> y != v.y) )
		return true;
	}
