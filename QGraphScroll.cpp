#include "QGraphScroll.h"
#include "ui_QGraphScroll.h"

QGraphScroll::QGraphScroll(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QGraphScroll)
{
    ui->setupUi(this);
    Default();

    // ДЛЯ ТЕСТА РАСКОММЕНТИРУЙТЕ

    //DarkMode();
    //
    //setBuildGraph(3);
    //setStep(0.1);
    //setFrame(1000);
    //
    //for(double i = 0 ; i < 100500; i++){
    //    appendGraph(i, sin(i / 10)*30 + 150, 1);
    //    appendGraph(i, cos(i / 10)*30 + 150, 2);
    //    appendGraph(i, 150,3);
    //}
    //
    //showGraph(1,QColor(255,255,0));
    //showGraph(2,QColor(0,255,0));
    //showGraph(3,QColor(255,255,255));

}

// DEL
QGraphScroll::~QGraphScroll(){ delete ui; }

// НАЧАЛЬНЫЕ НАСТРОЙКИ
void QGraphScroll::Default()
{
    // УКАЗАТЕЛИ
    Graph   = ui->Graph;
    B_Clear = ui->B_Clear;
    B_Scale = ui->B_Scale_Default;
    B_Left  = ui->B_Left;
    B_Right = ui->B_Right;
    LIST    = ui->LCD_List;
    MIKRIK  = ui->Micric;

    // ИЗМИНЕНИЕ СТРАНИЦЫ ПРИ ИЗМИНЕНИЕ СКРОЛА
    connect(MIKRIK, &QScrollBar::valueChanged   , this, &QGraphScroll::ListMove);

    // ИКОНКИ
    B_Clear ->setIcon(QIcon(":/Image/TRASH"));
    B_Scale ->setIcon(QIcon(":Image/ZOOM"));
    B_Left  ->setIcon(QIcon(":Image/LEFT"));
    B_Right ->setIcon(QIcon(":Image/RIGHT"));

    // НАСТРОЙКИ
    setStep(1);                     // Шаг равен единице
    setInteractive(true);           // Интерактив
    setSizeFont(10);                // Размер шрифта
    setBuildGraph(1);               // Кол-во графиков по умолчанию
    setSize(0,255);                 // Размерность
}

// ДАРК МОД
void QGraphScroll::DarkMode()
{
    setColor(QColor(0,180,0));
    setBackLineColor(QColor(0,100,0),QColor(0,100,0));
    setUpColor(QColor(60,60,60),QColor(40,40,40));
    setBackColor(QColor(40,40,40),QColor(60,60,60));

    Graph->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    Graph->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
}

// ПОЛНОЕ ВКЛЮЧЕНИЕ ВСЕХ ФУНКЦИЙ ИНТЕРАКТИВА
void QGraphScroll::setInteractive(bool Enable)
{
    setRangeDrag(Enable);
    setRangeZoom(Enable);
    setSelectAxes(Enable);
    setSelectLegend(Enable);
    setSelectPlottables(Enable);
}

// РАЗЛИЧНЫЕ ФУНКЦИИ ИНТЕРАКТИВА
void QGraphScroll::setRangeDrag(bool Enable)          { Graph->setInteraction(QCP::iRangeDrag, Enable); }
void QGraphScroll::setRangeZoom(bool Enable)          { Graph->setInteraction(QCP::iRangeZoom, Enable); }
void QGraphScroll::setSelectAxes(bool Enable)         { Graph->setInteraction(QCP::iSelectAxes, Enable); }
void QGraphScroll::setSelectLegend(bool Enable)       { Graph->setInteraction(QCP::iSelectLegend, Enable); }
void QGraphScroll::setSelectPlottables(bool Enable)   { Graph->setInteraction(QCP::iSelectPlottables, Enable); }

// ------------------------------------------------------------------------------------------------------------------------------

// ЦВЕТ БОРТОВ
void QGraphScroll::setColor(QColor Color)
{
    Graph->xAxis->setBasePen(QPen(Color, 1));
    Graph->yAxis->setBasePen(QPen(Color, 1));
    Graph->xAxis->setTickPen(QPen(Color, 1));
    Graph->yAxis->setTickPen(QPen(Color, 1));
    Graph->xAxis->setSubTickPen(QPen(Color, 1));
    Graph->yAxis->setSubTickPen(QPen(Color, 1));
    Graph->xAxis->setTickLabelColor(Color);
    Graph->yAxis->setTickLabelColor(Color);
    Graph->xAxis->grid()->setSubGridVisible(true);
    Graph->yAxis->grid()->setSubGridVisible(true);
    Graph->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    Graph->yAxis->grid()->setZeroLinePen(Qt::NoPen);
}

