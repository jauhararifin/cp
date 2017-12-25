n = int(input())
a = [int(x) for x in input().split(" ")]

def init_map():
	mp = {}
	for x in a:
		mp[x] = mp[x+1] = mp[x-1] = 0
	return mp

mp = init_map()
result = 0
for m, v in enumerate(a):
	result += v * (m - mp[v] - mp[v-1] - mp[v+1])
	mp[v] += 1
mp = init_map()
for m, v in enumerate(a[::-1]):
	result -= v * (m - mp[v] - mp[v-1] - mp[v+1])
	mp[v] += 1

print(result)