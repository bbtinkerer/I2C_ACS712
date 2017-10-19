# I2C ACS712

By bbtinkerer (<http://bb-tinkerer.blogspot.com/>)

## Description
Attiny85 program that returns the current RMS value of two ACS712 sensors via I2C. Returns 4 bytes (2 bytes per sensor MSB formatted) representing the current values in milliamps. The first 2 bytes for the first sensor and last two bytes for the second sensor. 

## Configuration

Burn ATtiny85 with fuses:

| Fuse Register  | Value |
|----------------|-------|
| Extended       | 0xFF  |
| High           | 0xD7  |
| Low            | 0xE2  |

Default I2C addresses selected by Pin 6

| PIN 6 | Address |
|-------|---------|
| GND   | 0x08    |
| VCC   | 0x09    |

(don't forget the 10K resistor when connecting to VCC)

Connect the first ACS712 sensor to Pin 3 and second sensor to Pin 2.

Update MAINS_FREQUENCY to your frequency and change the first argument of the ACS712 constructor to your sensor.

## Usage

Use Atmel Studio 7 to build and flash to your microcontroller. Alternatively, build and flash with your favorite AVR tool chain and programmers.

### Known Issues

If you discover any bugs, feel free to create an issue on GitHub fork and
send a pull request.


## Authors

* bbtinkerer (https://github.com/bbtinkerer/)


## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request


## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.