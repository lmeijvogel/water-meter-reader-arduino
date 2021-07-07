# Summary

This sketch reads the state of the analog pin: Every time it transitions to `up`,
it prints `USAGE: <val>` to the Arduino's serial port, with `<val>` being the actual
value read from the analog pin.

It also sends periodic `TICK: <val>` messages, so the receiver knows that the sensor
is still running.

# Details

A `USAGE` message is sent for each transition `down` => `up`. Even if the signal remains
`up`, the `USAGE` message is not repeated. `TICK` messages *are* sent.

If the signal goes `down` again, no explicit message is sent (only the `TICK`s).

If the signal transitions from `down` => `up` in quick succession, a `USAGE` message
is sent for each of them (barring debouncing and cycle time: each loop has a `delay(20)`,
so with `DEBOUNCE_MAXIMUM=5`, the minimum response time for a transition is 100ms for `up`
and an additional 100ms for `down`.

A repeated signal is therefore only detected if it occurs at least 200ms after the preceding one.

## Configuration in source

Configured in source:
- default analog pin: `A0`
- default signal threshold: `400` (above what value is the signal on the pin considered `up`)
- default tick interval: `2000` (Send a `TICK` message if no transitions for 2000ms)
- default debounce maximum: `5` (Maximum value for Kuhn's algorithm for debouncing buttons)

## Installation

For /dev/ttyACM0 to be visible on a Raspberry Pi, enable the serial interface from `raspi-config`:
- Interfacing Options
- Serial
- Would you like a login shell to accessible over serial => NO
- Enable serial interface => YES

Connecting the sensor to the Arduino:
- 5V:  Red
- GND: Black
- A0:  Yellow
