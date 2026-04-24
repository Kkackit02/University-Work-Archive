n = int(input())

count = 0

coin_types = [500, 100, 50, 10, 5, 1]

for coin in coin_types:
    count += n // coin
    # 해당 화페로 거슬러 줄 수 있는 동전의 갯수 세기
    n %= coin
print(count)
