# Heart Rate Monitor

**This project was made just for fun**. The goal of this project was to develop a Heart Rate Monitor app. to make my indoor bike training sessions a little more interesting. 

# About the project

The app uses **accelerometer data** sent by an **STM32 microcontroller** (mounted to a chest strap - image below) to the PC via **Bluetooth** (Bluetooth module attached to the USB port) to make the appropriate data manipulation, calculate the Heart Rate and then display useful information to the user, like **Heart Rate, Heart Rate Zone and calories burned** (according to user's age, gender and weight). 

The accelerometer mounted on the chest strap detects the impact associated with each heart beat and the user can **change the sensibility to filter the raw accelerometer data** before the Heart Rate calculation takes place. At the end of the workout the user can **save a .CSV file** with the data of each training session (Heart Rate, Heart Rate Zone and calories burned). 

The app shown below was developed using **MATLAB's App Designer** tool.


![Preview-Screens](https://github.com/patrickmetzner/HeartRateMonitor/blob/master/app.jpeg)

![Preview-Screens](https://github.com/patrickmetzner/HeartRateMonitor/blob/master/ChestStrap.jpeg)
 