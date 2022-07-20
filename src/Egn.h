#include <iostream>
#include <string>

class Egn
{
    public:
    
    enum class egnParseStatus
    {
        OK, WrongLength, NotAllSymbolsAreDigits, InvalidDate, InvalidControlNumber
    };
    
private:
    size_t day;
    size_t month;
    size_t year;
    
    bool isMale;
    std::string regionName;
    
    egnParseStatus status;
    
    size_t bornBefore;
    
    public:
    
    Egn(const std::string& egnStr);
    
    size_t getDay() const;
    size_t getMonth() const;
    size_t getYear() const;
    bool getIsMale() const;
    const std::string& getRegion() const;
    bool isValidEgn() const;
    size_t getBornBefore() const; //the count of the born babies born on the same date, same region, same gender BEFORE the current.
    
    Egn::egnParseStatus getParseStatus() const;
    
};
