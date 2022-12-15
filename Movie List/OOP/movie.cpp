#include "movie.h"

//Констуктор за замовчуванням
Movie::Movie()
{
    name = "";
    director = "";
    year = 0;
    actors = "";
    budget = 0;
    lenght = 0;
    country = "";
}

//Конструктор з параметрами
Movie::Movie(std::string usersName, std::string usersDirector, int usersYear, std::string usersActors
    , int usersBudget, int usersLength, std::string usersCountry)
{
    //Перевірка даних
    if( usersName==""||  usersDirector==""|| usersYear < 0 || usersActors==""
            || usersBudget<0||  usersLength<0|| usersCountry=="") throw ErrorsMovie("Error, check input data");
    name = usersName;
    director = usersDirector;
    year = usersYear;
    actors = usersActors;
    budget = usersBudget;
    lenght = usersLength;
    country = usersCountry;
}

//Конструктор виняткових с ситуація з 2 параметрами
Movie::ErrorsMovie::ErrorsMovie(QString usersErrorText, int usersErrorValues)
{
    textOfError = usersErrorText;
    valuse = usersErrorValues;
}

//Конструктор виняткових с ситуація з 1 параметром
Movie::ErrorsMovie::ErrorsMovie(QString usersErrorText)
{
    textOfError = usersErrorText;
}

//Геттери для полів
std::string Movie::getName()
{
    return name;
}
std::string Movie::getDirector()
{
    return director;
}
int Movie::getYear()
{
    return year;
}
std::string Movie::getActors()
{
    return actors;
}
long int Movie::getBudget()
{
    return budget;
}
float Movie::getLenght()
{
    return lenght;
}

std::string Movie::getCountry()
{
    return country;
}

//Сеттери для полів
void Movie::setName(std::string usersName)
{
    name = usersName;
}
void Movie::setDirector(std::string usersDirector)
{
    director = usersDirector;
}

void Movie::setYear(int usersYear)
{
    year = usersYear;
}

void Movie::setActors(std::string usersActors)
{
    actors = usersActors;
}

void Movie::setBudget(long int usersBudget)
{
    budget = usersBudget;
}

void Movie::setLenght(float usersLength)
{
    lenght = usersLength;
}

void Movie::setCountry(std::string usersCountry)
{
    country = usersCountry;
}

//Вивід фільму
void Movie::display(QPlainTextEdit* pl)
{
    QString str = QString::fromStdString("Name: "+name + " \nDirector: " + director + "\nYear: "  + std::to_string(year) + " \nActors: "
            + actors + "\nBudget: " + std::to_string(budget)+" mil$\nLenght: "+ std::to_string(lenght) + " min\nCountry: " + country);
    pl->setPlainText(str);
}

//Зчитування фільма з файлу
void  Movie::readFromFile( std::string str)
{
    //Знаходимо назву фільма
    int found1 = str.find("'");
    int found2 = str.find("'", found1+1);
    //Переві чи назва фільма була знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    name = str.substr(found1+1, found2-3);
     //Знаходимо режисера фільма
    found1 = str.find("'", found2+1);
    found2 = str.find("'", found1+1);
    //Переві чи режисер фільма була знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    director = str.substr(found1+1, found2-name.size()-6);
     //Знаходимо рік випуску фільма
    found1 = str.find("'", found2+1);
    found2 = str.find("'", found1+1);
    //Переві чи рік випуску фільма був знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    year = stoi(str.substr(found1 + 1, found2 - 1));
     //Знаходимо акьторів фільма
    found1 = str.find("'", found2 + 1);
    found2 = str.find("'", found1 + 1);
    //Переві чи акьтори фільма фільма були знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    actors = str.substr(found1 + 1, found2 - name.size() - director.size()-16);
     //Знаходимо бюджет фільма
    found1 = str.find("'", found2 + 1);
    found2 = str.find("'", found1 + 1);
    //Переві чи бюджет фільма було знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    budget = stoi(str.substr(found1 + 1, found2 - name.size() - director.size()- actors.size() - 18));
     //Знаходимо тривалість фільма
    found1 = str.find("'", found2 + 1);
    found2 = str.find("'", found1 + 1);
    //Переві чи тривалість фільма була знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    lenght = stoi(str.substr(found1 + 1, found2 - name.size() - director.size()- actors.size() - 24));
     //Знаходимо країну виробництва фільма
    found1 = str.find("'", found2 + 1);
    //Переві чи країну виробництва фільма була знайдена
    if(found1==std::string::npos||found2==std::string::npos)throw ErrorsMovie("Error, check input data");
    country = str.substr(found1 + 1, 3  );

}
//Ввід фільмів до файлу
void Movie::writeIntoFile(std::ostream& file)
{
    file <<  name << ' ' << director << ' ' << year << ' ' << actors << ' ' << budget << ' ' << lenght << ' ' << country<<std::endl;//<< director << year
}

//Оператор присвоєння
void Movie::operator = (Movie a)
{
    name = a.name;
    director = a.director;
    year = a.year;
    actors = a.actors;
    budget = a.budget;
    lenght = a.lenght;
    country = a.country;
}

//Оперетор порівняння
bool Movie::operator==(Movie a)
{
    return
            name == a.name &&
            director == a.director &&
            year == a.year &&
            actors == a.actors &&
            budget == a.budget &&
            lenght == a.lenght &&
            country == a.country;

}
