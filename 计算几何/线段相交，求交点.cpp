判线段相交，求交点
bool intersection(point a,point b,point c,point d,point &e)
{
    double d1 = (b-a) * (c-a), d2 = (b-a) * (d-a),
           d3 = (d-c) * (a-c), d4 = (d-c) * (b-c);
    if(sgn(d1)*sgn(d2) > 0)
       return false;
    e = point( (c.x*d2 - d.x*d1) / (d2-d1) , 
               (c.y*d2 - d.y*d1) / (d2-d1) );
    return true;   
}

