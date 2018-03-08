struct Point {
	int x, y;
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
};

struct kDTree {
/*
 *	other value
 */
	Point rin, rax;
};

bool operator <= (const Point A, const Point B) {
	return (A.x <= B.x && A.y <= B.y);
}

bool operator >= (const Point A, const Point B) {
	return (A.x >= B.x && A.y >= B.y);
}

bool cmpX(const Point &A, const Point &B) {
	return A.x < B.x;
}

bool cmpY(const Point &A, const Point &B) {
	return A.y < B.y;
}

void build(int p, int tl, int tr, int type) {
	t[p].rin = Point(1<<30, 1<<30);
	t[p].rax = Point(-1<<30, -1<<30);
	for (int i = tl; i < tr; ++ i) {
/*
 *	renew rin rmax
 */
	}
	if (tr - tl == 1) {
/*
 *	consider leaves
 */
		return;
	}
	
	int tm = (tl + tr) >> 1, sl = p * 2, sr = sl + 1;
	sort(a + tl, a + tr, type ? cmpX : cmpY);
	build(sl, tl, tm, type ^ 1);
	build(sr, tm, tr, type ^ 1);
/*
 *	renew node
 */
}

int query(int p, int tl, int tr, Point &qin, Point &qax) {
	if (tr - tl == 1) {
/*
 *	consider leaves
 */
	}
	if (t[p].rin >= qin && t[p].rax <= qax) return //
	if (t[p].rin.x > qax.x || t[p].rax.x < qin.x) return //
	if (t[p].rin.y > qax.y || t[p].rax.y < qin.y) return //
	
	int tm = (tl + tr) >> 1;
	int resl = query(p * 2    , tl, tm, qin, qax);
	int resr = query(p * 2 + 1, tm, tr, qin, qax);
	return //
}