// ЦВЕТ ГРАФА
void QGraphScroll::setColorLine(QColor Color, int Numeral_Graph){Graph->graph(Numeral_Graph - 1)->setPen(QPen(Color));}

// ЦВЕТ ФОНА ГРАФА
void QGraphScroll::setUpColor(QColor Up, QColor Down){
    QLinearGradient UpColor;
    UpColor.setFinalStop(0, 350);
    UpColor.setColorAt(0, Up);
    UpColor.setColorAt(1, Down);
    Graph->axisRect()->setBackground(UpColor);
}

// ЦВЕТ ЗАДНИКА ГРАФА
void QGraphScroll::setBackColor(QColor Up, QColor Down){
    QLinearGradient BackColor;
    BackColor.setFinalStop(0, 350);
    BackColor.setColorAt(0, Up);
    BackColor.setColorAt(1, Down);
    Graph->setBackground(BackColor);
}

// ------------------------------------------------------------------------------------------------------------------------------

// ЦВЕТ РАЗМЕТКИ
void QGraphScroll::setBackLineColor(QColor Color_1, QColor Color_2)
{
    Graph->xAxis->grid()->setPen(QPen(Color_1, 1, Qt::DotLine));
    Graph->yAxis->grid()->setPen(QPen(Color_1, 1, Qt::DotLine));
    Graph->xAxis->grid()->setSubGridPen(QPen(Color_2, 1, Qt::DotLine));
    Graph->yAxis->grid()->setSubGridPen(QPen(Color_2, 1, Qt::DotLine));
}

// РАЗМЕР ШРИФТА
void QGraphScroll::setSizeFont(unsigned int Size)
{
    Graph->xAxis->setTickLabelFont(QFont(QFont().family(), Size));
    Graph->yAxis->setTickLabelFont(QFont(QFont().family(), Size));
}

// ------------------------------------------------------------------------------------------------------------------------------

// ВИДИМОСТЬ ГРАФИКА
void QGraphScroll::setVisibleGraph(bool Enable, int Numeral_Graph){Graph->graph(Numeral_Graph - 1)->setVisible(Enable);}

// ИЗМЕНИТЬ КОЛ-ВО ГРАФОВ
void QGraphScroll::setBuildGraph(unsigned char Num)
{
    Graph->clearGraphs();                           // Очистка
    for(unsigned int i = 1; i <= Num; i++ ){        // Проход по массивам каждого графа
        Graph->addGraph();                          // Создаём граф
        Arr.push_back(*new std::vector<double>);    // Добавляем массив
    }
    BUILD = Num;                                    // Кол-во графов записываем в переменную
}

// ------------------------------------------------------------------------------------------------------------------------------

// ДОБАВИТЬ НОВОЕ ЗНАЧЕНИЕ В ГРАФ
void QGraphScroll::appendGraph(double x, double y, int Numeral_Graph, bool Add)
{

    // Проверка на заполненность страницы
    if( (x  >= (MaxList + 1) * Frame) && Add){

        // Если заполнена, добавляем новую страницу
        MaxList++; List = MaxList;

        // Выводим номер страницы
        LIST->display(MaxList  + 1);

        // Устанавливаем предел
        MIKRIK->setMaximum(MaxList);
        MIKRIK->setValue(MaxList);

        // Очищаем график (визуально)
        for(int i = 0; i < BUILD; i++){ Graph->graph(i)->setData(*new QVector<double> , *new QVector<double> ); }

        // Изменяем масштаб
        setSize(yMinPow,yMaxPos);
    }

    // Полученные значения записываем в массив
    if(Add){Arr.at(Numeral_Graph - 1).push_back(y); }

    // Добавляем координаты на график
    Graph->graph(Numeral_Graph - 1)->addData(x , y);


}

// ОТРИСОВКА ГРАФА
void QGraphScroll::showGraph(int Numeral_Graph, QColor Color){ Graph->replot(); setColorLine(Color,Numeral_Graph); }

// НАСТРОЙКА ШАГА
void QGraphScroll::setStep(double Step){ STEP = Step; }



// ИЗМИНЕНИЕ ФРЭЙМА
void QGraphScroll::setFrame(int frame){ Frame =  frame; }

// ------------------------------------------------------------------------------------------------------------------------------

