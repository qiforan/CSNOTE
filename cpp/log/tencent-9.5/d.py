mp = {}

def get_len(x):
	if x in mp:
		return mp.get(x)
	if x == 1 or x == 0:
		mp[x] = 1
		return 1
	temp = get_len(x//2)
	mp[x] = temp * 2 + 1
	return mp[x]

def get_one(l,r,k):
	if l > r:
		return 0
	len = get_len(k)
	mid = len // 2
	if l == 0 and r == len -1:
		return k
	if l > mid:
		return get_one(l-mid-1, r-mid-1, k // 2)
	elif r < mid:
		return get_one(l ,r, k // 2)
	elif k % 2 == 1:
		return 1 + get_one(l,mid-1,k//2) + get_one(0,r-mid-1, k // 2)
	else:
		return get_one(l,mid-1,k//2) + get_one(0,r-mid-1, k // 2)


def main():
	n = int(input())
	l = int(input())
	r = int(input())
	print(get_one(l-1,r-1,n))

main()