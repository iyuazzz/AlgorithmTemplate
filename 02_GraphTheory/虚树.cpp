void get() {
    std::sort(has + 1, has + num + 1, cmp); // sort dfn
	top = 1;
	sta[top] = has[1];
	for (int i = 2; i <= num; ++ i) {
		int now = has[i];
		int lca = LCA(sta[top], now); // 建议使用rmq欧拉序求lca
		while(true) {
			if(dep[lca] >= dep[sta[top - 1]]) {
				if(lca != sta[top]) {
					addedge(lca, sta[top], 0);
					if(lca != sta[top - 1]) sta[top] = lca;
					else -- top;
				}
				break; 
			} else {
				addedge(sta[top - 1], sta[top], 0);
				-- top;
			}
		}
		sta[++ top] = now;
	}
	while(-- top) {
		addedge(sta[top], sta[top + 1], 0);
	}
}