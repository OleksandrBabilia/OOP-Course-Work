#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <QPlainTextEdit>


//Клас фільму
class Movie
{
private:
    std::string name;
    std::string director;
    int year;
    std::string actors;
    int budget;
    int lenght;
    std::string country;
public:
    class ErrorsMovie
        {
        public:
            QString textOfError;
            int valuse;
            ErrorsMovie(QString usersErrorText, int usersErrorValues);
            ErrorsMovie(QString usersErrorText);
        };
    Movie();
    Movie(std::string, std::string, int, std::string,  int, int, std::string);
    std::string getName();
    std::string getDirector();
    int getYear();
    std::string getActors();
    long int getBudget();
    float getLenght();
    std::string getCountry();
    void setName(std::string);
    void setDirector(std::string);
    void setYear(int);
    void setActors(std::string);
    void setBudget(long int);
    void setLenght(float);
    void setCountry(std::string);
    void readFromFile(std::string);
    void writeIntoFile(std::ostream&);
    void operator = (Movie );
    bool operator==(Movie);
    void display(QPlainTextEdit*);
};

#endif // MOVIE_H
