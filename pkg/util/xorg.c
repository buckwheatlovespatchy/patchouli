#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>

#include "xorg.h"

int
setstatbar(const char* stat)
{
  xcb_connection_t* connection = xcb_connect(NULL, NULL);

  if (xcb_connection_has_error(connection)) return basicerrorhandler("Could not create connection");

  xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  xcb_window_t statbar = screen->root;
  
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, statbar, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(stat), stat);
  xcb_flush(connection);

  xcb_generic_error_t* error = xcb_request_check(connection, 
    xcb_change_property_checked(connection, XCB_PROP_MODE_REPLACE, statbar, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(stat), stat));

  if (error) return xcberrorhandler(error, "Could not change property", error->error_code);

  xcb_disconnect(connection);

  return 0;
}

static int
basicerrorhandler(const char* errormsg)
{
  perror(errormsg);
  return 1;
}

static int 
xcberrorhandler(xcb_generic_error_t* error, const char* errormsg, int errorcode)
{
  size_t perrormsglen = 50
  char perrormsg[perrormsglen];

  snprintf(perrormsg, perrormsglen, "%s - Error Code: %d\n", errormsg, errorcode);
  perror(perrormsg);
  free(error);
  return 1;
}
