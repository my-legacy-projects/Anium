#!/usr/bin/env bash

pid=$(pidof csgo_linux64) # Default to CS:GO

if [[ -n "$1" ]]; then
    if [ "$1" -eq "$1" ] 2>/dev/null; then
        # First argument is a int (PID)
        pid=$1
    else
        # First argument is a string (Process ID)
        pid=$(pidof $1)
    fi
fi

if [ -z "$pid" ]; then
    echo -e "\e[91mCould not find target process.\e[39m"
    exit -1
fi

if [ ! -e "/tmp/Anium.log" ]; then
    echo -e "\e[91mAnium had to be attached before being detached.\e[39m"
    exit -1
fi

if ! grep -q "Welcome to Anium" /tmp/Anium.log; then
    echo -e "\e[91mAnium was not fully loaded yet or was pre-loaded.\e[39m"
    exit -1
fi

# Parse Anium.log into finding our library name
log=$(head -n 1 /tmp/Anium.log)
no_prefix=${log:33}

if [[ "$no_prefix" == Unable* ]]; then
    echo -e "\e[91mAnium was unable to find itself, detaching is impossible without closing the game.\e[39m"
    exit -1
fi

handle=${log:51}
handle=(${handle//,/ })

echo "Anium was attached as $handle."

# Pause Steam
sudo killall -19 steam
sudo killall -19 steamwebhelper

input="$(
sudo gdb -n -q -batch \
    -ex "set logging on" \
    -ex "set logging file /dev/null" \
    -ex "attach $pid" \
    -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
    -ex "set \$dlclose = (int(*)(void*)) dlclose" \
    -ex "set \$library = \$dlopen(\"$handle\", 6)" \
    -ex "call \$dlclose(\$library)" \
    -ex "call \$dlclose(\$library)" \
    -ex "call \$dlclose(\$library)" \
    -ex "call \$dlerror()" \
    -ex "detach" \
    -ex "quit"
)"

# Resume Steam
sleep 1
sudo killall -18 steamwebhelper
sudo killall -18 steam

if ! grep -q "$handle" /proc/${pid}/maps; then
    echo "Successfully detached from PID $pid."
else
    echo -e "\e[91mA error occurred. See gdb.txt\e[39m"
    exit -1
fi

if [ -f "$(pwd)/gdb.txt" ]; then
    sudo rm -rf gdb.txt
fi
