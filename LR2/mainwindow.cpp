#include "mainwindow.h"
#include "ui_mainwindow.h"

//Конструктор
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputButton->setEnabled(false);//Делаем кнопку вывода в файл не активной по умолчанию
    ui->startButton->setEnabled(false);//Делаем кнопку старта не активной по умолчанию
}

//Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

//Загрузка файла с текстом
void MainWindow::on_loadFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "*.txt");//Получаем файл с текстом
    reading.setFileName(fileName);//Присваиваем имя файла QFile-у
    ui->outputButton->setEnabled(true);//Делаем кнопку вывода в файл активной
}

//Установка типа сортировки (алфавитная)
void MainWindow::on_radioButton_alphabet_clicked()
{
    if(ui->radioButton_alphabet->isChecked()){
        sortingType=true;
    }
}

//Установка типа сортировки (частотная)
void MainWindow::on_radioButton_frequency_2_clicked()
{
    if(ui->radioButton_frequency_2->isChecked()){
        sortingType=false;
    }
}

//Выбор файла для вывода
void MainWindow::on_outputButton_clicked()
{
    fileOutputName=QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "txt-files (*.txt)");//Получаем имя файла для вывода
    recording.setFileName(fileOutputName);//Присваиваем имя файла для вывода QFile-у
    ui->startButton->setEnabled(true);
}

//Заполнение map
void MainWindow::inputMap()
{
    QString line;//Строка считанная из файла
    QString word;//Слово, которое ищем в словаре
    QString key;//Ключи из словаря
    bool find = false;//Нашли ли данное слово в словаре?

    //Если файл существует и может быть открыт для чтения
    if(reading.exists()&&reading.open(QIODevice::ReadOnly)){
        //Читаем файл
        QTextStream inputstream(&reading);
        //Пока файл не закончился
        while(!inputstream.atEnd()){
            find = false;
            word = "";
            //Получаем строку из файла
            line = inputstream.readLine();
            //Берём каждый символ из строки
            foreach(QChar sym, line){
                find = false;
                //Если символ это буква или дефис (учитываются слова с дефисом)
                if((sym.isLetter()||sym=='-')&&(sym!=' ')){
                    //Прибавляем букву к слову
                    word+=sym;
                    //Если не буква, значит конец слова
                }
                else{
                    //Перебираем все ключи из словаря
                    foreach(key,dictionary.keys()){
                        //Если среди ключей есть наше слово
                        if((key==word)&&(word!="")){
                            //Ставим метку что слово найденно
                            find=true;
                            dictionary[word]++;//увеличиваем его частоту на единицу
                            word = "";
                        }
                     }
                    //Если слово не найденно добавляем слово в словарь со значением 1
                    if((!find)&&(word!="")){
                            dictionary.insert(word,1);
                            word = "";
                    }
               }
           }
        }
    }
reading.close();
}

//Вывод map в файл
void MainWindow::outputMap()
{
    //Если файл для записи существует и открыт для записи
    if(recording.exists()&&recording.open(QIODevice::WriteOnly))
    {
        //Если выбранна сортировка по алфавиту
        if(sortingType){
            //Для каждого элемента из map
            foreach (QString key, dictionary.keys()) {
                QTextStream outputStream(&recording);
                outputStream<<key;//Записываем ключ в файл
                outputStream<<" - ";//Записываем дефис
                //Записываем зачение в файл
                int value=dictionary.value(key);
                QString str;
                str.setNum(value);
                outputStream<<str;
                outputStream<<"\n";
                str = "";
            }
            //Если выбрана сортировка по частоте
        }else
        {
            int maxVal=0;//Максимальное значение
            //Определяем слово в словаре с максимальной частотой, перебирая весь словарь
            foreach(QString key, dictionary.keys()){
                if(dictionary.value(key)>maxVal){
                    maxVal=dictionary.value(key);
                }
            }

            //Выводим словарь на экран, начиная со слов с максимальной частотой
            for(int i=0;i<dictionary.size();i++){
                foreach (QString key, dictionary.keys()){
                    if(dictionary.value(key)==maxVal){
                        QTextStream outputStream(&recording);
                        outputStream<<key;//Записываем ключ в файл
                        outputStream<<" - ";//Записываем дефис
                        //Записываем зачение в файл
                        int value=dictionary.value(key);
                        QString str;
                        str.setNum(value);
                        outputStream<<str;
                        outputStream<<"\n";
                        str = "";
                    }
                }
                maxVal--;
            }
        }
    }
    recording.close();//Закрываем файл для записи
}

//Ядро программы
void MainWindow::core()
{
    inputMap();//Заполняем QMap
    outputMap();//Выводим QMap
}

//Обработка нажатия на кнопку старта
void MainWindow::on_startButton_clicked()
{
    core();//Вызываем ядро программы
}
