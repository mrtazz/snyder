---\nlayout: project\ntitle: restclient-cpp\n---
# snyder

[![Build Status](https://travis-ci.org/mrtazz/snyder.svg?branch=master)](https://travis-ci.org/mrtazz/snyder)
[![Packagecloud](https://img.shields.io/badge/packagecloud-available-brightgreen.svg)][pkgcloud]
[![Coverage Status](https://coveralls.io/repos/mrtazz/snyder/badge.svg?branch=master&service=github)](https://coveralls.io/github/mrtazz/snyder?branch=master)

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
For Linux there are packages available on [packagecloud][pkgcloud].

It's autotools, so for everything else there's this:

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
[pkgcloud]: https://packagecloud.io/mrtazz/snyder
