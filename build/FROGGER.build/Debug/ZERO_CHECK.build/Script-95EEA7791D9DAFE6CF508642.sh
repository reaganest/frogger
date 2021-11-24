#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/reaganesteves/Documents/GitHub/frogger/build
  make -f /Users/reaganesteves/Documents/GitHub/frogger/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/reaganesteves/Documents/GitHub/frogger/build
  make -f /Users/reaganesteves/Documents/GitHub/frogger/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/reaganesteves/Documents/GitHub/frogger/build
  make -f /Users/reaganesteves/Documents/GitHub/frogger/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/reaganesteves/Documents/GitHub/frogger/build
  make -f /Users/reaganesteves/Documents/GitHub/frogger/build/CMakeScripts/ReRunCMake.make
fi

