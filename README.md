# blastPulse
Labview and c++ files for control of pulse blast length, interblast interval, and number of repeated blasts

# src

C++ files to run on a beaglebone blue with a vanilla image (has robotics cape installed by default)

To compile `udpReceiver.cpp` run the command `g++ -o udpReceiver udpReceiver.cpp -lpthread -lroboticscape`

with newer versions of roboticscape, make a symbolic link `sudo ln -s -f ~/[path to udpReceiver] /etc/roboticscape/link_to_startup_program`

then set to run at startup under the roboticscape service

`sudo systemctl daemon-reload`

`sudo systemctl enable roboticscape`

