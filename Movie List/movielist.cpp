#include "movielist.h"

//Конструктор за замовчуванням
MovieList::MovieList()
{
    list.clear();
}

//Конструктор з параметром
MovieList::MovieList(Movie a)
{
    list.push_back(a);
}

//Конструктор копіювання
MovieList::MovieList(MovieList& a)
{
    list = a.list;
}

//Деструктор
MovieList::~MovieList()
{
    list.clear();
}

//Конструктор виняткових ситуацій з 2 параметрами
MovieList::Errors::Errors(QString usersErrorText, int usersErrorValues)
{
    textOfError = usersErrorText;
    valuse = usersErrorValues;
}

//Конструктор виняткових ситуацій з 1 параметрами
MovieList::Errors::Errors(QString usersErrorText)
{
    textOfError = usersErrorText;
}

//Вивід даних до списку
void MovieList::display(QTableWidget* tw)
{

    tw->setRowCount(list.size());
    for (int i = 0; i < list.size(); i++)
    {
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(list[i].getName()));
        tw->setItem(i,  0, name);
        QTableWidgetItem *director = new QTableWidgetItem(QString::fromStdString(list[i].getDirector()));
        tw->setItem(i,  1, director);
        QTableWidgetItem *year = new QTableWidgetItem(QString::number(list[i].getYear()));
        tw->setItem(i,  2, year);
        QTableWidgetItem *actors = new QTableWidgetItem(QString::fromStdString(list[i].getActors()));
        tw->setItem(i,  3, actors);
        QTableWidgetItem *budget = new QTableWidgetItem(QString::number(list[i].getBudget()));
        tw->setItem(i,  4, budget);
        QTableWidgetItem *lenght = new QTableWidgetItem(QString::number(list[i].getLenght()));
        tw->setItem(i,  6, lenght);
        QTableWidgetItem *country = new QTableWidgetItem(QString::fromStdString(list[i].getCountry()));
        tw->setItem(i,  5, country);
    }
}

//Зчитування фільмів з файду
std::istream& MovieList::operator >> (std::istream& infile)
{
    //Перевірка відкриття файлу
    if(!infile) throw Errors("Error, file cannot be found");
    //Перевірка чи файл порожній
    if(infile.peek()==std::ifstream::traits_type::eof()) throw Errors("Error, file is empty");

    Movie tmp;
    std::string str;
    try
    {
        //Пострічкове зчитування з файлу
        while (std::getline(infile, str))
        {
            tmp.readFromFile(str);
            list.push_back(tmp);
        }
    }
    catch (Movie::ErrorsMovie& error)
    {
        throw Errors(error.textOfError);
    }


    return infile;
}

//Запис фільмів до файду
std::ostream& MovieList::operator << (std::ostream& outfile)
{
    //Перевірка відкриття файлу
    if(!outfile)throw Errors("Error, file cannot be found");
    //Перевірка чи список фільмів порожній
    if(list.size()==0)throw Errors("Error, list is empty");
    //Пострічковий ввід фільмів до файлу
    for (int i = 0; i < list.size(); i++)
        list[i].writeIntoFile(outfile);
    return outfile;
}

//Додання одного фільму
void  MovieList::push_back(Movie a)
{
    list.push_back(a);
}

//Очищення списку
void MovieList::clear()
{
    list.clear();
}

//Видалення одного елементу
void MovieList::deleteElement(int index)
{
    if(list.size()==0)throw Errors("Error, list is empty");
    list.erase(list.begin() + index);
}

//Розмір масиву
int MovieList::getSize()
{
    return list.size();
}

//Сортування вибіркою за країною
void MovieList::selectionSort()
{
    //Перевірка чи файлу порожній
    if(list.size()==0)throw Errors("Error, list is empty");

    int i, j, min_idx;

    for (i = 0; i < list.size() - 1; i++)
    {

        min_idx = i;
        for (j = i + 1; j < list.size(); j++)
            if (list[j].getCountry() < list[min_idx].getCountry())
                min_idx = j;

        if (min_idx != i)
            std::swap(list[i], list[min_idx]);
    }
}

