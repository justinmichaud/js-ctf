# CTF

Go here: https://justinmichaud.com/js-ctf/v86-master/?profile=debian

Then, some commands to help you:

```
./run.sh
./debug.sh
vi ./run.sh
vi 0*
```

# 0-intro.js

Change the file so that calling B really calls A

# 1-*.js

Prove that rop is possible by overwriting returnPC (note: cloop makes this impossible, TODO)

# 2-*.js

Make a read64 primitive out of fakeobj and addrof

# Docker/wasm Details

This is the build of JSC with some changes, see this repo's history for details.

TODO: In build-box/, you can find a virtualbox image that I used to build jsc.

# Building the hd image:

Build using the instructions in Tools/Docker/alpine (including build-state)

```

debian$ sudo ./build-container.sh && node ./build-state.js

# Alpine doesn't work

js-ctf/v86-master/tools/docker/alpine$ sudo ./build.sh && node ./build-state.js 

js-ctf/v86-master$ python3 -m http.server 8000


```
Then go to http://localhost:8000/?profile=archlinux

To use the archlinux-boot profile (that is, if you don't use build-state), use firefox, and set:
privacy.reduceTimerPrecision	false	
privacy.reduceTimerPrecision.unconditional	false	

(don't forget to change them back)