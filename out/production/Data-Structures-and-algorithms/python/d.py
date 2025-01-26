
def some(A : str):
    arr = A.split('$')
    result_arr = []
    for word in arr:
        if word:
            length = int(word[-1])
            word_without_digit = word[:-1]  # Exclude the last character (digit)
            word_length = len(word_without_digit)
            print("word is", word_without_digit, "and length is", length)
            if length == word_length:
                result_arr.append(word)
    
    print(result_arr)
    return result_arr
some("grapes6$Mango6$Apple5$")

def countOddEvenLengthWords(A):
    if len(A) == 0:
        return []
    
    odd_len = 0
    even_len = 0
    
    arr = A.split(" ")
    print(arr)
    for word in arr:
        if len(word) > 0 and len(word) % 2 == 0:
            even_len +=1
        else:
            odd_len += 1
    
    return [odd_len, even_len]

print(countOddEvenLengthWords("a a "))

def modifyArrayBasedOnNext(A):
    if len(A) == 0:
        return 0
    
    i = 0
    res = []
    while i < len(A):
        if i == len(A) - 1:
            res.append(A[i])
            break
        
        if A[i] < A[i+1]:
            # merge two
            res.append(A[i] + A[i+1])
            i += 2
        else:
            res.append(A[i])
            i += 1
    
    return res

print(modifyArrayBasedOnNext([1,2,3,2,5,4,7,6]))
