#!/bin/fish

set BASE_DIR (dirname (readlink -m (status filename)))/..
set SCRIPTS_DIR (dirname (readlink -m (status filename)))

set build_dir "$BASE_DIR/build"

cd "$BASE_DIR"

rm -r "$build_dir"
rm -r aclocal.m4 autom4te.cache build-aux Makefile.in configure
