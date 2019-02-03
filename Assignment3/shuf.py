#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, inputLines, inputRange, headCount, repeat, args):
        self.inputRange = inputRange
        self.repeat = repeat
        self.inputLines = inputLines
        self.length = len(inputLines)
        self.forever = False
        self.headCount = headCount
        if headCount == None and repeat:
            self.forever = True
        elif headCount == None and not repeat:
            self.headCount = self.length
        elif headCount > len(self.inputLines) and not repeat:
            self.headCount = self.length

    def printPerm(self):
        if self.length == 0 or self.headCount == 0:
            return
        if self.forever:
            while(True):
                index = int(random.random() * self.length)
                sys.stdout.write(self.inputLines[index])
                if self.inputRange != None:
                    sys.stdout.write("\n")
            return
        if not self.repeat:
            indexes = random.sample(range(self.length), self.headCount)
            for i in indexes:
                sys.stdout.write(self.inputLines[i])
                if self.inputRange != None:
                    sys.stdout.write("\n")
            return
        if self.repeat:
            for t in range(self.headCount):
                index = int(random.random()*self.length)
                sys.stdout.write(self.inputLines[index])
                if self.inputRange != None:
                    sys.stdout.write("\n")
            return

def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... [FILE]
  or:  shuf.py -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.
    
With no FILE, or when FILE is -, read standard input."""

    # Parse option flags
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-i", "--input-range", action="store", dest="range",
                      help='treat each number in RANGE (Where RANGE is "LO-HI") as an input line')
    parser.add_option("-n", "--head-count", action="store", dest="count",
                      help="output at most COUNT lines. (Default: all input lines are outputted)")
    parser.add_option("-r", "--repeat", action="store_true", dest="repeat",
                      default=False, help="output lines can be repeated (Default False)")
    
    options, args = parser.parse_args(sys.argv[1:])

    # Handle -n option
    if options.count != None:
        try:
            headCount=int(options.count)
        except:
            parser.error("invalid line count: '{0}'".format(options.count))
        if headCount == 0:
            return
        elif headCount < 0:
            parser.error("invalid line count: '{0}'".format(options.count))
    else:
        headCount = options.count
            
            
    # Handle -r option
    try:
        repeat=bool(options.repeat)
    except:
        parser.error("invalid repeat boolean: '{0}'".format(options.repeat))

    # Handle -i option
    try:
        inputRange=options.range
    except:
        parser.error("invalid input range: '{0}'".format(options.range))
    # If -i flag is used, no file may be inputted as an argument
    if inputRange != None and len(args) > 0:
        parser.error("extra operand '{0}'\nTry 'shuf.py --help' for more information.".format(options.range))
    # Check for valid range format
    if inputRange != None:
        dash = False
        first = ""
        second = ""
        for char in inputRange:
            if char == "-" and first == "": #If dash comes before first int
                parser.error("invalid input range: '{0}'".format(options.range))
            if char == "-" and dash: #If char is the second dash
                parser.error("invalid input range: '{0}'".format(options.range))
            if char == "-" and not dash: #If char is 1st dash, set dash to True
                dash = True
                continue
            if not char.isdigit(): #If any character besides dash is not digit
                parser.error("invalid input range: '{0}'".format(options.range))
            if not dash: #Record numbers
                first = first + char
            else:
                second = second + char
        if second == "": #If no number came after the dash
            parser.error("invalid input range: '{0}'".format(options.range))
        try:
            first = int(first)
            second = int(second)
        except:
            parser.error("invalid input range: '{0}'".format(options.range))
        if first > second:
            parser.error("invalid input range: '{0}'".format(options.range))

    # Handle file input/stdin/"-" arguments
    if len(args) > 1:
        parser.error("extra operand '{0}'".format(args[1]))
    if inputRange != None:
        inputLines = list(map(str,range(first, second+1)))
    elif len(args) == 0 or (len(args) == 1 and args[0] == "-"):
        inputLines = sys.stdin.readlines()
    else:
        try:
            inputFile = open(args[0], 'r')
            inputLines = inputFile.readlines()
            inputFile.close()
        except IOError as e:
            errno = e.errno
            strerror = e.strerror
            parser.error("I/O error({0}): {1}".format(errno, strerror))
            
    #Generate and print randomly shuffled lines
    generator = shuf(inputLines, inputRange, headCount, repeat, args)
    generator.printPerm()
    
if __name__ == "__main__":
    main()
