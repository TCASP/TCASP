#ifndef WIREPROTOCOL_H
#define WIREPROTOCOL_H

struct wireprotocol_t
{
  byte version;
  char callsign[5];
  char type[4];
  short int longitude;//fractional part ddmmss
  short int latitude;//fractional part ddmmss (only +=0.5 - using modular math)
  byte height;//hundreds of feed (0-25500 feet)
  char speedns;//m/s
  char speedwe;//m/s
  char speedz;//feet/sec (-128-127 feet/sec ie-7680 to 7620 feet per min) 
  char arate;//rotation degrees/sec * 10
};
#define wp_size sizeof(wireprotocol_t)
#define V1 49
#endif

