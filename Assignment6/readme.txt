Brendon Ng
304-925-492
UCLA CS 35L Lab 3
TA Guangyu Zhou

Assignment 6: Multithreaded Performance

Homework: After-Action Report

Some problems I ran into were understanding how the code in main.c worked. Of
course the code there is beyond the scope of this class, but it took me a while
to find where to make parallel processes. Also, I had a big issue run-time
because I had a variable named "num" and I did not know that it was a reserved
name. My code ran on an endless loop because of that until I changed the name
to something else. Another thing that was tricky was figuring out how to print
all of the pixels. I had to store them in one global place because I could not
print as the function ran because there were multiple threads going at once, so
I stored everything in a 3-D array and printed it at the very end.

Conclusion:
The multithreaded version produced the following output:
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m41.039s
user	0m41.009s
sys	0m0.001s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m21.816s
user	0m42.983s
sys	0m0.004s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m11.166s
user	0m44.137s
sys	0m0.003s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.724s
user	0m44.291s
sys	0m0.004s
mv 8-test.ppm.tmp 8-test.ppm

As we can see, multithreading imporves the performance. The more threads we use
the faster our program runs. Doubling the amount of threads approximately cuts
the time in half. This is because the processes can run concurrently, making it
much faster.