// ИЗМЕНИТЬ РАЗМЕР ГРАФА
void QGraphScroll::setSize(int yMin, int yMax)
{
    yMinPow = yMin, yMaxPos = yMax;
    Graph->xAxis->setRange(Frame * (List) , Frame * (List + 1));
    Graph->yAxis->setRange(yMin, yMax);
}

// Изминение тика
void QGraphScroll::setTickerX(QString Tick, QString Text){
    if(Tick == "pi"){ Graph->xAxis->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi)); }
    else if(Tick == "log"){
        QSharedPointer<QCPAxisTickerLog> TICK(new QCPAxisTickerLog);
        TICK->setLogBase(Text.toDouble());
        Graph->xAxis->setTicker(TICK);
    }
    else if(Tick == "date"){
        QSharedPointer<QCPAxisTickerDateTime> TICK(new QCPAxisTickerDateTime);
        TICK->setDateTimeFormat(Text);    // "d. MMMM\nyyyy"
        Graph->xAxis->setTicker(TICK);
    }


}
void QGraphScroll::setTickerY(QString Tick, QString Text){
    if(Tick == "pi"){ Graph->xAxis->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi)); }
    else if(Tick == "log"){
        QSharedPointer<QCPAxisTickerLog> TICK(new QCPAxisTickerLog);
        TICK->setLogBase(Text.toDouble());
        Graph->yAxis->setTicker(TICK);
    }
    else if(Tick == "date"){
        QSharedPointer<QCPAxisTickerDateTime> TICK(new QCPAxisTickerDateTime);
        TICK->setDateTimeFormat(Text);    // "d. MMMM\nyyyy"
        Graph->yAxis->setTicker(TICK);
    }
}

// ПОЛНАЯ ЧИСТКА
void QGraphScroll::ClearGraph(){
    Graph->clearGraphs();                                                       // Очищаем все графы
    setBuildGraph(BUILD);                                                       // Пересоздаём их
    for(int i = 0; i < BUILD; i++){ Arr.at(i).clear(); }                        // Очищаем массивы
    List = 0, MaxList = 0;                                                      // Очистка переменныз страниц
    setSize(yMinPow,yMaxPos);                                                   // Изменяем масштаб
    LIST->display(List + 1);                                                    // Выводим номер страницы
    MIKRIK->setMaximum(MaxList);                                                // Очистка Sollider
}

// МАСШТАБ ПО УМОЛЧАНИЮ
void QGraphScroll::Default_Scale(){ setSize(yMinPow,yMaxPos); }

// ------------------------------------------------------------------------------------------------------------------------------

// СДВИГ НА СТРАНИЦУ
void QGraphScroll::setMove(int list)
{
    // Проверка на существующую страницу
    if(list >= 0 && list <= MaxList){

        // Переходим на прошлый лист и масштабируем
        List = list; setSize(yMinPow,yMaxPos);

        // Выводим номер страницы
        LIST->display(List  + 1);
        MIKRIK->setValue(List);

        // Проходим по всем имеющимся графикам
        for(int B = 0; B < BUILD; B++){

            // Обнуляем графики
            Graph->graph(B)->setData(*new QVector<double> , *new QVector<double> );

            // Кол-во эллементов в массиве
            int L = Arr.at(B).size();

            // Заполняем значения координат
            for(int i = List * Frame; (i < (List + 1) * Frame) && (i < L); i++){
                appendGraph(i, Arr.at(B).at(i),B + 1, false);
            }
        }

        // Рисуем
        showGraph();
    }
}

// ДАННЫЕ
std::vector<double> QGraphScroll::getData(int Numeral_Graph){return Arr.at(Numeral_Graph-1);}

// ------------------------------------------------------------------------------------------------------------------------------

// КНОПКИ УПРАВЛЕНИЯ
void QGraphScroll::on_B_Clear_clicked()         { ClearGraph();         Graph->replot(); }
void QGraphScroll::on_B_Scale_Default_clicked() { Default_Scale();      Graph->replot(); }
void QGraphScroll::on_B_Zero_clicked()          { setMove(0);           Graph->replot(); }
void QGraphScroll::on_B_Left_clicked()          { setMove(List - 1);    Graph->replot(); }
void QGraphScroll::on_B_Right_clicked()         { setMove(List + 1);    Graph->replot(); }
void QGraphScroll::on_B_Final_clicked()         { setMove(MaxList);     Graph->replot(); }

// СДВИГ СТРАНИЦ ПО СОЛАЙДЕРУ
void QGraphScroll::ListMove(){ setMove(MIKRIK->value()); }




