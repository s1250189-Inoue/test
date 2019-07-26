#pragma

// Maximum limit of elements
#define MAX_VERTICES		(16384)
#define MAX_EDGES		(16384)
#define MAX_FACES		(16384)
#define MAX_CORNERS                (64)

// no index
#define	NO_INDEX		   (-1)	

// structure for vertex coordinates
typedef struct {
    double v[ 3 ];		// 3D coordinates
} coord;

// structure for a winged edge
typedef struct {
    int		vidO;		// origin vertex ID of the edge
    int		vidD;		// destination vertex ID of the edge
    int		fidL;		// left face ID
    int		fidR;		// right face ID
} winged;

// structure for a face
typedef struct {
    coord	normal;		// normal vector of the face
    int		eid[ MAX_CORNERS ];
				// ID of an edge on the face
				// (Note that this data structure is
				// inefficient. It is better to implement
				// the wingled-edge or half-edge data
				// structure.
    int		nV;		// number of vertices on the face
} facet;


