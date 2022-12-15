#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "movie.h"
#include <QTableWidget>


//Клас списку фільмів
class MovieList
{
private:
    std::vector<Movie> list;
public:
    class Errors
        {
        public:
            QString textOfError;
            int valuse;
            Errors(QString usersErrorText, int usersErrorValues);
            Errors(QString usersErrorText);
        };
    MovieList();
    MovieList(Movie);
    MovieList(MovieList&);
    ~MovieList();
    void display(QTableWidget*);
    void push_back(Movie);
    void clear();
    void deleteElement(int);
    int getSize();
    std::istream& operator >> (std::istream&);
    std::ostream& operator << (std::ostream&);
    void selectionSort();
    Movie mostExpensiveAndOldest();
    std::string mostPopularActor();
    std::string allMoviesByActor(std::string);
    std::string mostExpensiveAndShortestByCountry(std::string);
    std::string sameDirectorsAndLowestBudgets();
    std::string longestPerDirector();
};
#endif // MOVIELIST_H
