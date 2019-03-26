#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
using std::string;

class Exceptions
{
    public:
        Exceptions();
        virtual ~Exceptions();
        virtual void print_exception()=0;
};

class Exception_file: public Exceptions
{
public:
    Exception_file();
    ~Exception_file();
    void print_exception();
};

class Exception_arg: public Exceptions
{
    unsigned nr;
public:
    Exception_arg(int _nr);
    ~Exception_arg();
    void print_exception();
};

#endif // EXCEPTIONS_H