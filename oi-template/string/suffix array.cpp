void suffixSort() {
	s[n++] = 'z' + 1;
	int m = 27;
	for (int i = 0; i < m; i++) cnt[i] = 0;
	for (int i = 0; i < n; i++) cnt[rk[i] = s[i] - 'a']++;
	for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0 ; i--) sa[--cnt[rk[i]]] = i;
	for (int l = 1, p = 0; p < n; m = p, l *= 2) {
		p = 0;
		for (int i = n - l; i < n; i++) tmp[p++] = i;
		for (int i = 0; i < n; i++) if (sa[i] >= l) tmp[p++] = sa[i] - l;
		for (int i = 0; i < m; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) cnt[rk[tmp[i]]] ++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
		swap(tmp, rk);
		rk[sa[0]] = 0;
		for (int i = p = 1; i < n; i++)
			rk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + l] == tmp[sa[i - 1] + l]) ? p - 1 : p++;
	}
	for (int i = 0; i < n; ++i) rk[sa[i]] = i;
	for (int i = 0, k = 0; i < n; height[rk[i++]] = k) {
		k = k ? k - 1 : 0;
		if (!rk[i]) continue;
		for (int j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
	}
	n--;
}