//Знаходження найстарішого та найдорожчого фільму.
Movie MovieList::mostExpensiveAndOldest()
{
    if(list.size()==0)throw Errors("Error, list is empty");
    //Створюємо два допоміжні списка фільмів та сортуємо перший за бюджетом, другий за ріком випуску.
    std::vector<Movie> listForBudget = list;
    std::vector<Movie> listForYear = list;

    std::sort(listForBudget.begin(), listForBudget.end(),
        [](Movie a, Movie b) {
            return a.getBudget() > b.getBudget();
        });
    std::sort(listForYear.begin(), listForYear.end(),
        [](Movie a, Movie b) {
            return a.getYear() < b.getYear();
        });
    //Пошук фільму одночасно найстарішого та найдорожчого фільму.

    if (listForBudget[0] == listForYear[0]) return listForBudget[0];

    throw(Errors("Warning, no such movie"));
}

//Знаходження найбільш популярного актору.
std::string MovieList::mostPopularActor()
{
    if(list.size()==0)throw Errors("Error, list is empty");
    //Створюєм стрічку з всіма акторами з списку
    std::string str;
    for (Movie el : list)
        str += el.getActors()+" ";
    std::vector<std::string> stringVec;

    int found1 , found2, found3=0, sum = 1, i = 0;
    //Ділим цю стрічку на підстрічки
    while (str.find(" ", found3+1))
    {
        found1 = found3++;
        found2 = str.find(" ", ++found1);
        found3 = str.find(" ", ++found2);
        stringVec.push_back(str.substr(found1, found3-sum));
        sum += stringVec[i++].size() + 1;
    }

    int arrSize = stringVec.size();
    for (int k = 4; k < stringVec.size(); k += 4)
        stringVec.erase(std::next(stringVec.begin(), k));
    //Знаходимо актора який тряпляється найбільше.
    int index, max=0;
    for (int k = 0; k < stringVec.size(); k++)
    {
        if (max < std::count(stringVec.begin(), stringVec.end(), stringVec[k]))
        {
            max = std::count(stringVec.begin(), stringVec.end(), stringVec[k]);
            index = k;
        }
    }
    if(stringVec.empty())throw(Errors("Warning, no such actor"));
    return stringVec[index];
}
//Знаходження фільмів з де знімався заданий актор.
std::string MovieList::allMoviesByActor(std::string actor)
{
    //Перевірка чи список порожній
    if(list.size()==0)throw Errors("Error, list is empty");
    //Перевірка формату актора
    if( actor=="")
    {
        throw(Errors("Error,check input"));
    }
    std::vector<int> index;
    std::string tmp, listOfMovies;
    //Шукаєм фільми з заданим актором, зберігаєм ці фільми
    for (int i = 0; i < list.size(); i++)
    {
        tmp = list[i].getActors();
        if (tmp.find(actor,0) != std::string::npos) index.push_back(i);
    }

    if(index.empty())
    {
        throw(Errors("Warning, no such movie"));
    }
    for (int i = 0; i < index.size()-1; i++)
        listOfMovies += list[index[i]].getName() + ", ";

    return listOfMovies + list[index[index.size()-1]].getName();
}

