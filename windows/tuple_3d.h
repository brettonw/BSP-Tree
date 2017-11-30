#ifndef     _COORD_
#include    "coord.h"
#endif  //  _COORD_

#ifndef	    _TUPLE_3D_
#define	    _TUPLE_3D_

class Tuple_3d {
    private:
    protected:
    real	xyz[4];
    public:
    Tuple_3d (void) {}
    Tuple_3d (const Tuple_3d& t);
    Tuple_3d (real x, real y, real z, real w);
    void operator = (const Tuple_3d& t);
    bool operator == (const Tuple_3d& t) const;
    bool operator != (const Tuple_3d& t) const;
    void operator () (real x, real y, real z, real w);
    real operator | (const Tuple_3d& t) const;
    real operator [] (Coord c) const;
    real& operator [] (Coord c);
    Coord majorAxis (void) const;
    Coord minorAxis (void) const;
};

inline	real	Tuple_3d::operator [] (Coord c) const {
    return xyz[c];
}

inline	real& Tuple_3d::operator [] (Coord c) {
    return xyz[c];
}


#endif  //  _TUPLE_3D_
