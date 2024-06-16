# README.md

## Overview

This repository contains two scripts:
1. `EMG_BLE_Code.ino` for the ESP32, which sends EMG data to a laptop via BLE.
2. `LSL3.py`, a Python script that connects to the ESP32, receives the BLE data, and starts an LSL stream.

The following sections detail the setup, usage, and how to visualize and record the data using LabRecorder and MATLAB EEGLAB.

## Setup

### 1. EMG BLE Code for ESP32

1. **Hardware Requirements:**
   - ESP32 development board
   - EMG sensor

2. **Software Requirements:**
   - Arduino IDE
   - BLE library for Arduino

3. **Steps:**
   - Open `EMG_BLE_Code.ino` in the Arduino IDE.
   - Connect your ESP32 to your computer.
   - Select the correct board and port in the Arduino IDE.
   - Upload the code to your ESP32.

### 2. LSL Streamer Python Script

1. **Software Requirements:**
   - Python 3.7+
   - `bleak` library
   - `pylsl` library

2. **Steps:**
   - Ensure your ESP32 is powered on and broadcasting BLE data.
   - Install the required Python libraries using pip:
     ```sh
     pip install bleak pylsl
     ```
   - Update the BLE address in `LSL3.py` with your ESP32's BLE address.
   - Run the script:
     ```sh
     python LSL3.py
     ```

## Recording Data using LabRecorder

1. **Download LabRecorder:**
   - Download LabRecorder from the [LabRecorder GitHub repository](https://github.com/labstreaminglayer/App-LabRecorder).

2. **Setup:**
   - Extract the downloaded files.
   - Run the LabRecorder application.
   - Select the `ESP32_BLE_Stream` from the list of available streams.
   - Choose a file name and directory to save the recording.
   - Click the "Start" button to begin recording.

![LabRecorder Interface](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Lab%20Recorder.png)
![LabRecorder Interface](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Lab%20Recorder.png)

## Visualizing Data in MATLAB using EEGLAB

1. **Download and Install EEGLAB:**
   - Download EEGLAB from the [EEGLAB website](https://sccn.ucsd.edu/eeglab/download.php).
   - Extract the files and add the EEGLAB folder to your MATLAB path.

2. **Load Recorded Data:**
   - Open MATLAB and start EEGLAB by typing `eeglab` in the command window.
   - Load the recorded `.xdf` file from LabRecorder:
     - `File -> Import data -> Using EEGLAB functions and plugins -> From imported .xdf file`
   - Browse to the location of your recorded file and load it.

3. **Visualize the Data:**
   - After loading the data, you can use EEGLAB's various visualization tools to analyze the EMG data.

![EEGLAB Interface](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/EEG%20Lab.png)

## Notes

- Ensure the BLE address in `LSL3.py` matches your ESP32's BLE address.
- Make sure your ESP32 is properly broadcasting data and that the BLE service and characteristic UUIDs match those in the Python script.
- If you encounter issues with BLE connections, try restarting your ESP32 or laptop's Bluetooth service.

## Files

- `EMG_BLE_Code.ino`: Arduino code for ESP32 to broadcast EMG data over BLE.
- `LSL3.py`: Python script to receive BLE data and start an LSL stream.

## Contact

For any issues or questions, please open an issue on the GitHub repository or contact the maintainer.

---

This README provides a detailed guide on setting up, using, and visualizing data from the EMG BLE system. Ensure to update paths and addresses as needed and refer to the provided screenshots for assistance.
