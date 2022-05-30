import sys
import random

MAX_VALUE = 1000000
MIN_VALUE = 0

if __name__ == '__main__':
    rows = int(sys.argv[1])
    for i in range(rows):
        print(str(random.randint(MIN_VALUE, MAX_VALUE)) + " ")
