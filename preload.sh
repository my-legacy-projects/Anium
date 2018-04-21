#!/usr/bin/env bash

# Allows only root to use ptrace. This is temporary until the user reboots the machine.
ptrace_input=$(sudo echo "2" | sudo tee /proc/sys/kernel/yama/ptrace_scope)

# Prevent crash dumps from being sent to kisak
sudo rm -rf /tmp/dumps
sudo mkdir /tmp/dumps
sudo chmod 000 /tmp/dumps

# Game Path
# This assumes the presence of the ~/.steam symlink
game=$(realpath "$HOME/.steam/steam/steamapps/common/Counter-Strike Global Offensive/")

if [ ! -d "$game" ]; then
    echo -e "\e[91mCould not find CS:GO. Please ensure the $HOME/.steam symlink exists.\e[39m"
fi

# csgo_linux64 links against libc, so we'll fake that for now
library=$(ls /usr/lib/libc.so* | tail -1)

if [ -z "$library" ]; then
    echo -e "\e[93mUnable to locate libc, pre-loading without spoofed name.\e[39m"
    library="$(pwd)/bin/libAnium.so"
fi

# Some magic that I copied straight from StackOverflow
victim_lib_array=(${library//./ })
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

echo "Pre-loading as $library_path."

export LD_PRELOAD
LD_PRELOAD="$library_path"

# Stole this from Fuzions preload script, shootout to LWSS
export LD_LIBRARY_PATH="$game"\
":$game/bin"\
":$game/bin/linux64"\
":$HOME/.steam/steam/ubuntu12_32"\
":$HOME/.steam/steam/ubuntu12_32/panorama"\
":/usr/lib64/atlas"\
":/usr/lib64/bind99"\
":/usr/lib64/iscsi"\
":/usr/lib64/nx"\
":/usr/lib64/qt-3.3/lib"\
":/usr/lib"\
":/lib64"\
":/usr/lib/i686"\
":/usr/lib/sse2"\
":/lib64/tls"\
":/lib64/sse2"\
":$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64/lib/x86_64-linux-gnu"\
":$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64/lib"\
":$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64/usr/lib/x86_64-linux-gnu"\
":$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64/usr/lib"\
":$HOME/.steam/ubuntu12_32/steam-runtime/amd64/lib/x86_64-linux-gnu"\
":$HOME/.steam/ubuntu12_32/steam-runtime/amd64/lib"\
":$HOME/.steam/ubuntu12_32/steam-runtime/amd64/usr/lib/x86_64-linux-gnu"\
":$HOME/.steam/ubuntu12_32/steam-runtime/amd64/usr/lib"\
":$HOME/.steam/steam/ubuntu12_32"\
":$HOME/.steam/steam/ubuntu12_64"

# Set file descriptor limit
ulimit -n 2048

# Enable Nvidia threaded optimizations
export __GL_THREADED_OPTIMIZATIONS=1
# Enable Mesa threaded shader compiles
export multithread_glsl_compiler=1

# Change into game directory
cd "$game"

echo "Launching Counter-Strike: Global Offensive..."

STATUS=42

while [ $STATUS -eq 42 ]; do
	if [ "${DEBUGGER}" == "gdb" ]; then
		ARGSFILE=$(mktemp $USER.hl2.gdb.XXXX)
		echo b main > "$ARGSFILE"
		echo run $@ -game csgo >> "$ARGSFILE"
		echo show args >> "$ARGSFILE"
		${DEBUGGER} "${game}/csgo_linux64" -x "$ARGSFILE"
		rm "$ARGSFILE"
		${DEBUGGER} "${game}/csgo_linux64" "$@"
	elif [ "${DEBUGGER}" == "lldb" ]; then
		ARGSFILE=$(mktemp $USER.hl2.lldb.XXXX)
		echo "b main" > "$ARGSFILE"
		echo "env DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH" > "$ARGSFILE"
		${DEBUGGER} -s "$ARGSFILE" -- "${game}/csgo_linux64" "$@"
		rm $ARGSFILE
	else
		exec ${DEBUGGER} "${game}/csgo_linux64" "$@"
	fi
	STATUS=$?
done

# Cleanup
sudo rm -rf "$library_path"

exit $STATUS
