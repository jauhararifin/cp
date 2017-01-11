#include <bits/stdc++.h>

using namespace std;

int n,m,x,rumah[1001],y,h;
bool ki[1000],ka[1000];

int main(void) {
	memset(rumah, 0, sizeof rumah);
	
	scanf("%d%d%d", &n, &m, &x);
	while (x--) {
		scanf("%d", &y);
		if (y % 2)
			ki[(y-1)/2] = 1;
		else
			ka[(y-1)/2] = 1;
		rumah[(y-1)/2] = ki[(y-1)/2]  + ka[(y-1)/2];
	}
	
	h = 0;
	for (int i = 0; i < max(n,m); i++) {
		if (rumah[i] == 2)
			h++;
		else if (rumah[i] == 1 && rumah[i+1] > 0)
			h++, rumah[i+1]--;
		else if (rumah[i] == 1)
			h++;
		rumah[i] = 0;
	}
	
	printf("%d\n", h);
	
	return 0;
}
