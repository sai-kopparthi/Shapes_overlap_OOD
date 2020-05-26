//
// Shape.cpp
//
#include "Shape.h"
#include <iostream>
using namespace std;

Circle::~Circle(void) {}

bool Circle::overlaps(const Shape& s) const
{
  return s.overlaps(*this);
}

bool Circle::overlaps(const Circle& c) const
{
  // compute square of distance between centers
  Point p = c.center - center;
  // compare with the square of the sum of radii
  return p.norm2() < (radius+c.radius)*(radius+c.radius);
}

bool Circle::overlaps(const Rectangle& r) const
{
  // coordinates (xn,yn) of the nearest point of the rectangle
  // to the circle center
  int xn = min(max(center.x,r.position.x),r.position.x+r.width);
  int yn = min(max(center.y,r.position.y),r.position.y+r.height);
  // test if the nearest point is in the circle
  return (xn-center.x)*(xn-center.x) +
         (yn-center.y)*(yn-center.y) < radius*radius;
}

bool Circle::fits_in(const Rectangle& r) const
{
  // check if the Circle fits in Rectangle r
  return ( center.x - radius >= r.position.x ) &&
         ( center.x + radius <= r.position.x + r.width ) &&
         ( center.y - radius >= r.position.y ) &&
         ( center.y + radius <= r.position.y + r.height );
}

void Circle::draw(void) const
{
  cout << "<circle cx=\"" << center.x << "\" cy=\"" << center.y
       << "\" r=\"" << radius << "\"/>" << endl;
}

Rectangle::~Rectangle(void) {}

bool Rectangle::overlaps(const Shape& s) const
{
  return s.overlaps(*this);
}

bool Rectangle::overlaps(const Circle& c) const
{
  return c.overlaps(*this);
}

bool Rectangle::overlaps(const Rectangle& r) const
{
  // test if all points of r are outside of the current rectangle
  if ( r.position.x            >= position.x+width  ) return false;
  if ( r.position.x + r.width  <= position.x        ) return false;
  if ( r.position.y            >= position.y+height ) return false;
  if ( r.position.y + r.height <= position.y        ) return false;

  // in all other cases there is overlap
  return true;
}

bool Rectangle::fits_in(const Rectangle& r) const
{
  // check if the Rectangle fits in Rectangle r
  return ( position.x >= r.position.x ) &&
         ( position.x + width <= r.position.x + r.width ) &&
         ( position.y >= r.position.y ) &&
         ( position.y + height <= r.position.y + r.height );
}

void Rectangle::draw(void) const
{
  cout << "<rect x=\"" << position.x << "\" y=\"" << position.y
       << "\" width=\"" << width << "\" height=\"" << height << "\"/>" << endl;
}
