
import sys

def pow(base, exp):

    result = 1

    while True:
        if (exp & 1):
            result *= base
        exp >>= 1

        if (exp <= 0):
            break

        base *= base

    return result

def logbase10(num):
    string = str(num)
    if str == '0':
        return "ERROR"

    return len(string) - 1

def rational(numerator, denominator):
    if denominator == 0:
        return "ERROR"

    string = ""

    numdigits = 130
    stringindex = 0
    facevalue = 0
    power = logbase10(int(numerator // denominator))
    result = int(numerator // denominator)
    tentopow = pow(10, power)

    while power > 0 and numdigits > 0:
        facevalue = str(int(result // tentopow) % 10)
        power -= 1
        numdigits -= 1
        string += facevalue
        tentopow = pow(10, power)

    if numdigits > 0:
        facevalue = str(result % 10)
        numdigits -= 1
        string += facevalue

    if numdigits > 0:
        string += '.'

        while numdigits > 0:
            numerator *= 10
            result = int(numerator // denominator)
            facevalue = str(result % 10)
            numdigits -= 1

            string += facevalue

    return string

if len(sys.argv) == 3:
    numerator = int(sys.argv[1])
    denominator = int(sys.argv[2])
    print(rational(numerator, denominator))
