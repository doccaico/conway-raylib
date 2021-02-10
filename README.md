##Build
### Desktop
```sh
$ mkdir build
$ cd build
$ cmake ../src

# run
$ make run
# or
$ cmake --build . -t run
```
### Web
```sh
$ ./make_web.bash

$ python wasm-server.py
# open in your browser ( http://localhost:8080/ )
# click `main.html`
```
