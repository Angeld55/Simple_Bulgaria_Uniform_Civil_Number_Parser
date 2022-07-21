#include "Egn.h"
#include <assert.h>  
#include <algorithm>

std::string getRegionByNumber(int n, int& diff)
{
    static const size_t REGIONS_COUNT = 28 + 1; //All regions + unknown region
    
    static char regions[REGIONS_COUNT][1024] = {"Благоевград", "Бургас", "Варна", "Велико Търново", "Видин", "Враца", "Габрово",
                      "Кърджали", "Кюстендил", "Ловеч", "Монтана", "Пазарджик", "Перник", "Плевен", "Пловдив",
                        "Разград", "Русе", "Силистра", "Сливен", "Смолян", "София - град", "София - окръг", "Стара Загора",
                        "Добрич (Толбухин)", "Търговище", "Хасково", "Шумен", "Ямбол", "Друг/Неизвестен"};
    static int regionNums[REGIONS_COUNT] = {43, 93, 139, 169, 183, 217, 233, 281, 301, 319, 341, 377, 395, 435, 501,
                                 527, 555, 575, 601, 623, 721, 751, 789, 821, 843, 871, 903, 925, 999};
                                 
    for(int i = 0; i < REGIONS_COUNT; i++)
    {
        if(n <= regionNums[i])
        {
            diff = n - (i == 0 ? 0 : (regionNums[i - 1] + 1));
            return regions[i];
        }
    }
    return "";
}

bool isValidDate(int year, int month, int day)
{
    if(1000 <= year <= 3000)
    {
        if((month==1 || month==3 || month==5|| month==7|| month==8||month==10||month==12) && day>0 && day<=31)
            return true;
        else  if(month==4 || month==6 || month==9|| month==11 && day>0 && day<=30)
            return true;
        else if(month==2)
        {
            if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29)
                return true;
            else if(day>0 && day<=28)
                return true;
           return false;
        }
    }
    return false;
}

bool checkLastDigit(const std::string& egn)
{
    int mult[9] = {2, 4, 8, 5, 10, 9, 7, 3, 6};
    int result = 0;
    
    for(int i = 0; i < 9; i++)
        result += (egn[i] - '0') * mult[i];
        
    int rem = result % 11;
    if(rem <= 9)
        return (egn[9] - '0') == rem;
    else
        return (egn[9] - '0') == 0;
}


Egn::Egn(const std::string& egnStr)
{
    if(egnStr.size() != 10)
    {
        status = egnParseStatus::WrongLength;
        return;
    }
    
    if(!std::all_of(egnStr.begin(), egnStr.end(), ::isdigit))
    {
        status = egnParseStatus::NotAllSymbolsAreDigits;
        return;
    }
    
    if(!checkLastDigit(egnStr))
    {
        status = egnParseStatus::InvalidControlNumber;
        return;
    }
    
    int yearNum = atoi(egnStr.substr(0,2).c_str());
    int monthNum = atoi(egnStr.substr(2,2).c_str());
    int dayNum = atoi(egnStr.substr(4,2).c_str());
    
    if(monthNum > 40)
    {
        yearNum += 2000;
        monthNum -= 40;
    }
    else if(monthNum > 20)
    {
        yearNum += 1800;
        monthNum -= 20;
    }
    else
        yearNum += 1900;
  
    day = dayNum;
    month = monthNum;
    year = yearNum;
    
    if(!isValidDate(year, month, day))
    {
        status =  egnParseStatus::InvalidDate;
        return;
    }
    
    int regionAndGenderNum = atoi(egnStr.substr(6,3).c_str());
    
    int diff = 0;
    regionName = getRegionByNumber(regionAndGenderNum, diff);
    bornBefore = diff / 2;

    
    isMale = regionAndGenderNum % 2 == 0;
    
    status = egnParseStatus::OK;
}
    
size_t Egn::getDay() const
{
    assert(isValidEgn());
    
    return day;
}
size_t Egn::getMonth() const
{
    assert(isValidEgn());
    return month;
}
size_t Egn::getYear() const
{
    assert(isValidEgn());
    
    return year;
}
bool Egn::getIsMale() const
{
    assert(isValidEgn());
    return isMale;
}
const std::string& Egn::getRegion() const
{
    assert(isValidEgn());
    return regionName;
}

size_t Egn::getBornBefore() const
{
    return bornBefore;
}

Egn::egnParseStatus Egn::getParseStatus() const
{
    return status;
}

bool Egn::isValidEgn() const
{
    return getParseStatus() == egnParseStatus::OK;
}
