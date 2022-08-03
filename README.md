Programmers use [binary numbers](https://en.wikipedia.org/wiki/Binary_number)
all the time, that's probably why there are a bunch of binary clocks available,
however, they simply translate a standard time `02:04` to it's equivalent in
binary: `0b10:100` which doesn't leverage the power of the binary numeral
system.

The whole point of the binary numeral system is that digits are **powers of 2**.
So if you take `0b10000` and divide it by 2 enough times, eventually you'll get
2 (in this case 3 times).

This is useful because you can quickly find out what is the double of `0b10`:
just shift: `0b100`, and what's half: `0b1`.

If you use a format like `0b10:100` you can't do that, because `0b101:000` is
not the double of `02:04`, it's `05:00`.

A true (actually true) binary clock would leverage **powers of 2**.

If a day is `0b10000`, half a day would obviously be `0b01000`, and a quarter of
a day `0b00100`. Obviously a 16th of a day would be `0b00001`.

Binary numbers can be easily represented in hexadecimal; day: `0x10`, half:
`0x8`, quarter: `0x4`, 16th: `0x1`.

This is [hexadecimal time](https://en.wikipedia.org/wiki/Hexadecimal_time),
which is much more powerful than standard time.

Two digits give you more than enough information about the current time, similar
to four digits of standard time.

Right now my time is `0xAF`, so I know I'm less than 6 minutes away from `0xB0`
(`16:30`), since `0xAF` is `16:24`, actually, it's `16:27`, but I don't care:
`0xB0` is close enough for me.

To watch a day go by in hexadecimal time check this
[online hexclock simulation](https://felipec.github.io/hexclock/?test=true).
