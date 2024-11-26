#include "checkML.h"

#ifndef VECTOR2D_H
#define VECTOR2D_H

#pragma once
template <class T>

class Vector2D {
private:
	T x;
	T y;

public:
	//constructor
	Vector2D() { x = 0; y = 0; }
	Vector2D(T x, T y) : x(x), y(y) {}

	T X() const {
		return x;
	}
	T Y() const {
		return y;
	}

	//Operaciones
	Vector2D& operator+=(const Vector2D b) {
		x += b.x;
		y += b.y;
		return *this;
	}

	template <class T>
	Vector2D<T>& operator+=(const Vector2D b) {
		x += b.x;
		y += b.y;
		return *this;
	}
	template <class T>
	Vector2D<T> operator+(const Vector2D b)const {
		return Vector2D(x + b.x, y + b.y);
	}
	template <class T>
	Vector2D<T> operator-(const Vector2D b)const {
		return Vector2D(x - b.x, y - b.y);
	}
	template <class T>
	Vector2D<T> operator*(const Vector2D b)const {
		return Vector2D(x * b.x, y * b.y);
	}
	template <class T>
	Vector2D<T> operator*(int n)const {
		return Vector2D(x * n, y * n);
	}
	template <class T>
	int operator*(const Vector2D& b)const {
		return (x * b.x) + (y * b.y);
	}
};

using Point2D = Vector2D<float>;

#endif