#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile(const int &value);
    int getvalue() const;

private:
    int m_value;
};

#endif // TILE_H
