//--------------------geometry--------------------

template<class T>struct Point{T x,y;};
template<class T>inline Point<T> operator+(Point<T> a,Point<T> b){a.x+=b.x;a.y+=b.y;return a;}
template<class T>inline Point<T> operator-(Point<T> a,Point<T> b){a.x-=b.x;a.y-=b.y;return a;}
template<class T>inline Point<T> operator*(Point<T> a,T k){a.x*=k;a.y*=k;return a;}
template<class T>inline Point<T> operator/(Point<T> a,T k){a.x/=k;a.y/=k;return a;}
template<class T>inline T det(T a,T b,T c,T d){return a*d-b*c;}
template<class T>inline T dot(T a,T b,T c,T d){return a*c+b*d;}
template<class T>inline T det(Point<T>&a,Point<T>&b){return a.x*b.y-a.y*b.x;}
template<class T>inline T dot(Point<T>&a,Point<T>&b){return a.x*b.x+a.y*b.y;}
inline int cmp(double a,double b){return(fabs(a-b)<1e-10)?0:(a<b?-1:1);}
inline void rotate(Point<double>&a,double th){Point<double>b;b.x=a.x*cos(th)-a.y*sin(th);b.y=a.x*sin(th)+a.y*cos(th);a=b;}

//--------------------geometry--------------------
