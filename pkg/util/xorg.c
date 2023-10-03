#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>

#include "xorg.h"

static int 
errorhandler(char* errormsg, int errorcode)
{
  printf("%s - Error Code: %d\n", errormsg, errorcode);
  return 1;
}

int
setstatbar(char* stat)
{
  xcb_connection_t* connection = xcb_connect(NULL, NULL);

  if (xcb_connection_has_error(connection)) return 1;

  xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  xcb_window_t statbar = screen->root;
  
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, statbar, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(stat), stat);
  xcb_flush(connection);

  xcb_generic_error_t* error = xcb_request_check(connection, 
    xcb_change_property_checked(connection, XCB_PROP_MODE_REPLACE, statbar, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(stat), stat));

  if (error)
  {
    int errcode = errorhandler("ERROR: Could not change property", error->error_code);
    free(error);
    return errcode;
  }

  xcb_disconnect(connection);

  return 0;
}
