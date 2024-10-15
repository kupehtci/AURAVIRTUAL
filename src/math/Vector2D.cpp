#include "Vector2D.h"


#include <iostream>
#include <math.h>
//#include "NCMath.h"



#include <iostream>
#include <math.h>
//#include "NCMath.h"

using namespace aura;


//Initializations of static members
const Vector2D Vector2D::up = Vector2D(0, 1);
const Vector2D Vector2D::right = Vector2D(1, 0);
const Vector2D Vector2D::down = Vector2D(0, -1);
const Vector2D Vector2D::left = Vector2D(-1, 0);
const Vector2D Vector2D::zero = Vector2D(0, 0);


Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}


/// <summary>
/// Operator for cout overloaded to allow to print on console the values stored inside class
/// </summary>
/// <param name="output">ostream class that get passed through the function</param>
/// <param name="vector2D">vector 2D instance to print its parameters</param>
/// <returns>ostream output with the encadenation of the vector2D values</returns>
std::ostream& operator<<(std::ostream& output,const Vector2D& vector2D)
{
    output << "(" << vector2D.x << "," << vector2D.y << ")";
    return output;
}

Vector2D& Vector2D::operator=(const Vector2D& equal) {

    this->x = equal.x;
    this->y = equal.y;
    return *this;
}

/// <summary>
/// Operator overload of sumatory function
/// </summary>
/// <param name="plus">Secondary parameter of the plus calculation</param>
/// <returns>Object with the two plus</returns>
Vector2D Vector2D::operator+(const Vector2D& plus) {
    return Vector2D(this->x + plus.x, this->y + plus.y);
}

/// <summary>
/// Operator overload for substracting vectors
/// </summary>
/// <param name="subs"></param>
/// <returns></returns>
Vector2D Vector2D::operator-(const Vector2D& subs) {
    return Vector2D(this->x - subs.x, this->y - subs.y);
}

Vector2D Vector2D::operator*(const float& op) {
    return Vector2D(this->x * op, this->y * op);
}


float Vector2D::Magnitude() {
    //Calculate |v| = squareroot(x^2 + y^2);
    return (float)(sqrt(pow(x, 2) + pow(y, 2)));
}

Vector2D* Vector2D::GetNormalized(Vector2D vector) {
    float magnitude = vector.Magnitude();

    Vector2D* normalizedVector = new Vector2D(vector.x / magnitude, vector.y / magnitude);
    return normalizedVector;
}

void Vector2D::Normalize() {
    float magnitude = this->Magnitude();
    this->x = (this->x / magnitude);
    this->y = (this->y / magnitude);
    Vector2D gh = Vector2D(3.0f, 3.0f);
}

float Vector2D::Distance(Vector2D a, Vector2D b) {
    Vector2D differenceVector = a - b;
    return differenceVector.Magnitude();
}

float Vector2D::Dot(Vector2D a, Vector2D b) {
    return (a.x * b.x) + (a.y * b.y);
}

float Vector2D::AngleRad(Vector2D a, Vector2D b) {
    // a.b = |a|*|b|*cos(theta)   ->   theta = arccos(a.b / |a|*|b|)
    float dotProduct = Dot(a, b);
    return acos(dotProduct / (a.Magnitude() * b.Magnitude()));
}

float Vector2D::AngleDeg(Vector2D a, Vector2D b){
    //return AuraMath::Rad2Deg(AngleRad(a, b));
    return 0.0f;
}

float Vector2D::SignedAngle(Vector2D a, Vector2D b) {
    //float angle = 0.0f;
    //angle = acos(Dot(a.GetNormalized(), b.GetNormalized()));
    //float cross = cross(a, b);
    //if (dotProduct(Vn, cross) < 0) { // Or > 0
    //	angle = -angle;
    //}
    return 0.0f;
}

Vector2D Vector2D::Lerp(Vector2D a, Vector2D b, float t) {

   //float lx = AuraMath::Lerp(a.x, b.x, t);
    //float ly = AuraMath::Lerp(a.y, b.y, t);
    //return Vector2D(lx, ly);
    return Vector2D(0.0, 0.0);
}
