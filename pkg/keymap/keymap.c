#include <stdio.h>
#include <string.h>
#include <xcb/xkb.h>

#include "keymap.h"

int
getkeymapname(char* buf, size_t len)
{
  xcb_connection_t* conn;
  xcb_xkb_get_names_cookie_t cookie;
  xcb_generic_error_t* error;
  xcb_xkb_get_names_reply_t* reply;
  xcb_xkb_get_names_value_list_t res_list;

  conn = xcb_connect(NULL, NULL);
  if (xcb_connection_has_error(conn)) return errorhandler("Could not create XCB connection");

  xcb_xkb_use_extension(conn, XCB_XKB_MAJOR_VERSION, XCB_XKB_MINOR_VERSION);

  cookie = xcb_xkb_get_names(conn, XCB_XKB_ID_USE_CORE_KBD, XCB_XKB_NAME_DETAIL_GROUP_NAMES | XCB_XKB_NAME_DETAIL_SYMBOLS);
  reply = xcb_xkb_get_names_reply(conn, cookie, &error);

  if (error) return cleanup("Could not get the keyboard layout", error, conn);

  const void* buffer = xcb_xkb_get_names_value_list(reply);
  xcb_xkb_get_names_value_list_unpack(buffer, reply->nTypes, reply->indicators, reply->virtualMods, reply->groupNames, 
                                      reply->nKeys, reply->nKeyAliases, reply->nRadioGroups, reply->which, &res_list);

  const char* layout = getatomname(conn, res_list.symbolsName);
  const char* layoutpart = NULL;

  if (layout)
  {
    const char* layoutstart = strchr(layout, '+');

    if (layoutstart)
    {
      const char* layoutend = strchr(layoutstart + 1, '+');

      if (layoutend) layoutpart = strndup(layoutstart + 1, layoutend - layoutstart - 1);

      else layoutpart  = layoutstart + 1;
    }

    else layoutpart = layout;
  }

  snprintf(buf, len, "%s", layoutpart);

  return cleanup(NULL, reply, conn);
}

static int
cleanup(const char* msg, void* ptr, xcb_connection_t* conn)
{
  free(ptr);
  xcb_disconnect(conn);

  if (msg) return errorhandler(msg);
  else return 0;
}

static int
errorhandler(const char* msg)
{
  perror(msg);
  return 1;
}

static const char*
getatomname(xcb_connection_t* conn, xcb_atom_t atom)
{
  char* name;

  xcb_get_atom_name_cookie_t cookie = xcb_get_atom_name(conn, atom);
  xcb_get_atom_name_reply_t* reply = xcb_get_atom_name_reply(conn, cookie, NULL);

  if (reply) name = xcb_get_atom_name_name(reply);
  else name = NULL;

  return name;
}