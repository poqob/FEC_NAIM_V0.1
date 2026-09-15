# FEC_NAIM_V0.1

## About
FEC_NAIM_V0.1 is an Arduino/C++ embedded control project designed around a modular and process-based architecture. The system runs multiple hardware and communication processes in parallel, including motor control, lift control, IMU handling, load sensing, and distance sensing.

At startup, the main sketch registers these processes into a scheduler and executes them continuously. Network communication is handled by a dedicated process and a custom service layer, enabling message-based interaction between devices over configured channels and routes.

This structure separates hardware drivers, process logic, and services into clear layers, making the project easier to extend and maintain when adding new sensors, actuators, or communication features.

## How to Run
1. Install Arduino IDE (or use PlatformIO) and the required board support package for your target board.
2. Open `/home/runner/work/FEC_NAIM_V0.1/FEC_NAIM_V0.1/FEC_NAIM_V0.1.ino`.
3. Verify that required libraries are available in the project (for example, the process scheduler and included local network modules under `lib/`).
4. Select the correct board and serial port in your IDE.
5. Build and upload the sketch to the device.
6. Open the serial monitor (115200 baud if using the default UART setup) to observe runtime behavior and debugging/network output.
