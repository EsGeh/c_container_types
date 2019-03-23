#!/bin/fish

set BASE_DIR (dirname (readlink -m (status filename)))/..
set SCRIPTS_DIR (dirname (readlink -m (status filename)))

set build_dir "$BASE_DIR/build"

cd "$BASE_DIR"
and eval "$SCRIPTS_DIR/run_autotools.fish"

and mkdir -p -v "$build_dir"
and cd "$build_dir"

and eval "$BASE_DIR/configure"
and make
and ./test
