#!/bin/sh

ARG=$1
ARGC=$#
GNU_MUSL_PATH=/usr/bin/musl-clang

help_menu()
{
  printf "\033[1mChansoft Builder\033[0m\nA POSIX-compliant way to build software cross-platform\n"
  printf "\n\033[1mUsage:\033[0m\n    ./builder [arg]\n"
  printf "\n\033[1mArgs:\033[0m\n    install - Install the bundled software, automatically detects your OS, performs necessary cleanups after install\n    remove - Removes any installed versions of the software and cleans up the leftover files\n"
}

install()
{
  OS=$(uname -s)

  case "$OS" in
    "FreeBSD")
      make freebsd install clean
    ;;

    "Linux")
      if [ -x $GNU_MUSL_PATH ]; then
        make linux install-gnu clean
      else
        make linux install clean
      fi
    ;;

    "NetBSD")
      make netbsd install clean
    ;;

    "OpenBSD")
      make openbsd install clean
    ;;

    *)
      printf "Unsupported OS detected, exiting.\n"
      exit 1
    ;;

  esac
}

main()
{
  if [ "$ARGC" -gt "1" ]; then
    printf "Too many arguments provided, please check argument count.\n"
    exit 1
  fi

  case "$ARG" in
    "install")
      install
    ;;

    "remove")
      make remove clean
    ;;

    "help" | "")
      help_menu
    ;;

    *)
      printf "Unknown argument %s\n" "$ARG"
    ;;
  
  esac
}

main
