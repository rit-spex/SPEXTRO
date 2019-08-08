EESchema Schematic File Version 4
LIBS:Sensors-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor_Motion:BNO055 U?
U 1 1 5D4B688F
P 2700 2350
F 0 "U?" H 2700 3228 50  0000 C CNN
F 1 "BNO055" H 2700 3137 50  0000 C CNN
F 2 "Package_LGA:LGA-28_5.2x3.8mm_P0.5mm" H 2950 1700 50  0001 L CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST_BNO055_DS000_14.pdf" H 2700 2550 50  0001 C CNN
	1    2700 2350
	1    0    0    -1  
$EndComp
Text Notes 1250 1150 0    100  ~ 0
Accelerometer / Magnetometer / Gyro
Wire Notes Line
	900  850  900  3700
Wire Notes Line
	900  3700 4700 3700
Wire Notes Line
	4700 3700 4700 850 
Wire Notes Line
	4700 850  900  850 
$EndSCHEMATC
