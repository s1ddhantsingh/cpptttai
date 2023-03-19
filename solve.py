from math import ceil

# function to check if it is possible to satisfy all orders with given number of upgrades
def can_satisfy_all_orders(n, tc, tm, orders, upgrades):
    for i in range(n):
        a, b, c = orders[i]
        time_with_upgrades = a*(tc - upgrades) + b*(tm - upgrades)
        if time_with_upgrades > c:
            return False
    return True

# function to find the minimum number of upgrades required to satisfy all orders
def find_min_upgrades(n, tc, tm, orders):
    # initialize binary search range
    left = 0
    right = max(tc, tm)

    # perform binary search
    while left < right:
        mid = (left + right) // 2
        if can_satisfy_all_orders(n, tc, tm, orders, mid):
            right = mid
        else:
            left = mid + 1

    # return result
    return left if can_satisfy_all_orders(n, tc, tm, orders, left) else -1

# main function to process input and output results
def main():
    t = int(input())
    for _ in range(t):
        n, tc, tm = map(int, input().split())
        orders = [tuple(map(int, input().split())) for _ in range(n)]
        result = find_min_upgrades(n, tc, tm, orders)
        print(result)

# call main function
if __name__ == '__main__':
    main()