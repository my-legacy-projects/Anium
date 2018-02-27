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

# Get the full path of the .so that we'll be faking
victim_lib=$(cat /proc/${pid}/maps | grep /usr/lib/ | shuf -n 1)
victim_lib=${victim_lib##* }

# Some magic that I copied straight from StackOverflow
victim_lib_array=(${victim_lib//./ })
number_to_spoof=${victim_lib_array[-1]}
library_path=$(IFS=. ; echo "${victim_lib_array[*]}")

if [ "$number_to_spoof" == "so" ]; then
    # If the shared library doesn't have multiple versions, let's just append .0 at the end.
    number_to_spoof="$number_to_spoof.0"
else
    # else we'll increase the found version by one
    number_to_spoof=$(($number_to_spoof + 1))
fi

victim_lib_array[-1]="$number_to_spoof"
library_path=$(IFS=. ; echo "${victim_lib_array[*]}")

if [ -e "$library_path" ]; then
    echo -e "\e[91mA error occurred. Please retry.\e[39m"
    exit -1
else
    sudo cp "bin/libAnium.so" "$library_path"

    # Get the file name of the resulting library
    result_lib_name=$(basename ${library_path})
    result_lib="${result_lib_name%.*}"

    # and patch the soname of Anium to it
    sudo patchelf --set-soname "$library_path" "$result_lib"
fi

echo "Attaching as $result_lib ($library_path) to PID $pid"

# Allows only root to use ptrace. This is temporary until the user reboots the machine.
ptrace_input=$(sudo echo "2" | sudo tee /proc/sys/kernel/yama/ptrace_scope)

# Prevent crash dumps from being sent to kisak
sudo rm -rf /tmp/dumps
sudo mkdir /tmp/dumps
sudo chmod 000 /tmp/dumps

# Pause Steam
sudo killall -19 steam
sudo killall -19 steamwebhelper

# Uses dlmopen instead of normal dlopen - Credit to LWSS
input="$(
sudo gdb -n -q -batch \
  -ex "set logging on" \
  -ex "set logging file /dev/null" \
  -ex "attach $pid" \
  -ex "set \$linkMapID = (long int)0" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "set \$dlmopen = (void*(*)(long int, char*, int)) dlmopen" \
  -ex "set \$dlinfo = (int (*)(void*, int, void*)) dlinfo" \
  -ex "set \$malloc = (void*(*)(long long)) malloc" \
  -ex "set \$target = \$dlopen(\"$library_path\", 2)" \
  -ex "p \$target" \
  -ex "p \$linkMapID" \
  -ex "call \$dlmopen(0, \"$library_path\", 1)" \
  -ex "set \$error = call dlerror()" \
  -ex "x/s \$error" \
  -ex "detach" \
  -ex "quit"
)"

# Resume Steam
sleep 1
sudo killall -18 steamwebhelper
sudo killall -18 steam

sudo rm -rf "$library_path"

if grep -q "$library_path" /proc/${pid}/maps; then
    echo "Successfully attached to PID $pid."
else
    echo -e "\e[91mA error occurred. See gdb.txt\e[39m"
    exit -1
fi

if [ -f "$(pwd)/gdb.txt" ]; then
    sudo rm -rf gdb.txt
fi
