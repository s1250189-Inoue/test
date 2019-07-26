#include <math.h>
#include "common.h"
#include "coord.h"


// add vectors
coord add_vectors( coord a, coord b )
{
    int k;
    coord sum;
    for ( k = 0; k < 3; ++k ) {
	sum.v[ k ] = a.v[ k ] + b.v[ k ];
    }
    return sum;
}

// subtract vectors
coord subtract_vectors( coord a, coord b )
{
    int k;
    coord diff;
    for ( k = 0; k < 3; ++k ) {
	diff.v[ k ] = a.v[ k ] - b.v[ k ];
    }
    return diff;
}

// inner product
double inner_prod( coord a, coord b )
{
    int k;
    double iprod = 0.0;
    for ( k = 0; k < 3; ++k ) {
	iprod += a.v[ k ] * b.v[ k ];
    }
    return iprod;
}

// outer product
coord outer_prod( coord a, coord b )
{
    int k;
    coord oprod;
    for ( k = 0; k < 3; ++k ) {
	oprod.v[ k ] = a.v[ (k+1)%3 ] * b.v[ (k+2)%3 ] - a.v[ (k+2)%3 ] * b.v[ (k+1)%3 ];
    }
    return oprod;
}

// normalize a vector
coord normalize( coord v )
{
    int k;
    double norm = sqrt( inner_prod( v, v ) );
    coord unit;
    for ( k = 0; k < 3; ++k ) {
	unit.v[ k ] = v.v[ k ] / norm;
    }
    return unit;
}
