#!/bin/sh
#svn status -u $1 | sed -n 's/^[ \]*Status contra revis?o:[ \t]*\([0-9][0-9\.]*\).*/\1/p'

svn stat -v $1 | sed -n 's/^[ A-Z?\*|!]\{1,15\}/r/;s/ \{1,15\}/\/r/;s/ .*//p'
