#!/usr/bin/python

import os
import sys
import subprocess
import random
import re
import math

# Performs Tarantula processing on dominion.c using the test in minion_tarantula.c
def main():

    DEBUG = False

    linestatus = {}
    numtests = 100
    totalfails = 0

    random.seed()

    for i in xrange(0, numtests):
        subprocess.call(["rm", "dominion.gcda"])
        seed = str(random.randint(0, 10000000))
        if DEBUG:
            print "seed: " + seed
        outpipe = subprocess.Popen(["./minion_tarantula.out", seed], stdout=subprocess.PIPE)
        teststatus = int(outpipe.stdout.read()[0])
        if DEBUG:
            print "test status: " + str(teststatus)
        subprocess.call(["gcov", "dominion.c"], stdout=open("/dev/null", "w"))

        infile = open("dominion.c.gcov", "r");

        totalfails += teststatus

        for line in infile:
            linenumber = int(re.sub(r'.*?:\s*(\d+):.*', r'\1', line))
            covered = True
            try:
                coveredtimes = int(re.sub(r'\w*(.*?):\s*\d+:.*', r'\1', line))
            except ValueError:
                covered = False
            if linenumber != 0:
                if linenumber not in linestatus:
                    linestatus[linenumber] = [0, 0] # passes, fails
                if covered:
                    linestatus[linenumber][teststatus] += 1

    totalpasses = numtests - totalfails

    if totalpasses == 0:
        print "All tests failed"
    elif totalfails == 0:
        print "All tests succeeded"
    else:
        print "Suspicious lines:"
        for line, status in linestatus.iteritems():
            passes = status[0]
            fails = status[1]
            if passes != 0 or fails != 0: # Don't divide by zero
                susp = (1.0 * fails / totalfails) / ( (1.0 * passes / totalpasses) + (1.0 * fails / totalfails) )
                if susp > 0:
                    print "%4.d:\t%.2f\t%s" % (line, susp, "#" * int(math.floor(susp * 50)))
                    if DEBUG:
                        print "\t\tFails: {0}\tPasses: {1}".format(fails, passes)
        if DEBUG:
            print "Total fails: {0}\tTotal passes: {1}\tTotal tests: {2}".format(totalfails, totalpasses, numtests)

if __name__ == '__main__':
    main()
