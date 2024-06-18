# blastPulse
Labview and c++ files for control of pulse blast length, interblast interval, and number of repeated blasts. This is a system meant to operate using a laptop running a control VI that communicates with a BeagleBone Blue instrumented to control the solenoid hardware for a blast system.

# Generage Use

1. Click the green button in the top right of this repository labeled `Code` and either clone this repository using git or download and extract the zip file of the repository's contents
2. Move the `BlastPulse-LabviewVIs` folder to your desired location
3. Turn on Beaglebone Blue and wait for it to initialize 
4. Connect to the BeagleBone-XXXX wifi network, password: BeagleBone
5. In labview open the 'GenericBlastPulseWithTransducer' vi
6. Follow the instructions embedded in the vi

# BeagleBone Blue Setup

This assumes some familiarity with configuring an embedded linus system

Copy the contents of `src` onto the beaglebone blue

To compile `rc_blastPulse_UDPReceiver.cpp` run the command `g++ -o udpReceiver rc_blastPulse_UDPReceiver.cpp -lpthread -lroboticscape`

make a symbolic link `sudo ln -s -f [path to udpReceiver] /etc/robotcontrol/link_to_startup_program`

then set to run at startup under the robotcontrol service

`sudo systemctl daemon-reload`

`sudo systemctl enable robotcontrol.service`

restart the beaglebone and check the program status

`sudo systemctl status -u robotcontrol.service`

# Testing

`src` contains a test executable `sendtest`, run with `./sendtest`

to recompile: `g++ -o sendtest udpSendTest.cpp`

