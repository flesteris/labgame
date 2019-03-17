#ifndef DATE_HPP
#define DATE_HPP

class Date
{
private:
    int day;
    int week;
    int month;

public:
    Date();
    ~Date();
    void next();
};

#endif
