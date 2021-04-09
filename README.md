# Simple 128bit integer library for Q

This is a C extension to KDB+/Q making GCC's ___int128_ type available in Q as a guid.

## Build and Load

Build with _make_, load with _\l i128.q_.

## Converting to/from
```
q) i128.parse "12345678910111213141516"
0cbe8b32-8956-b642-9d02-000000000000
q) i128.parse 38#"9"
ffffffff-3f22-8a09-7ac4-865aa84c3b4b
q) i128.cast 0 -1 0Wj
00000000-0000-0000-0000-000000000000 ffffffff-ffff-ffff-ffff-ffffffffffff ffffffff-ffff-ff7f-0000-000000000000
q) i128.cast .z.p
90d91c44-a0f4-5009-0000-000000000000
q) {x}i:i128.mul . i128.cast 256 0Wj
00ffffff-ffff-ffff-7f00-000000000000
q) (i128.low;i128.high)@\: i
-256 127
q) i128.str i
"2361183241434822606592"
```
_cast, low, high, str_ are all atomic.

## Operators
Available operators _add, sub, mul, div, mod, lt_ are all atomic.
```
q) i128.str (i128.mul/) i128.cast 1+til 33
"8683317618811886495518194401280000000"
q) i128.str i128.mul . i128.cast (10 20;(3 4;50 60))
"30"   "40"
"1000" "1200"
q) i128.lt[rand 0Ng;5 10#50?0Ng]
0001101111b
1000000000b
1100101000b
0000010110b
1011011110b
```
