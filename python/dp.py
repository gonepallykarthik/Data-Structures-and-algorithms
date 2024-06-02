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


# print('ans is ', numDecodings("226"))

def equal(A):
    if len(A) == 0:
        return []
    test = []
    res = [-1] * 4
    dict = {  }
    for i in range(0, len(A)):
        for j in range(i+1, len(A)):
            current_sum = A[i] + A[j]
            if current_sum in dict:
                if res[0] == -1:
                    two_indices = dict[current_sum]
                    res[0] = two_indices[0]
                    res[1] = two_indices[1]
                    res[2] = i
                    res[3] = j
                else:
                    two_indices = dict[current_sum]
                    if two_indices[0] < res[0]  or two_indices[1] < res[1] or i < res[2] or j < res[3]:
                        res[0] = two_indices[0]
                        res[1] = two_indices[1]
                        res[2] = i
                        res[3] = j
                
                res1 = [-1] * 4
                two_indices = dict[current_sum]
                res1[0] = two_indices[0]
                res1[1] = two_indices[1]
                res1[2] = i
                res1[3] = j
                test.append( res1 )
                # return [ dict[current_sum], i, j ]
            elif current_sum not in dict:
                dict[current_sum] = []
                dict[current_sum].append(i)
                dict[current_sum].append(j)
    print(res)    
    print(test)
    return [] if res[0] == -1 else res

print(equal([1,1,1,1,1]))
