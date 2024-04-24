# print("hello welcome application")


"""
2163 -> 3 ways to decode
"""
def waysToDecode(str):
    if len(str) == 0:
        return 0 

    if len(str) == 1 and str[0] == '0':
        return 0
    
    n = len(str)
    dp = [0] * (n+1)
    dp[0] = 1
    dp[1] = 1

    for i in range(2, n+1):
        if int(str[i-1]) >=1 and int(str[i-1]) <= 9:
            dp[i] = dp[i-1]
        
        if int(str[i-2]) == 1:
            dp[i] += dp[i-2]
        elif int(str[i-2]) == 2 and int(str[i-1]) >=0 and int(str[i-1]) <= 6:
            dp[i] += dp[i-2]
    
    print(dp)
    return dp[n]


print(waysToDecode("0799733"))
# print(waysToDecode("11"))
