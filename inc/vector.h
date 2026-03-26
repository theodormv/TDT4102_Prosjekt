

#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>
#include <type_traits>
#include <array>
#include "AnimationWindow.h"

#ifndef USE
#define USE


#define PI 3.14159265359
//#define ASSERT(x) if(!(x)) __debugbreak();

/*
static float q_sqrt(float number) {
		int i;
		float x2, y;
		constexpr float threehalfs = 1.5;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y;                       // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);               // what the fuck? 
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

		return y;
}

*/


template<std::size_t nDims, typename T = double>
class VectorNd {
	std::array<T, nDims> elements;
public:
	VectorNd() {
		static_assert(nDims != 0, "Cant use 0 dimentional VectorNd");
		T* iter = elements.begin();
		do {
			*iter = 0;
		} while (++iter < elements.end());
	}
	
	VectorNd(const VectorNd<nDims, T>& other) {
		for (int i = 0; i < nDims; ++i) {
			elements[i] = other.get(i);
		}
	}

	template<typename U>
	VectorNd(const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; ++i) {
			elements.get(i) = static_cast<U>(other.get(i));
		}

	}

	template<typename ... Targs>
	VectorNd(T dim0, Targs ... Dims) {
		//std::cout << nDims << std::endl;
		//static_assert(nDims != 0);
		elements[0] = dim0;
		set(1, Dims...);
	}

	void set(size_t index, T val) {
		elements[index] = val;
	}
	
	T get(int index) const {
		return elements[index];
	}

	T& operator[](int index) { return elements[index]; }

	T norm() const  {
		T magn = 0;
		for (auto it = elements.begin(); it < elements.end(); it++) magn += (*it) * (*it);
		return sqrt(magn);
	}

	T squareNorm() const {
		T magn = 0;
		for (auto it = elements.begin(); it < elements.end(); it++) magn += (*it) * (*it);
		return magn;
	}
	
	VectorNd<nDims, T>& normalize() {
		T magnitude = norm();
		if(magnitude != 0) for (auto it = elements.begin(); it < elements.end(); it++) (*it) /= magnitude;
		return *this;
	}

	VectorNd<nDims, T> getNormalized() const{
		VectorNd<nDims, T> n = *this;
		T magnitude = norm();
		if (magnitude != 0) for (int i = 0; i < nDims; i++) n[i] /= magnitude;
		return n;
	}
	
    /*
	VectorNd<nDims, T>& qNorm() {
		double inverseMagnitude = q_sqrt(norm());
		std::cout << inverseMagnitude << std::endl;
		for (int i = 0; i < nDims; i++) elements.get(i) *= inverseMagnitude;
		for (int i = 0; i < nDims; i++) std::cout << elements.get(i) << std::endl;
		return *this;
	}
    */

	template<std::size_t dimN, typename V, typename U>
	friend auto dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, U>& vec2) -> decltype(vec1.get(0) * vec2.get(0));
	
    template<typename V, typename U>
	friend VectorNd<3, decltype((V)1 * (U)1)> cross(const VectorNd<3, V>& a, const VectorNd<3, U>& b);

	template<std::size_t dimN, typename U>
	friend U abs(const VectorNd<dimN, U>& vec);

	template<std::size_t dimN, typename U>
	friend std::ostream& operator<< (std::ostream& console, const VectorNd<dimN, U>& vec);

	template<typename U>
	VectorNd<nDims, T>& operator = (const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; i++) elements.get(i) = other.get(i);
		return *this;
	}

	VectorNd<nDims, T>& operator = (const VectorNd<nDims, T>& other) {
		std::memcpy(elements.begin(), other.elements.begin(), nDims*sizeof(T));
		return *this;
	}

	template<typename U>
	VectorNd<nDims, decltype((T)1 + (U)1)> operator + (const VectorNd<nDims, U>& other) const {
		VectorNd < nDims, decltype((T)1 + (U)1)> result;
		for (int i = 0; i < nDims; i++) result[i] = elements[i] + other.get(i);
		return result;
	}
	
	template<typename U>
	VectorNd<nDims, decltype((T)1 - (U)1)> operator - (const VectorNd<nDims, U>& other) const  {
		VectorNd < nDims, decltype((T)1 + (U)1)> result;
		for (int i = 0; i < nDims; i++) result[i] = elements[i] - other.get(i);
		return result;
	}

	VectorNd<nDims, T> operator -() const {
		VectorNd<nDims, T> result;
		for (int i = 0; i < nDims; i++) result[i] = -elements[i];
		return result;
	}

	template<typename U>
	VectorNd<nDims, T>& operator += (const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; i++) elements[i] += other.get(i);
		return *this;
	}

	template<typename U>
	VectorNd<nDims, T>& operator -= (const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; i++) elements[i] -= other.get(i);
		return *this;
	}

	template<typename U>
	VectorNd<nDims, decltype((T)1 * (U)1)> operator * (U num) const {
		VectorNd<nDims, decltype((T)1 + (U)1)> product;
		for (int i = 0; i < nDims; i++) {
			product[i] = elements[i] * num;
		}
		return product;
	}

	template<size_t mDims, typename V, typename U>
	friend VectorNd<mDims, decltype((V)1 * (U)1)> operator * (VectorNd<mDims, V> vec, U num);

	template<typename U>
	VectorNd<nDims, decltype((T)1 / (U)1)> operator / (U num) const {
		VectorNd<nDims, decltype((T)1 + (U)1)> product;
		for (int i = 0; i < nDims; i++) {
			product[i] = elements[i] / num;
		}
		return product;
	}

	template<typename U>
	VectorNd<nDims, T>& operator *= (U num) {
		for (auto it = elements.begin(); it < elements.end(); it++) (*it) *= num;
		return *this;
	}

	template<typename U>
	VectorNd<nDims, T>& operator /= (U num) {
		for (auto it = elements.begin(); it < elements.end(); it++) (*it) /= num;
		return *this;
	}


    TDT4102::Point toPoint2d() const{
        return {this->get(0), this->get(1)};
    }

	bool operator == (const VectorNd<nDims, T>& other) {
		bool same = true;
		for (int i = 0; i < nDims; i++) {
			same = same && (elements.get(i) == other.elements.get(i));
		}
		return same;
	}


	/*
	template<typename U>
	VectorNd<nDims, decltype((T)1 + (U)1)> operator () (U val) {
		static_assert(!std::is_pointer<T>::value, "[error] invoking function on non function poiter based VectorNd");

		using retType = decltype((T)1 + (U)1);
		VectorNd<nDims, retType> invocedVector;
		for (int i = 0; i < nDims; i++) invocedVector[i] = elements.get(i)(val);
		return invocedVector;
	}*/

