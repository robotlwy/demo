s = list(input())
length = len(s)
num = 0
def strNumber(s):
    length = len(s)
    num = 0
    while (length != 1):
        #至少让最后两个字母连续
        index = length - 1
        num += ord(s[index]) - ord(s[index - 1])
        s[index] = chr(ord(s[index - 1]) + 1)
        # 找到连续字母串的第一个
        while s[index] == chr(ord(s[index - 1]) + 1):
            index -= 1
        #如果第一个字母为a,则将列表长度减一,从后往前赋字母逆序(从z开始)
        if s[index] == 'a':
            for i in range(1, length):
                s[i] = chr(ord('z') - length + 1 + i)
            s = s[1:]
            length -= 1
        #否则将连续字母串的第一个字母ASCII减一,其他的从后往前赋字母逆序(从z开始)
        else:
            s[index] = chr(ord(s[index]) - 1)
            for i in range(index + 1, length):
                s[i] = chr(ord('z') - length + i + 1)
        # 不能这样 因为有length-1的情况
        # for i in range(index+1, length):
        #     s[i] = chr(ord('z') - length + 1 + i) 
    num += ord(s[0]) - ord('a') + 1
    return num
print(strNumber(s))
