inline void addedge(int u, int v, int c);
inline int	build();
inline void	dinic(int u);


for (off = t; ; )
	if (build())
		dinic(s);
			else break;


inline void addedge(int u, int v, int c) {
	w[++ W].v = v; w[W].c = c; w[W].next = ww[u]; ww[u] = W;
	w[++ W].v = u; w[W].c = 0; w[W].next = ww[v]; ww[v] = W;
}

inline int build() {
	int	fi, la;
	memset(dist, 0, sizeof(dist)); dist[que[la = 1] = s] = 1;
	for (fi = 1; fi <= la; ++ fi) {
		int	u = que[fi];
		for (int i = ww[u]; i; i = w[i].next) if (w[i].c) {
			int	v = w[i].v;
			if (dist[v]) continue;
			dist[v] = dist[u] + 1; que[++ la] = v;
			if (v == t) return 1;
		}
	}
	return 0;
}

inline void dinic(int u) {
	if (u == t) {
		int	flow = 1 << 30;
		for (int i = t; i != s; i = w[stq[i] ^ 1].v) flow = min(flow, w[stq[i]].c);
		for (int i = t; i != s; i = w[stq[i] ^ 1].v) {
			w[stq[i]].c -= flow; w[stq[i] ^ 1].c += flow;
			if (!w[stq[i]].c) off = w[stq[i] ^ 1].v;
		}
		maxflow += flow;
		return;
	}
	for (int i = ww[u]; i; i = w[i].next) if (w[i].c) {
		int	v = w[i].v;
		if (dist[v] != dist[u] + 1) continue;
		stq[v] = i; dinic(v);
		if (dist[u] > dist[off]) return;
		off = t;
	}
	dist[u] = -1;
}