private:
	template<typename... Targs> 
	void set(size_t index, T value, Targs... Margs) { //recursive set function
		assert(!(index >= nDims));
		elements[index] = value;

		set(index + 1, Margs...);
	}

};

	template<size_t mDims, typename V, typename U>
	VectorNd<mDims, decltype((V)1 * (U)1)> operator * (VectorNd<mDims, V> vec, U num){
		VectorNd<mDims, decltype((V)1 + (U)1)> product;
		for (int i = 0; i < mDims; i++) {
			product[i] =vec.elements[i] * num;
		}
		return product;
	}

template<std::size_t dimN, typename U>
std::ostream& operator<< (std::ostream& console, const VectorNd<dimN, U>& vec){
	console << '[';
	for (int i = 0; i < dimN-1; i++) console << vec.get(i) << ", ";
	console << vec.get(dimN - 1);
	console << ']';
	return console;
}

template<std::size_t dimN, typename V, typename U>
auto dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, U>& vec2) -> decltype((V)1 * (U)1) {
	
	auto product = vec1[0]*vec2[0];
	for(int i = 1; i < dimN; i++){
		product += vec1.get(i) * vec2.get(i);
	}
	return product;
}

template<std::size_t dimN, typename V>
V dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, V>& vec2) {

	V product = vec1.get(0) * vec2.get(0);
	for (int i = 1; i < dimN; i++) {
		product += vec1.get(i) * vec2.get(i);
	}

	return product;
}


template<std::size_t dimN, typename U>
U abs(const VectorNd<dimN, U>& vec) {
	return vec.norm();
}

template<typename V, typename U>
VectorNd<3, decltype((V)1 * (U)1)> cross(const VectorNd<3, V>& a, const VectorNd<3, U>& b) {
	VectorNd<3, decltype((V)1 * (U)1)> product;
	product[0] = a.get(1) * b.get(2) - a.get(2) * b.get(1);
	product[1] = a.get(2) * b.get(0) - a.get(0) * b.get(2);
	product[2] = a.get(0) * b.get(1) - a.get(1) * b.get(0);
	return product;
}

typedef VectorNd<3, float> Vector3f;
typedef VectorNd<3, double> Vector3d;
#endif


template<typename T>
VectorNd<3, T> rotateVecAroundVecAx(VectorNd<3, T> vec, VectorNd<3, T> vecAx, float theta) {

	VectorNd<3, T> ap = vecAx * (dot(vec, vecAx) / dot(vecAx, vecAx));
	VectorNd<3, T> ao = vec - ap;

	VectorNd<3, T> a = vec;
	if (ao.norm() == 0) return a;
	VectorNd<3, T> orth = cross(vecAx, ao);

	T x1 = cos(theta) / (ao.norm());
	T x2 = sin(theta) / (orth.norm());


	VectorNd<3, T> aor = (ao * x1 + orth * x2) * ao.norm();

	a = ap + aor;
	return a;
	//__debugbreak();
}
