#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMap>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//Конструктор
    ~MainWindow();//Деструктор

private slots:
    void core();//Главный алгоритм заполнения и сортировки словаря
    void inputMap();//ЗАполнение мапы
    void outputMap();//Вывод Qmap в файл
    void sort();//Сортировка Qmap

    void on_loadFile_clicked();//Обработка нажатия на кнопку загрузки файла
    void on_radioButton_alphabet_clicked();//Обработка нажатия на кнопку выбора режима сортировки (алфавитная)
    void on_radioButton_frequency_2_clicked();//Обработка нажатия на кнопку выбора режима сортировки (частотная)
    void on_outputButton_clicked();//Обработка нажатия на кнопку вывода в файл


    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;//Главное окно
    QString fileName="";//Имя файла с текстом
    QFile reading;//Файл считывания
    bool sortingType;//Тип сортировки (1-алфавитная    0-по частоте)
    QString fileOutputName="";//Имя файла для вывода
    QFile recording;//Файл записи
    QMap<QString,int> dictionary; //Словарь (ключ-значение)
};
#endif // MAINWINDOW_H
