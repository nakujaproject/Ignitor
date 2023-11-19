#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include <cmath>
#include <vector>

// Constants for Goertzel algorithm
const float f_target = 100; // Target frequency [Hz]
const float fs = 1000;      // Sampling frequency [Hz]
const int N = 100;          // Number of samples for Goertzel algorithm

// Goertzel algorithm variables
float r, s, w;          // Goertzel coefficients
float x_prev1 = 0;      // Previous output x(n-1)
float x_prev2 = 0;      // Previous output x(n-2)
float amplitude = 0;    // Amplitude of the target frequency
float phase = 0;        // Phase of the target frequency

// Data buffer for the moving window
std::vector<float> data_window;

// Simulated GPIO setup function (replace this with your actual setup logic)
void setupGPIO(int pin, bool mode) {
    pinMode(pin, mode ? OUTPUT : INPUT);
    Serial.println("Setting up GPIO pin " + String(pin) + " in mode " + String(mode));
}

// Simulated GPIO read function (replace this with your actual reading logic)
bool readGPIO(int pin) {
    Serial.println("Reading from GPIO pin " + String(pin));
    return digitalRead(pin) == HIGH;  // Replace this with the actual reading logic
}

float readFlowSensor(ModbusMaster& sensor, int pin) {
    setupGPIO(pin, false);  // Replace false with the actual mode for input

    uint16_t flowRate = 0;

    // Read flow using MODBUS
    uint8_t result = sensor.readHoldingRegisters(FLOW_REGISTER, FLOW_DATA_SIZE);

    if (result == sensor.ku8MBSuccess) {
        for (uint8_t j = 0; j < FLOW_DATA_SIZE; j++) {
            flowRate = sensor.getResponseBuffer(j);
        }
        return static_cast<float>(flowRate);
    } else {
        Serial.println("MODBUS Failure. Code: " + String(result));
        return 0.0;
    }
}

// Function to calculate the Goertzel coefficients
void calcGoertzelCoefficients() {
    int k = static_cast<int>(N * f_target / fs);
    float theta = 2 * 3.14159 * k / N;
    r = 2.0 * cos(theta);
    s = sin(theta);
    w = 2.0 * cos(2 * theta);
}

// Function to perform the Goertzel algorithm and obtain amplitude and phase data
void performGoertzelAlgorithm(float x_curr) {
    float x_temp = x_curr + r * x_prev1 - x_prev2;
    x_prev2 = x_prev1;
    x_prev1 = x_temp;

    // Calculate magnitude squared (amplitude squared) from Goertzel output
    float x_result = x_prev2 * x_prev2 + x_prev1 * x_prev1 - r * x_prev1 * x_prev2;
    // Convert magnitude squared to amplitude and phase
    amplitude = sqrt(x_result);
    phase = atan2(x_prev1, x_prev2);
}

void setup() {
    Serial.begin(9600);

    // Initializing and configuring microcontroller peripherals and GPIO pins
    SoftwareSerial swSerial(2, 3); // RX, TX
    ModbusMaster sensor;
    swSerial.begin(9600);
    sensor.begin(1, swSerial); // MODBUS_DEVICE_ID, SoftwareSerial

    calcGoertzelCoefficients();
}

void loop() {
    // Read the input signal from the flow sensor using MODBUS
    float input_signal = readFlowSensor(sensor, 4); // Replace 4 with the actual pin connected to the flow sensor

    // Add the new data point to the data_window
    data_window.push_back(input_signal);

    // If the size of data_window exceeds N, remove the oldest data point
    if (data_window.size() > N) {
        data_window.erase(data_window.begin());
    }

    // Perform Goertzel algorithm on the data in the data_window
    performGoertzelAlgorithm(input_signal);

    // Fourier series approximation using Goertzel-derived amplitude and phase data
    float t = 0; // Time variable for generating the Fourier series
    float sum = 0; // Sum of the Fourier series
    for (int i = 0; i < data_window.size(); i++) {
        // Generate the ith harmonic component and add it to the sum
        sum += amplitude * cos(2 * 3.14159 * f_target * t / fs + phase);
        t += 1.0 / fs;
    }

    // Additional code for using the Fourier series approximation (sum)
    // For example, you can use 'sum' to represent the approximated signal.
    // ...

    // Additional code for the main loop
    // ...

    delay(1000); // Simulated delay for periodic readings (adjust as needed)
}
