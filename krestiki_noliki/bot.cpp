#include "bot.h"
#include <cstdlib>

Bot::Bot(Map *map) : m_map(map), m_playingWith(Map::Value::None) {}

void Bot::setPlayingWith(Map::Value value)
{
    m_playingWith = value;
}

void Bot::makeMove() {
    int size = m_map->MAP_SIZE;

    // Проверяем возможные позиции для победы
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (m_map->getCell(x, y) == Map::Value::None)
            {
                m_map->setCell(x, y, m_playingWith);

                if (m_map->getWinner() == m_playingWith)
                {
                    return;
                }
                m_map->setCell(x, y, Map::Value::None);
            }
        }
    }

    // Проверяем возможные позиции для блокировки
    Map::Value opponent = (m_playingWith == Map::Value::X) ? Map::Value::O : Map::Value::X;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (m_map->getCell(x, y) == Map::Value::None)
            {
                m_map->setCell(x, y, opponent);
                if (m_map->getWinner() == opponent)
                {
                    m_map->setCell(x, y, m_playingWith);
                    return;
                }
                m_map->setCell(x, y, Map::Value::None);
            }
        }
    }

    while (true)
    {
        int x = rand() % size;
        int y = rand() % size;

        if (m_map->getCell(x, y) == Map::Value::None)
        {
            m_map->setCell(x, y, m_playingWith);
            return;
        }
    }
}
