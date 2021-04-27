#!/bin/python
import sys
from collections import Counter

argc = len(sys.argv)

if argc != 2:
    print("Usage: " + sys.argv[0] + " stack_data")
    exit(1)

with open(sys.argv[1], 'r') as stack_data:
    lines = [x[:-2] for x in stack_data.readlines()]
    lines = sorted(lines)
    sample_rates = dict(Counter(lines).items())
    
    for key, value in sample_rates.items():
        print(key + " " + str(value))


