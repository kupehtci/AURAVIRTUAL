//
// Created by Daniel Laplana Gimeno on 7/2/24.
//

#ifndef AURAVIRTUAL_VECTOR2D_H
#define AURAVIRTUAL_VECTOR2D_H

namespace aura
{

    struct Vector2D {
    public:
        float x;
        float y;

        Vector2D();
        Vector2D(float x, float y);


        //friend std::ostream& operator<<(std::ostream& output, Vector2D& vector2D);
        Vector2D& operator=(const Vector2D& equal);
        Vector2D operator+(const Vector2D& plus);
        Vector2D operator-(const Vector2D& subs);
        Vector2D operator*(const float& op);

        /// <summary>
        /// Calculate the magnitude of a vector
        /// </summary>
        /// <returns>Lenght/Magnitude of a vector</returns>
        float Magnitude();

        /// <summary>
        /// Return a normalized vector with same direction and angle as the given one.
        /// IT DUPLICATED THE VECTOR
        /// </summary>
        /// <param name="vector">Vector to take as reference to create its normalized version</param>
        /// <returns>Normalized vector</returns>
        Vector2D* GetNormalized(Vector2D vector);

        /// <summary>
        /// Normalize the x and y componenents of the vector. Normalize = Vector with the same direction and orientation but a magnitude (lenght) of 1
        /// </summary>
        void Normalize();

        void  Scalar(float scalar);


        // MATHEMATICAL METHODS

        /// <summary>
        /// Distance between the two vectors. Its the magnitude of the vector between them Magnitude(b - a).
        /// </summary>
        /// <param name="a">First vector</param>
        /// <param name="b">Second vector</param>
        /// <returns>Distance between the two vectors</returns>
        static float Distance(Vector2D a, Vector2D b);

        /// <summary>
        /// Calculates the dot product of the two vectors
        /// </summary>
        /// <param name="a"> vector a for the dot product</param>
        /// <param name="b"> vector b for the dot product</param>
        /// <returns></returns>
        static float Dot(Vector2D a, Vector2D b);

        /// <summary>
        /// Return the angle between the two vectors in radians
        /// </summary>
        /// <param name="a">Vector2D for the starting point of the angle</param>
        /// <param name="b">Vector2D for the ending point of the angle</param>
        /// <returns>Angle in degrees</returns>
        static float AngleRad(Vector2D a, Vector2D b);

        /// <summary>
        /// Return the angle between the two vectors in degrees
        /// </summary>
        /// <param name="a">Vector2D for the starting point of the angle</param>
        /// <param name="b">Vector2D for the ending point of the angle</param>
        /// <returns>Angle in degrees</returns>
        static float AngleDeg(Vector2D a, Vector2D b);

        /// <summary>
        /// NOT FINISHED. Return the angle with a sign of direction for the angle in the direction from a to b
        /// </summary>
        /// <param name="a">Vector that its the starting point of the angle</param>
        /// <param name="b">Vector that its the ending point of the angle</param>
        /// <returns></returns>
        static float SignedAngle(Vector2D a, Vector2D b);

        /// <summary>
        /// Linearly interpolates between vector a and b and return the interpolation. Calculates: result = (1-t) * a + t * b
        /// </summary>
        /// <param name="a"> First vector</param>
        /// <param name="b"> Second vector</param>
        /// <param name="t"> Factor of the interpolation. t = 0 will return a and t = 1 will return b. This value is clamped between 0 and 1</param>
        /// <returns>Linear interpolation of the two vectors. </returns>
        static Vector2D Lerp(Vector2D a, Vector2D b, float t);

        /// <summary>
        /// Linearly interpolates between vector a and b and return the interpolation. Calculates: result = (1-t) * a + t * b
        /// </summary>
        /// <param name="a"> First vector</param>
        /// <param name="b"> Second vector</param>
        /// <param name="t"> Factor of the interpolation. t = 0 will return a and t = 1 will return b. This value is not clamped between 0 and 1, so example: LerpUnclamped(1,2,1.5) will return 2.5</param>
        /// <returns>Linear interpolation of the two vectors. </returns>
        static Vector2D LerpUnclamped(Vector2D a, Vector2D b, float t);

        //static float Cross(Vector2D a, Vector2D b);
        //static float SqrMagnitude(Vector2D a);
        //static float Magnitude(Vector2D a);
        //static Vector2D MoveTowards(Vector2D current, Vector2D target, float maxDistanceDelta);
        //static Vector2D Scale(Vector2D a, Vector2D b);
        //static Vector2D ClampMagnitude(Vector2D vector, float maxLength);
        //static Vector2D Normalize(Vector2D value);
        //static Vector2D Reflect(Vector2D inDirection, Vector2D inNormal);
        //static Vector2D Perpendicular(Vector2D inDirection);
        //static Vector2D Project(Vector2D vector, Vector2D onNormal);
        //static Vector2D ProjectOnPlane(Vector2D vector, Vector2D planeNormal);
        //static Vector2D Rotate(Vector2D vector, float angle);
        //static Vector2D RotateTowards(Vector2D current, Vector2D target, float maxRadiansDelta, float maxMagnitudeDelta);
        //static Vector2D SmoothDamp(Vector2D current, Vector2D target, Vector2D& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
        //

        // STATIC MEMBERS FOR COMMON VECTORS
    public:

        static const Vector2D up;				//vector for UP direction
        static const Vector2D right;			//vector for RIGHT direction
        static const Vector2D down;				//vector for DOWN direction
        static const Vector2D left;				//vector for LEFT direction
        static const Vector2D zero;				//vector for ZERO vector components
    };

}

#endif //AURAVIRTUAL_VECTOR2D_H
