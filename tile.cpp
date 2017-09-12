#include "tile.h"

Tile::Tile(const int &value) : m_value(value)
{
}

int Tile::getvalue() const
{
    return m_value;
}
