# 🏁 Race_3LED_ESP32

## ESP32 Web-Controlled Robot Race Signal System

A web-controlled robot race signal system developed using an **ESP32**, three LEDs, and a custom web interface.

The ESP32 operates in **Wi-Fi Access Point (AP) mode**, allowing a smartphone or computer to connect directly to the ESP32 and control the physical race lights through a locally hosted web interface without requiring an external router or internet connection.

The system uses three race states:

- 🔴 **STOP**
- 🟡 **READY**
- 🟢 **GO**

This project demonstrates the integration of **embedded systems, IoT, electronics, Wi-Fi communication, and web-based hardware control** within a robotics engineering application.

---

## 🎥 Project Demos

### Physical Implementation

The final implementation demonstrates the web interface controlling the three physical LEDs through the ESP32 Wi-Fi network.



https://github.com/user-attachments/assets/9d497d66-de70-44a6-b88c-77cdcc627264


### Wokwi Simulation

A short simulation video demonstrates the initial STOP, READY, and GO LED control logic using Wokwi.



https://github.com/user-attachments/assets/75c5ecb3-660b-42bb-afe7-db52829fa5d3



---

## 🚦 System Operation

The system represents a robotic race starting signal with three operating states:

| Signal | Command | Function | ESP32 GPIO |
|---|---|---|---:|
| 🔴 Red | STOP | Stops the race | GPIO 26 |
| 🟡 Yellow | READY | Prepares for the race | GPIO 27 |
| 🟢 Green | GO | Starts the race | GPIO 25 |

The traffic lights displayed on the web interface act as the control buttons.

When a signal is selected, the webpage sends an HTTP request to the ESP32. The ESP32 activates the corresponding physical LED while turning the other two LEDs off.

---

## 🧩 Components
<img width="3024" height="4032" alt="IMG_5044" src="https://github.com/user-attachments/assets/baeb5f69-2b8c-40b4-846b-92d6c56f4752" />
<img width="3024" height="4032" alt="IMG_5042" src="https://github.com/user-attachments/assets/6aff449b-7c48-4522-96f4-10dddd1effea" />
<img width="3024" height="4032" alt="IMG_5045" src="https://github.com/user-attachments/assets/c0bafc94-9e44-4263-b674-b3ac3830c9c3" />

The following components were used:

- ESP32 development board
- Breadboard
- 1 × Red LED
- 1 × Yellow LED
- 1 × Green LED
- 3 × 330 Ω resistors
- Jumper wires
- USB cable
- Computer with Arduino IDE
- Smartphone or computer for web control

---

## 🔌 Hardware Connections

Each LED is connected to a dedicated ESP32 GPIO pin through a **330 Ω current-limiting resistor**.

### 🔴 Red LED

```text
GPIO 26
   │
330 Ω Resistor
   │
LED Anode (+)
   │
LED Cathode (-)
   │
GND
```

### 🟡 Yellow LED

```text
GPIO 27
   │
330 Ω Resistor
   │
LED Anode (+)
   │
LED Cathode (-)
   │
GND
```

### 🟢 Green LED

```text
GPIO 25
   │
330 Ω Resistor
   │
LED Anode (+)
   │
LED Cathode (-)
   │
GND
```

### Wiring Summary

| Component | ESP32 Connection |
|---|---:|
| Red LED | GPIO 26 |
| Yellow LED | GPIO 27 |
| Green LED | GPIO 25 |
| LED Cathodes | GND |
| LED Resistors | 330 Ω |

The cathodes (short legs) of all three LEDs are connected to the **negative rail of the breadboard**.

The negative rail is connected to a **GND pin on the ESP32**, providing a common ground for the three LEDs.

---

## 📡 ESP32 Wi-Fi Access Point

The ESP32 is configured in **Wi-Fi Access Point (AP) mode**.

Instead of connecting to an existing Wi-Fi network, the ESP32 creates its own local wireless network.

A smartphone or computer can connect directly to this network and communicate with the ESP32.

### Network Configuration

```text
SSID: Wejdan_Robot_Race
IP Address: 192.168.4.1
```

After connecting to the ESP32 Wi-Fi network, the control interface can be accessed through a web browser at:

```text
192.168.4.1
```

No internet connection is required because the webpage and web server are hosted locally by the ESP32.

---

## 🔄 System Architecture

```text
Smartphone / Computer
        │
        │ Wi-Fi
        ▼
ESP32 Access Point
        │
        ▼
ESP32 Web Server
        │
        │ HTTP Requests
        ▼
STOP / READY / GO
        │
        ├── STOP  → GPIO 26
        ├── READY → GPIO 27
        └── GO    → GPIO 25
        │
        ▼
Physical LEDs
     🔴   🟡   🟢
```

---

## 🌐 Web Control Interface

The control webpage is hosted directly by the ESP32 web server.

The interface was designed around a **robot race concept** and includes:

- Robot race track
- Starting line
- Robot race vehicle
- Interactive traffic signal
- STOP, READY, and GO states
- Visual indication of the selected signal
- Robot movement animation
- Responsive web layout

The three traffic-light circles themselves function as the control buttons.

### 🔴 STOP

Selecting the red signal sends:

```text
/stop
```

The ESP32 changes the outputs to:

```text
Red LED    → ON
Yellow LED → OFF
Green LED  → OFF
```

### 🟡 READY

Selecting the yellow signal sends:

```text
/ready
```

The ESP32 changes the outputs to:

```text
Red LED    → OFF
Yellow LED → ON
Green LED  → OFF
```

### 🟢 GO

Selecting the green signal sends:

```text
/go
```

The ESP32 changes the outputs to:

```text
Red LED    → OFF
Yellow LED → OFF
Green LED  → ON
```

