#pragma once

/*

DOCUMENTATION:

vector2::down()         Shortcut for writing Vector2(0, -1)
vector2::left()         Shortcut for writing Vector2(-1, 0)
vector2::right()        Shortcut for writing Vector2(1, 0)
vector2::up()           Shortcut for writing Vector2(0, 1)
vector2::zero()         Shortcut for writing Vector2(0, 0)
vector2::one()          Shortcut for writing Vector2(1, 1)

vector2(x,y)            Returns new vector2 element with x,y
vector2A.magnitude()    Returns magnitude of vector2 element
vector2A.dot(vector2B)  Returns dot product of 2 vector2 elements

Support for following operators:
vector2A    +   vector2B
vector2A    -   vector2B
vector2A    ==  vector2B
vector2     *   scalar
vector2     /   scalar

*/

class vector2
{
    public:
        static vector2 down(){
            return vector2(0, -1);
        }
        static vector2 left(){
            return vector2(-1, 0);
        }
        static vector2 right(){
            return vector2(1, 0);
        }
        static vector2 up(){
            return vector2(0, 1);
        }
        static vector2 zero(){
            return vector2(0, 0);
        }
        static vector2 one(){
            return vector2(1, 1);
        }

        int x,y;
        vector2(int _x, int _y) : x(_x), y(_y) {}
        vector2() : x(0), y(0) {}

        int magnitude();
        int dot(vector2 vector2B);

        vector2 operator +(vector2 const& vector2B);
        vector2 operator -(vector2 const& vector2B);
        vector2 operator *(int const& scalar);
        vector2 operator /(int const& scalar);
        bool operator ==(vector2 const& vector2B);
};