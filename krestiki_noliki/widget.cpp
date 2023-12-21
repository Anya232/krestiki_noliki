#include "widget.h"

#include <QVBoxLayout>
#include <QGridLayout>

#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent)
{    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(30);

    this->setWindowTitle("Крестики-Нолики");

    m_titleLabel = new QLabel("");
    m_titleLabel->setStyleSheet("font-size: 24px");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    QGridLayout* grid = new QGridLayout();
    grid->setSpacing(0);

    for (int i = 0; i < Map::MAP_SIZE; i++) {
        for (int j = 0; j < Map::MAP_SIZE; j++) {
            QPushButton* btn = new QPushButton(this);
            btn->setFixedSize(80, 80);
            btn->setStyleSheet("font-size: 36px");
            connect(btn, &QPushButton::clicked, [=]() {
                this->buttonClicked(j, i);
            });

            grid->addWidget(btn, i, j);
            m_buttons.append(btn);
        }
    }

    QPushButton* resetBtn = new QPushButton("Новая игра");
    connect(resetBtn, &QPushButton::pressed, this, &Widget::resetGame);

    mainLayout->addWidget(m_titleLabel);
    mainLayout->addLayout(grid);
    mainLayout->addWidget(resetBtn);
    mainLayout->addStretch();

    m_bot = new Bot(&m_map);
    resetGame();
}

Widget::~Widget()
{
}

void Widget::updateMap()
{
    for (int i = 0; i < Map::MAP_SIZE; i++) {
        for (int j = 0; j < Map::MAP_SIZE; j++) {
            QString ch = m_map.getCellChar(j, i);
            int idx = i * Map::MAP_SIZE + j;

            if (ch == "X")
                m_buttons[idx]->setStyleSheet("font-size: 36px; color: red");
            else if (ch == "O")
                m_buttons[idx]->setStyleSheet("font-size: 36px; color: green");

            m_buttons[idx]->setText(ch);
        }
    }
}

void Widget::resetGame()
{
    m_gameOver = false;
    m_map.clear();

    m_player = Map::getRandValue();
    m_bot->setPlayingWith((m_player == Map::Value::X) ? Map::Value::O : Map::Value::X);

    m_titleLabel->setText("Игра началась!");

    updateMap();
}

bool Widget::checkGameOver()
{
    Map::Value winner = m_map.getWinner();

    if (winner != Map::None || m_map.isFull()) {
        m_gameOver = true;

        switch(winner) {
            case Map::X: m_titleLabel->setText("Игрок Х победил!"); break;
            case Map::O: m_titleLabel->setText("Игрок O победил!"); break;
            default: m_titleLabel->setText("Ничья!"); break;
        }
    }

    return m_gameOver;
}

void Widget::buttonClicked(int x, int y)
{
    if (m_gameOver) return;

    if (m_map.getCell(x, y) != Map::None)
    {
        m_titleLabel->setText("Клетка не пустая!");
        return;
    }

    m_map.setCell(x, y, m_player);
    updateMap();
    if (checkGameOver()) return;

    m_bot->makeMove();
    updateMap();
    if (checkGameOver()) return;
}

