#ifndef _XORG_H_
#define _XORG_H_

#include <stdlib.h>
#include <xcb/xcb.h>

int
setstatbar(const char* stat);

static int
basicerrorhandler(const char* errormsg);

static int
xcberrorhandler(xcb_generic_error_t* error, const char* errormsg, int errorcode);

#endif
