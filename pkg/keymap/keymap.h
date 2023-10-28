#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include <stdlib.h>
#include <xcb/xcb.h>

int
getkeymapname(char* buf, size_t len);

static int
cleanup(const char* msg, void* ptr, xcb_connection_t* conn);

static int
errorhandler(const char* msg);

static const char*
getatomname(xcb_connection_t* conn, xcb_atom_t atom);

#endif