# Flexiwave
The Brainovative Flexiwave is an advanced EMG sensor featuring adjustable gain settings, ranging from 1 to 50 for instrumental gain. This adaptability makes it an ideal solution for a wide range of physiological monitoring applications. The Flexiwave seamlessly interfaces with microcontrollers, facilitating straightforward integration across a variety of platforms. It features a bandpass filter that can be configured to meet specific analysis requirements, ensuring flexibility and precision in signal output for diverse applications. This EMG sensor is perfect for applications in biomechanics, including biofeedback devices and prosthetic arms, enhancing user experience with precise muscle activity measurements.

# Hardware
Here are images that provide a detailed overview of the hardware design, illustrating the various components and their configurations.
| ![Image 1](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Front.jpg) | ![Image 2](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Back.jpg) |
|--------------------------------|--------------------------------|
| PCB Front    | PCB Back      |

| ![Image 3](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/PCB_Front.jpg) | ![Image 4](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/PCB_Back.jpg) |
|--------------------------------|--------------------------------|
| Front        | Back      |

## Features
1.Input Voltage: 3.3 – 5 V

2.Input Impedance: 10^12 Ω

3.Adjustable Instrumental Gain: 1 - 50

4.Bandpass filter: 20 – 500 Hz

5.Compatible Hardware: Compactable with any ADC

6.Bio Potentials: EMG

7.No. of channels: 1

8.Electrodes: 3 (Positive, Negative, and Reference)

9.Dimensions: 36.38 x 25.01 mm

# How To Use

![Image](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Connection.jpg) 


## Connections

- **VCC:** 3.3V / 5V
- **GND:** GND of Microcontroller
- **Out:** Analog Output of Microcontroller
- **IN1:** Place this electrode on the muscle you want to measure. Ideally, it should be positioned over the belly of the muscle, which is the thickest part of the muscle.
- **IN2:** Place this electrode on the same muscle, but a few centimeters away from Electrode 1, along the length of the muscle fiber. The distance between the electrodes typically ranges from 1 to 2 centimeters, depending on the size of the muscle and the specificity of the measurement.
- **REF:** The reference electrode should be placed on a neutral, electrically inactive site. Common placements include a bony area or a distant site from the muscle being measured to ensure it picks up minimal muscle activity. Typical locations are the bony prominences such as the elbow, wrist, or an electrically neutral area like the shoulder or a nearby bone.

## Gain 
The gain of the Flexiwave sensor is adjustable, allowing users to amplify the muscle signals to a desired level for optimal signal processing and analysis. This feature enhances the sensor's versatility, making it suitable for a wide range of applications in biomechanics and biofeedback.
Range:1-50 (1ohm-1Kohm)

| ![Image 1](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Front.jpg) | ![Image 2](https://github.com/BrainovativeLabs/Flexiwave/blob/main/Images/Back.jpg) |









