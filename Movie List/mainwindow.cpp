#include "mainwindow.h"
#include "ui_mainwindow.h"

MovieList list;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnWidth(1,125);
    ui->tableWidget->setColumnWidth(2,60);
    ui->tableWidget->setColumnWidth(3,407);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(6,100);
    ui->tableWidget->setColumnWidth(5,60);
    ui->yearSpinBox->setMinimum(1500);
    ui->yearSpinBox->setMaximum(2022);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Зчитування з файлу
void MainWindow::on_readFromFileButton_clicked()
{
    try
    {
        std::ifstream infile("C:\\Users\\home\\Desktop\\Movies.txt");
        list >> infile;
        list.display(ui->tableWidget);
        ui->indexSpinBox->setMinimum(1);
        ui->indexSpinBox->setMaximum(list.getSize());
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::critical(this,"Error",error.textOfError);
    }

}

//Додання одного фільму
void MainWindow::on_addMovieButton_clicked()
{
    //Перевірки даних
    if(ui->nameLineEdit->text()==""||
            ui->directorLineEdit->text()==""||
            ui->yearSpinBox->text()=="0"||
            ui->actorsLineEdit->text()==""||
            ui->budgetLineEdit->text().toInt()<0||
            ui->budgetLineEdit->text()==""||
            ui->lengthLineEdit->text().toInt()<0||
            ui->lengthLineEdit->text()==""||
            ui->countryLineEdit->text()=="")
    {
        QMessageBox::critical(this, "Error", "Error, check input data");
        return;
    }
    try
    {
        Movie tmp(ui->nameLineEdit->text().toStdString(),
                  ui->directorLineEdit->text().toStdString(),
                  ui->yearSpinBox->text().toInt(),
                  ui->actorsLineEdit->text().toStdString(),
                  ui->budgetLineEdit->text().toInt(),
                  ui->lengthLineEdit->text().toInt(),
                  ui->countryLineEdit->text().toStdString());

        list.push_back(tmp);
        list.display(ui->tableWidget);

        ui->indexSpinBox->setMinimum(1);
        ui->indexSpinBox->setMaximum(list.getSize());
        ui->nameLineEdit->setText("");
        ui->directorLineEdit->setText("");
        ui->yearSpinBox->setValue(0);
        ui->actorsLineEdit->setText("");
        ui->budgetLineEdit->setText("");
        ui->lengthLineEdit->setText("");
        ui->countryLineEdit->setText("");
        }
    catch (Movie::ErrorsMovie& error)
    {
        QMessageBox::critical(this,"Error",error.textOfError);
    }
}

//Очищення полів для вводу інформації
void MainWindow::on_clearButton_clicked()
{
    ui->nameLineEdit->setText("");
    ui->directorLineEdit->setText("");
    ui->yearSpinBox->setValue(0);
    ui->actorsLineEdit->setText("");
    ui->budgetLineEdit->setText("");
    ui->lengthLineEdit->setText("");
    ui->countryLineEdit->setText("");
}

//Запис фільмів у файл
void MainWindow::on_writeIntoFileButton_clicked()
{ 
    try
    {
        std::ofstream outfile("C:\\Users\\home\\Desktop\\OutPut.txt", std::ios::app);
        list << outfile;
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::critical(this,"Error",error.textOfError);
    }
}

//Сортування вибіркою
void MainWindow::on_sortButton_clicked()
{
    try
    {
        list.selectionSort();
        list.display(ui->tableWidget);
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::critical(this,"Error",error.textOfError);
    }


}

//Знаходження найбільш популярного актору
void MainWindow::on_mostPopularActorButton_clicked()
{
    try
    {
        QString str = QString::fromStdString(list.mostPopularActor());
        ui->plainTextEdit->setPlainText("Most popular actor is "+str);
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::warning(this,"Warning",error.textOfError);
    }

}

//Знаходження фільмів з де знімався заданий актор.
void MainWindow::on_allMoviedByActorButton_clicked()
{
    try
    {
        QString str = QString::fromStdString(list.allMoviesByActor(
                           ui->searchActorLineEidt->text().toStdString()));
         ui->plainTextEdit->setPlainText(ui->searchActorLineEidt->text()+" played in "+str);
    }
    catch (MovieList::Errors& error)
    {
        if(error.textOfError=="Error,check input")QMessageBox::critical(this,"Error",error.textOfError);
        else QMessageBox::warning(this,"Warning",error.textOfError);
    }

}

//Знаходження фільмів для кожного режисера з найбільшою тривалістю
void MainWindow::on_longestMoviePerDirButton_clicked()
{
    try
    {
        QString str = QString::fromStdString("Longest movies per Director are:\n\n" + list.longestPerDirector());
        ui->plainTextEdit->setPlainText(str);
    }
    catch (MovieList::Errors& error)
    {
       QMessageBox::critical(this,"Error",error.textOfError);
    }

}

//Знаходження фільмів з однаковими режисерами та найменшим бюджетом.
void MainWindow::on_sameDirLowBudButton_clicked()
{

    try
    {
        QString str = QString::fromStdString("Movies with same Directors and Lowest budgets are: " + list.sameDirectorsAndLowestBudgets());
        ui->plainTextEdit->setPlainText(str);
    }
    catch (MovieList::Errors& error)
    {
       QMessageBox::critical(this,"Error",error.textOfError);
    }


}

//Знаходження найстарішого та найдорожчого фільму.
void MainWindow::on_longesAndMostExpensiveButton_clicked()
{
    try
    {
        Movie a = list.mostExpensiveAndOldest();
        a.display(ui->plainTextEdit);
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::critical(this,"Warning",error.textOfError);
    }
    catch (Movie::ErrorsMovie& error)
    {
        QMessageBox::critical(this,"Warning",error.textOfError);
    }

}

//Знаходження найдорожчого та найкоротшого фільму
void MainWindow::on_mostExpensiveAndShortestButton_clicked()
{
    try
    {
        QString str = QString::fromStdString(list.mostExpensiveAndShortestByCountry(ui->searchCountryLineEdit->text().toStdString()));
        ui->plainTextEdit->setPlainText(str);
    }
    catch (MovieList::Errors& error)
    {
       QMessageBox::critical(this,"Error",error.textOfError);
    }


}

//Очищення списку фільмів
void MainWindow::on_clearListButton_clicked()
{
    list.clear();
    list.display(ui->tableWidget);
    ui->indexSpinBox->setMaximum(list.getSize());
}

//Видалення одного елементу зі списку
void MainWindow::on_deleteButton_clicked()
{
    try
    {
        list.deleteElement(ui->indexSpinBox->value()-1);
        list.display(ui->tableWidget);
        ui->indexSpinBox->setMinimum(1);
        ui->indexSpinBox->setMaximum(list.getSize());
    }
    catch (MovieList::Errors& error)
    {
        QMessageBox::warning(this,"Warning",error.textOfError);
    }

}

