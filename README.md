# RadioHAL: A Radio Hardware Abstraction Layer

RadioHAL is a generic radio abstraction library used by the [RFQuack
framework](https://github.com/trendmicro/rfquack).

RadioHAL is based on RadioHead and, as a matter of fact, it retains most of its
code as it's now in a very initial stage. The reason of the fork is beacause
we'd like to create a library with very few assumption on the packet structure.
For instance, we're not interested in addressing, broadcasting, and all the
other useful features that are necessary if you need to run a sensor network.

For RF analysis, these features could be useful, but are not necessary and most
of the times would make payload analysis harder if not impossible. As we needed
a generic radio abstraction for the [RFQuack
framework](https://github.com/trendmicro/rfquack), I've thought to re-use
RadioHead and fork it under GPLv2.

RadioHAL is not compatible with RadioHead.

## Status
* Support for the TI CC1120 transceiver added and tested
* RFM69 driver modified to remove assumptions on packets structure

All the other drivers are still untouched for now.

## Community
* Slack team: https://join-rfquack-slack.herokuapp.com
* Twitter: https://twitter.com/rfquack
