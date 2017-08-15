# Temperature Sensor 

The temperature sensor is responsible for predicting the body temperature by measuring both the room and the finger temperature and applying a linear regression - an [Elastic Net](https://en.wikipedia.org/wiki/Elastic_net_regularization) to be precise - to it. This readme aims to provide a better understanding on how this is achieved and how the temperature sensors integrates into the existing HealthHub architecture.

We used the DS18B20 digital temperature sensor as well as the c++ libraries [OneWire](http://playground.arduino.cc/Learning/OneWire) and  [Arduino-Temperature-Control-Library](https://github.com/milesburton/Arduino-Temperature-Control-Library).

# Class Structure
Like any other sensor class the TemperatureSensor class provides the function `finishedScan()`, `update()` and `getSensorValue()` to obtain the sensor value. These functions are called **every second**.

In order to obtain the body temperature the implementation goes through several steps:
1. Check if the scan is already finished or not (`finishedScan()`).
2. Request both the room and finger temperature (`update()`).
3. If the scan is finished, estimate the body temperature by applying linear regression (`getSensorValue()`). 

Let's go through each step in a little more detail:

## Check if the Scan is finished
The sensor stores the last five values of the requested finger temperature to create a history over a given time. Once the list is completely filled with values, the standard deviation is computed using the `standardDeviation()` function provided by the List class. If the deviation is smaller than a given threshold (200 = 0.2°C), the scan is deemed finished and the variable `isFinishedScan` is set to true.

## Request Temperatures
The human body regulates its temperature over its limbs which makes it impossible to conclude directly from the finger temperature to the body temperature. This poses a problem, since we aim to measure vital data by placing the hand on the device. To make an attempt to solve this issue, the temperature class measures the room temperature as well as the current finger temperature and derives an approximation to the body temperature.

## Estimate the Body Temperature
To be able to estimate the body temperature given the room and finger temperature, a regression model was trained using actual body temperatures measured by a thermometer. The training was done using the python library [scikit-learn](http://scikit-learn.org/).

The `fingerTemp2BodyTemp` function uses the learned coefficients and intercept to calculate the estimated value. This is done by applying the formula `bodyTemp = intercept + (fingerTemp * finger_coef) + (roomTemp * room_coef)`

> Note that this value is a very rough estimation of the actual body temperature and should not be used for medical purposes!

```python
int16_t TemperatureSensor::fingerTemp2bodyTemp(int16_t fingerTemp, int16_t roomTempMean){
  int32_t finger_coef = 8;
  int32_t room_coef = -6;
  int32_t interception = 354429;

  int32_t result = (interception + (fingerTemp * finger_coef) + (roomTempMean * room_coef)) / 100;

  return result;
}
```
