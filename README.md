# snyder

[![Build Status](https://travis-ci.org/mrtazz/snyder.svg?branch=master)](https://travis-ci.org/mrtazz/snyder)
[![Packagecloud](https://img.shields.io/badge/packagecloud-available-green.svg)](https://packagecloud.io/mrtazz/snyder)

## Overview

Snyder is a metrics library for C++11. It supports tracking of a number of
metric types from different threads.

## Usage
```cpp
auto reg = new Snyder::MetricsRegistry();
reg->Increment("foo");
reg->Increment("foo", 5);
reg->Gauge("bla", 10);

// get a snapshot and clear out metrics
auto snapshot = reg->Snapshot();
reg->Reset();
```

## Metrics Types
- counters: a monotonic increasing count
- gauge: simple value tracking

## Installation
It's autotools, so:
```
./autogen.sh
./configure
make install
```

## Etymology
Snyder is named after [Betty Snyder][betty_snyder], one of the six original
programmers of [ENIAC][eniac], who is credited with inventing breakpoints for
debugging.



[betty_snyder]: https://en.wikipedia.org/wiki/Betty_Holberton
[eniac]: https://en.wikipedia.org/wiki/ENIAC
