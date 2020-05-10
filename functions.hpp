#define EPSILON 0.000001
#define CROSS(dest, v1, v2) dest[0] = v1[1]*v2[2]-v1[2]*v2[1]; dest[1] = v1[2]*v2[0]-v1[0]*v2[2]; dest[2] = v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1, v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest, v1, v2) \
    dest[0] = v1[0]-v2[0]; \
    dest[1] = v1[1]-v2[1]; \
    dest[2] = v1[2]-v2[2];
int intersect_triangle(int orig[3], double dir[3], int vert0[3], int vert1[3], int vert2[3]){
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det;
    double t,u,v;
    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);
    CROSS(pvec, dir, edge2);
    det = DOT(edge1, pvec);
    if (det > -EPSILON && det < EPSILON)
        return -1.0;
    SUB(tvec, orig, vert0);

    u = DOT(tvec, pvec) / det;
    if (u < 0.0 || u > 1.0)
        return -1.0;
    CROSS(qvec, tvec, edge1);
    v=DOT(dir, qvec) / det;
    if (v < 0.0 || u + v > 1.0)
        return -1.0;
    t=DOT(edge2, qvec) / det;
    return t;
}
