print('welcome')

def numDecodings(s:str):
    if len(s) == 0:
        return 0
    return numDecodingsHelper(0, s)

def numDecodingsHelper(idx, s):
    # if idx > len(s):
        # return 0

    if idx >= len(s):
        return 1
    
    oneCharacterString = s[idx]
    print('one character ', oneCharacterString)
    r1 = 0
    n = int(oneCharacterString)
    if n >= 1 and n <= 26:
        r1 = numDecodingsHelper(idx + 1, s)

    r2 = 0
    TwoCharcterString = s[idx : idx+2]
    print('two', TwoCharcterString, idx, idx+3)
    n1 = int(TwoCharcterString)
    if 1 >= n1 and n1 <= 26:
        r2 = numDecodingsHelper(idx +2, s)
    
    return r1 + r2


print('ans is ', numDecodings("226"))