import math

with open('input.txt', 'r') as f:
    page = int(f.read())

numberCountList = [0] * 10


def count(page):
    # page的长度
    length = int(math.log10(page) + 1)
    # 最高位
    maxBit = int(page / 10 ** (length - 1))
    for i in range(10):
        numberCountList[i] += maxBit * (length - 1) * 10 ** (length - 2)
    for i in range(maxBit):
        numberCountList[i] += 10 ** (length - 1)
    other = page % 10 ** (length - 1)
    if (other == 0):
        numberCountList[maxBit] += 1
        numberCountList[0] += length - 1
        return
    otherLength =int(math.log10(other)) + 1
    if (other != length - 1):
        numberCountList[0] += (length - 1 - otherLength) * (other + 1)
    numberCountList[maxBit] += other + 1
    return count(other)


length =int(math.log10(page)) + 1
count(page)
numberCountList[0] -= int((10 ** length - 1)/9)
with open('output.txt', 'w') as f:
    for i in range(10):
        f.write(str(int(numberCountList[i])) + '\n')
