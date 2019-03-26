#ifndef _COLOR_H
#define _COLOR_H

struct Color
{
    double *r, *g, *b;
    double *s;

    Color();
    Color(const double &_r, const double &_g, const double &_b, const double &_s);
    Color(const Color &c);
    Color& operator=(const Color& c);
    Color operator+(const Color& c) const;
    Color operator-(const Color& c) const;
    Color operator+=(const Color& c);
    Color operator-=(const Color& c);
    Color operator*(const Color& c) const;
    Color operator*(double scalar) const;
    double getR()const;
    double getG()const;
    double getB()const;
    double getS()const;
    void setR(double r);
    void setG(double g);
    void setB(double b);
    void setS(double s);
    void fixColor();

    double brightness();
    Color colorAverage(const Color& color)const;
    Color clip();
    ~Color();
};

#endif