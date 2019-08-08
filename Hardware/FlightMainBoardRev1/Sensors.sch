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
$Comp
L 2019-08-08_00-59-52:MS561101BA03-50 U?
U 1 1 5D4B749C
P 8150 1850
F 0 "U?" H 8150 2437 60  0000 C CNN
F 1 "MS561101BA03-50" H 8150 2331 60  0000 C CNN
F 2 "SON8_MS5611" H 8150 2290 60  0001 C CNN
F 3 "" H 8150 1850 60  0000 C CNN
	1    8150 1850
	1    0    0    -1  
$EndComp
Text GLabel 9200 1750 2    50   Input ~ 0
PRESSURE_SDI
Text GLabel 9200 1850 2    50   Input ~ 0
PRESSURE_SDO
Text GLabel 9200 1650 2    50   Input ~ 0
PRESSURE_SCLK
Wire Wire Line
	9050 1650 9200 1650
Wire Wire Line
	9050 1750 9200 1750
Wire Wire Line
	9050 1850 9200 1850
$Comp
L Device:C C?
U 1 1 5D4B7664
P 6750 1800
F 0 "C?" H 6865 1846 50  0000 L CNN
F 1 "C" H 6865 1755 50  0000 L CNN
F 2 "" H 6788 1650 50  0001 C CNN
F 3 "~" H 6750 1800 50  0001 C CNN
	1    6750 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4B76F7
P 6750 2150
F 0 "#PWR?" H 6750 1900 50  0001 C CNN
F 1 "GND" H 6755 1977 50  0000 C CNN
F 2 "" H 6750 2150 50  0001 C CNN
F 3 "" H 6750 2150 50  0001 C CNN
	1    6750 2150
	1    0    0    -1  
$EndComp
Text GLabel 6750 1450 1    50   Input ~ 0
+3.3v
Wire Wire Line
	6750 1650 6750 1450
Wire Wire Line
	6750 2150 6750 2050
Wire Wire Line
	7250 1650 6750 1650
Connection ~ 6750 1650
Wire Wire Line
	7250 1750 7050 1750
Wire Wire Line
	7050 1750 7050 1850
Wire Wire Line
	7050 2050 6750 2050
Connection ~ 6750 2050
Wire Wire Line
	6750 2050 6750 1950
Text GLabel 9200 1950 2    50   Input ~ 0
PRESSURE_CSB
Text Notes 7550 1000 0    100  ~ 0
Pressure Sensor
Wire Notes Line
	5950 750  5950 2800
Wire Notes Line
	5950 2800 10400 2800
Wire Notes Line
	10400 2800 10400 750 
Wire Notes Line
	10400 750  5950 750 
Wire Wire Line
	9050 1950 9200 1950
Wire Wire Line
	7250 1850 7050 1850
Connection ~ 7050 1850
Wire Wire Line
	7050 1850 7050 2050
Text GLabel 2350 1450 0    50   Input ~ 0
+3.3v
Wire Wire Line
	2800 1650 2800 1450
Wire Wire Line
	2800 1450 2600 1450
Wire Wire Line
	2600 1650 2600 1450
Connection ~ 2600 1450
Wire Wire Line
	2600 1450 2350 1450
Text GLabel 1950 2250 0    50   Input ~ 0
+3.3v
Wire Wire Line
	1950 2250 2100 2250
$Comp
L power:GND #PWR?
U 1 1 5D4B7BAF
P 2600 3200
F 0 "#PWR?" H 2600 2950 50  0001 C CNN
F 1 "GND" H 2605 3027 50  0000 C CNN
F 2 "" H 2600 3200 50  0001 C CNN
F 3 "" H 2600 3200 50  0001 C CNN
	1    2600 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4B7C34
P 3700 2850
F 0 "#PWR?" H 3700 2600 50  0001 C CNN
F 1 "GND" V 3705 2722 50  0000 R CNN
F 2 "" H 3700 2850 50  0001 C CNN
F 3 "" H 3700 2850 50  0001 C CNN
	1    3700 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D4B7D5B
P 3500 2850
F 0 "C?" V 3752 2850 50  0000 C CNN
F 1 "0.1uF" V 3661 2850 50  0000 C CNN
F 2 "" H 3538 2700 50  0001 C CNN
F 3 "~" H 3500 2850 50  0001 C CNN
	1    3500 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal Y?
U 1 1 5D4B7E09
P 3500 2050
F 0 "Y?" V 3454 2181 50  0000 L CNN
F 1 "32.768 kHz" V 3545 2181 50  0000 L CNN
F 2 "" H 3500 2050 50  0001 C CNN
F 3 "~" H 3500 2050 50  0001 C CNN
	1    3500 2050
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D4B7EC1
P 4200 1850
F 0 "C?" V 4452 1850 50  0000 C CNN
F 1 "22pF" V 4361 1850 50  0000 C CNN
F 2 "" H 4238 1700 50  0001 C CNN
F 3 "~" H 4200 1850 50  0001 C CNN
	1    4200 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D4B7F99
P 4200 2350
F 0 "C?" V 3948 2350 50  0000 C CNN
F 1 "22pF" V 4039 2350 50  0000 C CNN
F 2 "" H 4238 2200 50  0001 C CNN
F 3 "~" H 4200 2350 50  0001 C CNN
	1    4200 2350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4B802B
P 4500 2500
F 0 "#PWR?" H 4500 2250 50  0001 C CNN
F 1 "GND" H 4505 2327 50  0000 C CNN
F 2 "" H 4500 2500 50  0001 C CNN
F 3 "" H 4500 2500 50  0001 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2350 4500 2350
Connection ~ 4500 2350
Wire Wire Line
	4500 2350 4500 2500
Wire Wire Line
	3300 2350 3500 2350
Wire Wire Line
	3500 2200 3500 2350
Connection ~ 3500 2350
Wire Wire Line
	3500 2350 4050 2350
Wire Wire Line
	4350 1850 4500 1850
Wire Wire Line
	4500 1850 4500 2350
Wire Wire Line
	3500 1900 3500 1850
Wire Wire Line
	3300 1850 3500 1850
Connection ~ 3500 1850
Wire Wire Line
	3500 1850 4050 1850
Wire Wire Line
	3300 2850 3350 2850
Wire Wire Line
	3650 2850 3700 2850
$Comp
L Device:C C?
U 1 1 5D4BB55F
P 3050 1450
F 0 "C?" V 2798 1450 50  0000 C CNN
F 1 "0.1uF" V 2889 1450 50  0000 C CNN
F 2 "" H 3088 1300 50  0001 C CNN
F 3 "~" H 3050 1450 50  0001 C CNN
	1    3050 1450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4BB603
P 3350 1450
F 0 "#PWR?" H 3350 1200 50  0001 C CNN
F 1 "GND" V 3355 1322 50  0000 R CNN
F 2 "" H 3350 1450 50  0001 C CNN
F 3 "" H 3350 1450 50  0001 C CNN
	1    3350 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 1450 2800 1450
Connection ~ 2800 1450
Wire Wire Line
	3350 1450 3200 1450
$EndSCHEMATC
