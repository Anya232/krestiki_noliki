#include "map.h"
#include <cassert>

Map::Map()
{
    static_assert(MAP_SIZE > 2); // размеры поля должны быть больше 2
    clear();
}

void Map::clear()
{
    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
    {
        m_map[i] = Value::None;
    }
}

Map::Value Map::getRandValue()
{
    return (Map::Value)(rand() % 2);
}

QString Map::getCellChar(int x, int y)
{
    Value cellValue = getCell(x, y);
    if (cellValue == Value::X)
    {
        return "X";
    }
    else if (cellValue == Value::O)
    {
        return "O";
    }
    else
    {
        return " ";
    }
}

Map::Value Map::getCell(int x, int y)
{
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
    {
        return Value::None;
    }
    return m_map[y * MAP_SIZE + x];
}

void Map::setCell(int x, int y, Value value)
{
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
    {
        m_map[y * MAP_SIZE + x] = value;
    }
}

bool Map::isFull()
{
    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
    {
        if (m_map[i] == Value::None)
        {
            return false;
        }
    }
    return true;
}

Map::Value Map::getWinner()
{
    // Проверка столбцов
    for (int i = 0; i < MAP_SIZE; i++)
    {
        if (m_map[i] != Value::None)
        {
            bool same = true;
            for (int j = 1; j < MAP_SIZE; j++)
            {
                if (m_map[i] != m_map[i + j * MAP_SIZE])
                {
                    same = false;
                    break;
                }
            }
            if (same)
            {
                return m_map[i];
            }
        }
    }

    // Проверка строк
    for (int i = 0; i < MAP_SIZE; i++)
    {
        int y = i * MAP_SIZE;

        if (m_map[y] != Value::None)
        {
            bool same = true;
            for (int j = 1; j < MAP_SIZE; j++)
            {
                if (m_map[y] != m_map[y + j])
                {
                    same = false;
                    break;
                }
            }
            if (same)
            {
                return m_map[y];
            }
        }
    }

    // Проверка диагоналей
    bool same = true;
    for (int i = 1; i < MAP_SIZE; i++)
    {
        if (m_map[0] != m_map[i + i * MAP_SIZE])
        {
            same = false;
            break;
        }
    }
    if (same)
    {
        return m_map[0];
    }

    same = true;
    for (int i = 1; i < MAP_SIZE; i++)
    {
       if (m_map[MAP_SIZE - 1] != m_map[(MAP_SIZE - 1) + i * (MAP_SIZE - 1)])
       {
           same = false;
           break;
       }
    }
    if (same)
    {
       return m_map[MAP_SIZE - 1];
    }

    return Value::None;
}
