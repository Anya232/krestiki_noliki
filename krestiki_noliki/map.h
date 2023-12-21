#ifndef MAP_H
#define MAP_H

#include <QString>

class Map
{

public:
    const static int MAP_SIZE = 3;
    enum Value { X, O, None };

    Map();

    void clear();

    static Value getRandValue();

    QString getCellChar(int x, int y);
    Value getCell(int x, int y);
    void setCell(int x, int y, Value value);

    bool isFull();
    Value getWinner();

private:
    Value m_map[MAP_SIZE * MAP_SIZE];
};

#endif // MAP_H