//Знаходження фільмів з найбільшим бюджетом та найменшою тривалістю за заданою країною виробництва.
std::string MovieList::mostExpensiveAndShortestByCountry(std::string country)
{
    //Перевірка чи список порожній
    if(list.size()==0)throw Errors("Error, list is empty");
    //Перевірка формату країни
    if( country=="")
    {
        throw(Errors("Error, check input data"));
    }

    std::vector<Movie> listForBudget;
    std::vector<Movie> listForLenght;
    //Створюєм два допоміжі списка фільмів та записуєм в них фільми з заданою країною виробництва
    for(Movie el:list)
    {
        if(el.getCountry()!=country)continue;;
        listForBudget.push_back(el);
        listForLenght.push_back(el);
    }
    //Перевірка чи існують фільми з заданою країною
    if(listForBudget.empty())
    {
        throw(Errors("No such movies"));
    }

    std::sort(listForBudget.begin(), listForBudget.end(),
        [](Movie a, Movie b) {
            return a.getBudget() < b.getBudget();
        });
    std::sort(listForLenght.begin(), listForLenght.end(),
        [](Movie a, Movie b) {
            return a.getLenght() > b.getLenght();
        });

    std::vector<int> index;

    for (int i = 0; i < listForBudget.size(); i++)
        if ((listForBudget[i].getCountry() == country && listForLenght[i].getCountry() == country)&&
             (listForBudget[i].getLenght() == listForLenght[i].getLenght())&&
             (listForBudget[i].getBudget() == listForLenght[i].getBudget()))
                index.push_back(i);
    std::string tmp="";

    if(index.empty())
    {
        throw(Errors("No such movies"));
    }

    for (int i = 0; i < index.size()-1; i++)
        tmp+=listForBudget[index[i]].getName()+", ";


    return country+" movie with biggest budget and shortest length is " + tmp+listForBudget[listForBudget.size()-1].getName();
}
//Знаходження фільмів з однаковими режисерами та найменшим бюджетом.
std::string MovieList::sameDirectorsAndLowestBudgets()
{
    //Перевірка чи список порожній
    if(list.size()==0)throw Errors("Error, list is empty");
    //Створюєм допоміжний список та сортуєм його за бюджетом
    std::vector<Movie> listForBudget = list;

    std::sort(listForBudget.begin(), listForBudget.end(),
        [](Movie a, Movie b) {
            return a.getBudget() < b.getBudget();
        });

    std::vector<int> index;

    std::string cmp = listForBudget[0].getDirector();
    index.push_back(0);
    //Перевірка чи існує більше 1 фільму з однаковим режисером та найменшим бюджетом.
    for (int i = 1; i < list.size(); i++)
        if (listForBudget[i].getDirector() == cmp)
            index.push_back(i);

    std::string tmp = "";
    for (int i = 0; i < index.size()-1; i++)
        tmp += listForBudget[index[i]].getName() + ", ";

    if(index.size()==1)throw Errors("No such movies");
    return tmp+listForBudget[index[index.size()-1]].getName();
}

//Знаходження фільмів для кожного режисера з найбільшою тривалістю
std::string MovieList::longestPerDirector()
{

    if(list.size()==0)throw Errors("Error, list is empty");

    std::vector<Movie> listForDirector = list;
    std::vector<int> index;
    //Створюємо два допоміжний список фільмів та сортуємо його за за тривалістю.
    std::sort(listForDirector.begin(), listForDirector.end(),
        [](Movie a, Movie b) {
            return a.getDirector() > b.getDirector();
        });

    std::string str = "";
    //Відокремлення фільмів якщо є ще фільми від даного режисера.
    for (int i = 0; i < listForDirector.size(); i++)
    {
        std::string tmp = listForDirector[i].getDirector();
        if (std::count_if(listForDirector.begin(), listForDirector.end(),
            [&tmp](Movie a) {
                return a.getDirector() == tmp;
            }) > 1) index.push_back(i);
        else str += "   "+listForDirector[i].getDirector() + " - " + listForDirector[i].getName() + "\n";
    }
    //Знахолдення найдовшого фільму для режисера якшо він має більше 1 фільму.
    int max = 0, indexOfMax = 0, j = 0;;
    std::string name = listForDirector[index[0]].getDirector();
    for (int i = 0; i < index.size(); i++)
    {
        if (listForDirector[index[i]].getDirector() == name)
        {
            if (max < listForDirector[index[i]].getLenght())
            {
                max = listForDirector[index[i]].getLenght();
                indexOfMax = index[i];
            }
        }
        else
        {
            str += "   "+listForDirector[indexOfMax].getDirector() + " - " + listForDirector[indexOfMax].getName()  + "\n";

            name = listForDirector[index[i+ 1]].getDirector();
            max = 0;
            indexOfMax = 0;
            i--;
        }
    }
    str += "   "+listForDirector[indexOfMax].getDirector() + " - " + listForDirector[indexOfMax].getName()  + "\n";
    std::cout << std::endl;

    return str;
}
