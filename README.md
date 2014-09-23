Introduction
============
This is a simple client/server program. The server has two implementations (server_slow.cc, server_fast.cc), one is 100 times faster than the other, based on my test. However the only difference between the two is that server_slow.cc defined two additional unused variables. Why does that lead to such a huge performance difference?

Usage
=====

    $ make
    $ ./server_slow (or ./server_fast)

    (in another terminal)
    $ time ./client
