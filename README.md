TCasp
=====

Conrad Micallef - 2014 - conradmicallef@gmail.com

DISCLAIMER- This device DOES NOT SAVE YOUR LIFE - use at your own risk, and PLEASE - DO NOT TRUST IT - use your eyes, ears and flight controllers - they are all there to help you.

COPYRIGHT - Code is plublished under GNU license - you're free to copy and use personally, but noc ommercial activity is permitted on this code without express autorisation from author.


Arduino - reference TCAS implementation

This implementation is an adaptation of TCAS for microlight use.

Project requres the use of a Moteino, serial display and GPS

GPS tested is a ublox 7m - connected via softwareserial
Display tested is a serial display (1 wire - serial - using softwareserial

Workings
Using GPS to get longitude and latitude eg 35.1234, 14.4321
drop 35, and 14 and only consider fractional part
convert fractional part fo a number between -32768 and 32767 (numbers chosen on purpose)
using gps calculate angular rate
broadcast position every 3 seconds

if position received
predict upto 30 secuds in the future
locate minimal for altitude match, and x,y match
categorize alert type
display alert

Libraries
using TinyGPS library
using SoftwareSerial library
using RFH69 library

TODO
project is mostly undocumented, first prototype tested 26/11/2014 and initial functions deemed working


