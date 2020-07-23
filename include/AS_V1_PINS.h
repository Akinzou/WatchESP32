// BME280:     0x76: connected to GND,       0x77: connected to VDDIO
// MAX31341:   The address is 0xD2           (left justified with LSB set to 0).
//ICM-26002:   b1101000: connected to GND,   b1101001: connected to VDDIO
//MAX17055:    0x6C                          (or 0x36 for 7 MSbit address).

#define TFT_DC 4
#define TFT_CS 15
#define TFT_RST 27

#define SPIspeed 40000000L
