#include "Cell.h"

bool operator==(Cell c1, Cell c2)
{
    return (c1.row == c2.row) && (c1.col == c2.col);
}

bool operator!=(Cell c1, Cell c2)
{
    return !(c1 == c2);
}
