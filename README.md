# PushDown Automata 
## for language L = {w: n_a(w) + n_b(w) = n_c(w)}

### Install dependencies

#### tests
$ sudo apt-get install check

#### js build

[See how install emscripten](https://emscripten.org/docs/getting_started/downloads.html)

##### adding in PATH

PATH=/path/to/emscipten/compiler:$PATH

### Build

#### tests

$ make build \
$ make test

#### js build

$ make build_js

#### build

$ make build