The robot also moves forward on the web interface to visually represent the start of the race.

---

## ⚙️ How It Works

1. The ESP32 starts in **Wi-Fi Access Point mode**.
2. It creates its own local Wi-Fi network.
3. The ESP32 starts an HTTP web server.
4. A smartphone or computer connects to the ESP32 Wi-Fi network.
5. The user opens `192.168.4.1` in a web browser.
6. The ESP32 serves the Robot Race Control interface.
7. The user selects STOP, READY, or GO.
8. The webpage sends the corresponding HTTP request.
9. The ESP32 changes the appropriate GPIO output.
10. The selected physical LED turns ON while the other two LEDs turn OFF.

---

## 🖥️ Initial Simulation with Wokwi

Before moving to the physical implementation, the project was first developed and tested using the **Wokwi ESP32 simulator**.

The initial simulation included:

- ESP32 configuration
- Three LED connections
- GPIO assignments
- STOP, READY, and GO logic
- LED output testing

The three LED states were successfully tested in the simulation before moving to the physical circuit.

### 🎥 Simulation Test

A short video was recorded during the simulation stage to demonstrate the three LED states operating in Wokwi.


https://github.com/user-attachments/assets/44506687-a1e7-49b8-bec1-f65929ae42ff

---
### Challenge

While the LED control logic could be tested successfully in Wokwi, I encountered a limitation when attempting to access and test the **ESP32-hosted web interface through the browser using the available free simulation environment**.

This prevented the complete browser-to-ESP32 interaction from being tested through the simulation environment.

### Solution

The simulation was used to develop and verify the circuit and LED control logic.

The project was then transferred to the **physical ESP32 and breadboard**, where the ESP32 was configured as a Wi-Fi Access Point.

A smartphone could then connect directly to the ESP32 network and access the locally hosted control interface at:

```text
192.168.4.1
```

The complete communication flow was then tested on the physical hardware:

```text
Web Interface
      │
      ▼
Wi-Fi Connection
      │
      ▼
ESP32 Web Server
      │
      ▼
STOP / READY / GO
      │
      ▼
Physical LEDs
```

This development process allowed the circuit and control logic to be tested virtually before completing the full web-controlled system using physical hardware.

---

## 🧪 Hardware Testing & Debugging

Before integrating the final web interface, the physical LEDs and GPIO connections were tested individually to verify the circuit.

The final GPIO mapping used in the physical implementation is:

```cpp
RED_LED    = 26;
YELLOW_LED = 27;
GREEN_LED  = 25;
```

After verifying the physical circuit, the ESP32 Access Point and web interface were tested using a browser connected directly to the ESP32 Wi-Fi network.

The final implementation successfully provided wireless control of the three physical race signals through the ESP32-hosted web interface.

---

## 💻 Software & Technologies

The project was developed using:

- **Arduino IDE**
- **C/C++**
- **ESP32**
- **ESP32 Wi-Fi**
- **ESP32 WebServer**
- **Wi-Fi Access Point mode**
- **HTTP communication**
- **HTML**
- **CSS**
- **JavaScript**
- **Wokwi Simulator**

The HTML, CSS, and JavaScript interface is embedded directly within the ESP32 program and served by its local web server.

---

## 📁 Repository Structure

```text
Race_3LED_ESP32/
│
├── Race_3LED_ESP32.ino
├── README.md
│
└── demo/
    ├── physical-demo.mp4
    └── wokwi-demo.mp4
```

---

## ▶️ Running the Project

### 1. Build the Circuit

Connect the LEDs according to the following GPIO configuration:

```text
Red    → GPIO 26
Yellow → GPIO 27
Green  → GPIO 25
GND    → Breadboard negative rail
```

Use a **330 Ω resistor** with each LED.

### 2. Connect the ESP32

Connect the ESP32 to the computer using a USB cable.

### 3. Open the Arduino Project

Open:

```text
Race_3LED_ESP32.ino
```

using Arduino IDE.

### 4. Select the Board and Port

Select the appropriate ESP32 board and COM port in Arduino IDE.

### 5. Upload the Code

Upload the program to the ESP32.

### 6. Check the Serial Monitor

Open the Serial Monitor at:

```text
115200 baud
```

The ESP32 will display information about the Access Point and web server.

The local IP address is:

```text
192.168.4.1
```

### 7. Connect to the ESP32 Wi-Fi

Using a smartphone or computer, connect to:

```text
Wejdan_Robot_Race
```

The device may display **No Internet Connection**.

This is expected because the ESP32 network is used for local communication rather than internet access.

### 8. Open the Web Interface

Open a web browser and navigate to:

```text
192.168.4.1
```

The Robot Race Control interface will appear.

### 9. Control the Signals

Use the interactive traffic light to select:

```text
STOP
READY
GO
```

The corresponding physical LED will respond to the selected command.

---

## 🎯 Learning Outcomes

Through this project, I gained practical experience with:

- ESP32 GPIO programming
- Breadboard circuit implementation
- LED current-limiting resistors
- Common ground connections
- Embedded systems development
- ESP32 Wi-Fi Access Point configuration
- Local wireless communication
- Embedded HTTP web servers
- HTTP request handling
- Web-to-hardware communication
- HTML and CSS interface development
- JavaScript-based hardware commands
- Wokwi circuit prototyping
- Physical electronics testing and debugging
- Moving from simulation to physical hardware
- Integrating IoT and web technologies into robotics applications

---

## 🤖 Robotics Engineering Internship

This project was completed as part of the **Robotics Engineering Internship at Smart Methods**, within the **IoT, Electronics, and Electrical Power Track**.

The task provided hands-on experience in integrating **ESP32-based embedded systems, electronic circuits, Wi-Fi communication, IoT concepts, and web-based hardware control** within a robotics engineering application.
