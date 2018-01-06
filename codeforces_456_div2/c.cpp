#include <bits/stdc++.h>

using namespace std;

typedef struct {
	int max_health;
	int start_health;
	int regen;
} enemy;

typedef struct {
	int time;
	int e;
	int health;
} event;

int n,m,bounty,increase,damage;
enemy e[100000];
event v[100000];
pair<int,int> last_update[100000]; // time, health

bool cmp(event a, event b) {
	return a.time < b.time;
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d%d", &bounty, &increase, &damage);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &e[i].max_health, &e[i].start_health, &e[i].regen);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &v[i].time, &v[i].e, &v[i].health), v[i].e--;
	
	for (int i = 0; i < n; i++)
		if (e[i].max_health <= damage && increase > 0) {
			printf("-1\n");
			return 0;
		}

	sort(v, v + m, cmp);
	map<long long,int> ev;
	for (int i = 0; i < n; i++) {
		if (e[i].start_health <= damage)
			ev[0]++;
		last_update[i] = make_pair(0, e[i].start_health);
	}

	for (int i = 0; i < m; i++) {
		if (v[i].health <= damage && last_update[v[i].e].second > damage) {
			ev[v[i].time]++;
		}
		if (last_update[v[i].e].second <= damage) {
			long long after_damage = 10000000000LL;
			if (e[v[i].e].regen > 0)
				after_damage = (damage - last_update[v[i].e].second) / e[v[i].e].regen + 1 + last_update[v[i].e].first;
			if (after_damage >= v[i].time && v[i].health > damage) {
				ev[v[i].time]--;
			}
			if (after_damage < v[i].time) {
				ev[after_damage]--;
				if (v[i].health <= damage) {
					ev[v[i].time]++;
				}
			}
		}
		last_update[v[i].e] = make_pair(v[i].time, v[i].health);
	}
	for (int i = 0; i < n; i++)
		if (last_update[i].second <= damage) {
			long long after_damage = 10000000000LL;
			if (e[i].regen <= 0) {
				if (increase > 0) {
					printf("-1\n");
					return 0;
				}
			} else
				after_damage = (damage - last_update[i].second) / e[i].regen + 1 + last_update[i].first;
			ev[after_damage]--;
		}

	long long n = 0, h = 0;
	for (auto i = ev.begin(); i != ev.end(); i++) {
		if (i->second > 0)
			n += i->second;
		else if (i->second < 0) {
			h = max(h, (long long) n * (long long) (bounty + increase * (i->first - 1LL)));
			n += i->second;
		}
	}
	printf("%lld\n", h);

	return 0;
}