#include "vector2.h"
#include <math.h>

vector2 vector2::operator +(vector2 const& vector2B){
    return vector2(x+vector2B.x, y+vector2B.y);
};
vector2 vector2::operator -(vector2 const& vector2B){
    return vector2(x-vector2B.x, y-vector2B.y);
};
vector2 vector2::operator *(int const& scalar){
    return vector2(x*scalar, y*scalar);
};
vector2 vector2::operator /(int const& scalar){
    return vector2(x/scalar, y/scalar);
};
bool vector2::operator ==(vector2 const& vector2B){
    if (x==vector2B.x && y==vector2B.y){
        return true;
    }
    return false;
}

int vector2::magnitude(){
    return sqrt(x*x + y*y);
}

int vector2::dot(vector2 vector2B){
    return (x*vector2B.x + y*vector2B.y);
}