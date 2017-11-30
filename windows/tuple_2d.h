#ifndef     _COORD_
#include    "coord.h"
#endif  //  _COORD_

#ifndef     _TUPLE_2D_
#define     _TUPLE_2D_

class Tuple_2d {
    protected:
    real xy[2];
    public:
    Tuple_2d (void) {}
    Tuple_2d (const Tuple_2d& t);
    Tuple_2d (real x, real y);
    void operator = (const Tuple_2d& t);
    bool operator == (const Tuple_2d& t) const;
    bool operator != (const Tuple_2d& t) const;
    void operator () (real x, real y);
    real operator | (const Tuple_2d& t) const;
    real operator [] (Coord c) const;
    real& operator [] (Coord c);
};

inline real Tuple_2d::operator [] (Coord c) const {
    return xy[c];
}

inline real& Tuple_2d::operator [] (Coord c) {
    return xy[c];
}

#endif  //  _TUPLE_2D_
