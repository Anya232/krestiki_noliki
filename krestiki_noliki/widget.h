#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QLabel>

#include "bot.h"
#include "map.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateMap();
    void resetGame();
    bool checkGameOver();

private:
    void buttonClicked(int x, int y);

    Map m_map;

    Map::Value m_player;

    Bot* m_bot;

    QVector<QPushButton*> m_buttons;
    QLabel* m_titleLabel;

    bool m_gameOver = false;
};

#endif // WIDGET_H
