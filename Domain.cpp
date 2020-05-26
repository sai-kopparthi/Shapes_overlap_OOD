//
// Domain.cpp
//
#include "Domain.h"
#include<iostream>
using namespace std;

Domain::Domain(void):sizex(600),sizey(500) {}

Domain::~Domain(void)
{
  for ( size_t i = 0; i < s.size(); i++ )
    delete s[i];
}

void Domain::addShape(const Shape* p)
{
  s.push_back(p);
}

void Domain::draw(void)
{
  // check if all shapes fit in the domain
  Rectangle domain_rectangle(Point(0,0),sizex,sizey);
  bool fits = true;
  for ( size_t i = 0; i < s.size(); i++ )
  {
    fits &= s[i]->fits_in(domain_rectangle);
  }

  // check for overlap between all objects
  bool overlap = false;
  for ( size_t i = 0; i < s.size(); i++ )
  {
    for ( size_t j = i+1; j < s.size(); j++ )
    {
      overlap |= s[i]->overlaps(*s[j]);
    }
  }

  // print svg header
  cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>\n";
  cout << "<svg width=\"" << sizex+100 << "\" height=\"" << sizey+100 << "\"\n";
  cout << "xmlns=\"http://www.w3.org/2000/svg\">\n";
  cout << "<g transform=\"matrix(1,0,0,-1,50," << sizey+50 << ")\"\n";
  cout << "fill=\"white\" fill-opacity=\"0.5\"";
  cout << " stroke=\"black\" stroke-width=\"2\">\n";

  // draw enclosing domain
  cout << "<rect fill=\"lightgrey\" x=\"0\" y=\"0\""
       << " width=\"" << sizex << "\" height=\"" << sizey << "\"/>\n";

  // draw all shapes
  for ( size_t i = 0; i < s.size(); i++ )
    s[i]->draw();
  cout << "</g>\n";

  // print diagnostic: ok or overlap or does not fit
  cout << "<g transform=\"matrix(1,0,0,1,50," << sizey+90 << ")\"\n";
  cout << " font-family=\"Arial\" font-size=\"32\">\n";
  if ( !fits)
    cout << "<text x=\"0\" y=\"0\">does not fit</text>" << endl;
  else if ( overlap )
    cout << "<text x=\"0\" y=\"0\">overlap</text>" << endl;
  else
    cout << "<text x=\"0\" y=\"0\">ok</text>" << endl;
  cout << "</g>\n";

  cout << "</svg>\n";
}
