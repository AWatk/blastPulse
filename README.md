# blastPulse
Labview and c++ files for control of pulse blast length, interblast interval, and number of repeated blasts

# src

C++ files to run on formatted beaglebone blue

To compile `rc_blastPulse_UDPReceiver.cpp` run the command `g++ -o udpReceiver rc_blastPulse_UDPReceiver.cpp -lpthread -lroboticscape`

make a symbolic link `sudo ln -s -f [path to udpReceiver] /etc/robotcontrol/link_to_startup_program`

then set to run at startup under the robotcontrol service

`sudo systemctl daemon-reload`

`sudo systemctl enable robotcontrol.service`

restart the beaglebone and check the program status

`sudo systemctl status -u robotcontrol.service`

# testing

`src` contains a test executable `sendtest`, run with `./sendtest`

to recompile: `g++ -o sendtest udpSendTest.cpp`

