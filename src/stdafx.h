// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

#ifdef ARDUINO
#include "Arduino.h"
#include <stdlib.h>
#else
#include "targetver.h"

#include <WinSock2.h>
#include <stdio.h>
#include <tchar.h>
#include "emuino.h"
#pragma comment (lib, "ws2_32")

#endif

#include <string.h>

const double pi=3.1415926;

// TODO: reference additional headers your program requires here
#endif
