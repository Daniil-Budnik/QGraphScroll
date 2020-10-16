#ifndef QGRAPHSCROLL_H
#define QGRAPHSCROLL_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QScrollBar>
#include <QLCDNumber>

#include "QCustomPlot/qcustomplot.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class QGraphScroll; }
QT_END_NAMESPACE

class QGraphScroll : public QMainWindow
{
    Q_OBJECT

public:
    QGraphScroll(QWidget *parent = nullptr);
    ~QGraphScroll();

    QCustomPlot *Graph;

    void Default();                                                                 // Начальные настройки
    void DarkMode();                                                                // Темная тема

    // Настройки интерактива
    void setInteractive(bool Enable = true);
    void setRangeDrag(bool Enable = true);
    void setRangeZoom(bool Enable = true);
    void setSelectAxes(bool Enable = true);
    void setSelectLegend(bool Enable = true);
    void setSelectPlottables(bool Enable = true);

    // Стилистика
    void setColor(QColor Color);                                                    // Цвет
    void setBackLineColor(QColor Color_1, QColor Color_2);                          // Цвет бортов
    void setUpColor(QColor Up, QColor Dow);                                         // Цвет фона внутри бортов
    void setBackColor(QColor Up , QColor Down);                                     // Цвет фона вне бортов
    void setColorLine(QColor Color, int Numeral_Graph = 1);                         // Цвет графа
    void setSizeFont(unsigned int Size = 10);                                       // Размер шрифта

    void setVisibleGraph(bool Enable = true, int Numeral_Graph = 1);                // Видимость графа
    void setBuildGraph(unsigned char Num = 30);                                     // Резервируем память под графы

    void appendGraph(double x, double y, int Numeral_Graph = 1,  bool Add = true);  // Добавить новый элемент в гра
    void showGraph(int Numeral_Graph = 1, QColor Color = QColor(200,200,0));        // Нарисовать

    void setStep(double Step = 1);                                                  // Шаг по X
    void setFrame(int frame);                                                       // Масштаб видимости по X (на странице)
    void setSize(int yMin, int yMax);                                               // Масштаб по Y

    void setTickerX(QString Tick, QString Text = "");                               // Тикеры по X
    void setTickerY(QString Tick, QString Text = "");                               // Тикеры по Y

    void ClearGraph();                                                              // Чистка графа
    void Default_Scale();                                                           // Вернуть стандартный масштаб
    void setMove(int List);                                                         // Перемещение по страницам

    std::vector<double> getData(int Numeral_Graph);                                 // Вернуть массив данных


private slots:
    void on_B_Clear_clicked();
    void on_B_Scale_Default_clicked();
    void on_B_Zero_clicked();
    void on_B_Left_clicked();
    void on_B_Right_clicked();
    void on_B_Final_clicked();

    void ListMove();

private:
    Ui::QGraphScroll *ui;

    int yMinPow = -10, yMaxPos = 270;
    int Frame = 4096;
    int List = 0, MaxList = 0;
    int BUILD = 1;
    double STEP = 1;

    std::vector<std::vector<double>> Arr;

    QPushButton *B_Clear, *B_Scale, *B_Left, *B_Right;
    QLCDNumber *LIST;
    QScrollBar *MIKRIK;

};

#endif
