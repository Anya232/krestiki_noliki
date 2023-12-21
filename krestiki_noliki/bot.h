#ifndef BOT_H
#define BOT_H

#include "map.h"

class Bot
{

public:
    Bot(Map* map);

    void setPlayingWith(Map::Value value);
    void makeMove();

private:
    Map* m_map;
    Map::Value m_playingWith;
};

#endif // BOT_H
