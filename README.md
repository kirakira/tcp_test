Introduction
============
This is a simple client/server program. The server has two implementations (server_slow.cc, server_fast.cc), one is 100 times faster than the other, based on my test. However the only difference between the two is that server_slow.cc defined two additional unused variables. Why does that lead to such a huge performance difference?

Usage
=====

    $ make
    $ ./server_slow (or ./server_fast)

    (in another terminal)
    $ time ./client

Test results
============
On my computer (RHEL 6.5, Linux 2.6.32, gcc 4.8.2), the slow version took 3.9 seconds to finish (real 3.961s, user 0.005s, sys 0.004s), while the fast version only took 0.003 seconds (real 0.003s, user 0.000s, sys 0.002s).
