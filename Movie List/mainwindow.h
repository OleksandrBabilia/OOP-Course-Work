#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movie.h"
#include "movielist.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_readFromFileButton_clicked();

    void on_addMovieButton_clicked();

    void on_clearButton_clicked();

    void on_writeIntoFileButton_clicked();

    void on_sortButton_clicked();

    void on_mostPopularActorButton_clicked();

    void on_allMoviedByActorButton_clicked();

    void on_longestMoviePerDirButton_clicked();

    void on_sameDirLowBudButton_clicked();

    void on_longesAndMostExpensiveButton_clicked();

    void on_mostExpensiveAndShortestButton_clicked();

    void on_clearListButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
