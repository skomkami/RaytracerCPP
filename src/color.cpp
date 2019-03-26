#include "../include/color.h"

Color::Color(): r(new double(0.5)), g(new double(0.5)), b(new double(0.5)), s(new double()) 
{}

Color::Color(const double &_r, const double &_g, const double &_b, const double &_s):
    r(new double(_r)), g(new double(_g)), b(new double(_b)), s(new double(_s))
{}

Color::Color(const Color &c): r(new double(c.getR())), g(new double(c.getG())), b(new double(c.getB())), s(new double(c.getS()))
{}

Color& Color::operator=(const Color &c)
{    
    this->setR(c.getR());
    this->setG(c.getG());
    this->setB(c.getB());
    return *this;
}

Color Color::operator+(const Color& c) const
{
    Color temp(this->getR() + c.getR(), this->getG() + c.getG(), this->getB() + c.getB(), this->getS() + c.getS());
    //temp.fixColor();
    return temp;
}

Color Color::operator-(const Color& c) const
{
    Color temp(this->getR() - c.getR(), this->getG() - c.getG(), this->getB() - c.getB(), this->getS() - c.getS());
    //temp.fixColor();
    return temp;
}

Color Color::operator+=(const Color& c)
{
    (*this) = (*this) + c;
    return (*this);
}

Color Color::operator-=(const Color& c)
{
    (*this) = (*this) - c;
    return (*this);
}

Color Color::operator*(const Color& c) const
{
    double r1 = this->getR();
    double g1 = this->getG();
    double b1 = this->getB();
    double s1 = this->getS();
    double r2 = c.getR();
    double g2 = c.getG();
    double b2 = c.getB();
    double s2 = c.getS();

    Color temp(r1*r2, g1*g2, b1*b2, s1*s2);
    //temp.fixColor();
    return temp;
}

Color Color::operator*(double scalar) const
{
    Color temp(this->getR() * scalar, this->getG() * scalar, this->getB() * scalar, this->getS());
    //temp.fixColor();
    return temp;
}


void Color::fixColor()
{
    if(this->getR()>1) this->setR(1);
    if(this->getG()>1) this->setG(1);
    if(this->getB()>1) this->setB(1);
    if(this->getS()>1) this->setS(1);
    if(this->getR()<0) this->setR(0);
    if(this->getG()<0) this->setG(0);
    if(this->getB()<0) this->setB(0);    
    if(this->getS()<0) this->setS(0);
}

double Color::getR()const { return *(this->r); }
double Color::getG()const { return *(this->g); }
double Color::getB()const { return *(this->b); }
double Color::getS()const { return *(this->s); }

void Color::setR(double r)
{
    *(this->r) = r;
}

void Color::setG(double g)
{
    *(this->g) = g;
}

void Color::setB(double b)
{
    *(this->b) = b;
}

void Color::setS(double s)
{
    *(this->s) = s;
}

Color::~Color()
{
    delete this->r;
    delete this->g;
    delete this->b;
    delete this->s;
}

double Color::brightness()
{
    return(this->getR() + this->getG() + this->getB())/3;
}

Color Color::colorAverage(const Color& color)const
{
    return Color((this->getR()+color.getR())/2, (this->getG() + color.getG())/2, (this->getB() + color.getB())/2, (this->getS() + color.getS())/2);
}

Color Color::clip() {
    double alllight = this->getR() + this->getG() + this->getB();
    double excesslight = alllight - 3;
    if (excesslight > 0) {
        this->setR(this->getR() + excesslight*(this->getR()/alllight));
        this->setG(this->getG() + excesslight*(this->getG()/alllight));
        this->setB(this->getB() + excesslight*(this->getB()/alllight));
    }
    if (this->getR() > 1) { this->setR(1); }
    if (this->getG() > 1) { this->setG(1); }
    if (this->getB() > 1) { this->setB(1); }
    if (this->getR() < 0) { this->setR(0); }
    if (this->getG() < 0) { this->setG(0); }
    if (this->getB() < 0) { this->setB(0); }
    
    return Color (this->getR(), this->getG(), this->getB(), this->getS());
}