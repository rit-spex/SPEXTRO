EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L RF_GPS_ublox:MAX-8Q U?
U 1 1 5D4B630F
P 2300 2400
F 0 "U?" H 2300 1614 50  0000 C CNN
F 1 "MAX-8Q" H 2300 1523 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 2700 1750 50  0001 C CNN
F 3 "" H 2300 2400 50  0001 C CNN
	1    2300 2400
	1    0    0    -1  
$EndComp
Text GLabel 1450 2000 0    50   Input ~ 0
COMMS_RX
Text GLabel 1450 2100 0    50   Input ~ 0
COMMS_TX
$Comp
L Device:R R?
U 1 1 5D4B6445
P 3250 2700
F 0 "R?" V 3043 2700 50  0000 C CNN
F 1 "80" V 3134 2700 50  0000 C CNN
F 2 "" V 3180 2700 50  0001 C CNN
F 3 "~" H 3250 2700 50  0001 C CNN
	1    3250 2700
	0    1    1    0   
$EndComp
$Comp
L Device:LED D?
U 1 1 5D4B64CB
P 3850 2700
F 0 "D?" H 3842 2445 50  0000 C CNN
F 1 "LED" H 3842 2536 50  0000 C CNN
F 2 "" H 3850 2700 50  0001 C CNN
F 3 "~" H 3850 2700 50  0001 C CNN
	1    3850 2700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4B6567
P 4100 2900
F 0 "#PWR?" H 4100 2650 50  0001 C CNN
F 1 "GND" H 4105 2727 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2700 3100 2700
Wire Wire Line
	4000 2700 4100 2700
Wire Wire Line
	4100 2700 4100 2900
Wire Wire Line
	1700 2000 1450 2000
Wire Wire Line
	1700 2100 1450 2100
$Comp
L power:GND #PWR?
U 1 1 5D4B6648
P 2300 3400
F 0 "#PWR?" H 2300 3150 50  0001 C CNN
F 1 "GND" H 2305 3227 50  0000 C CNN
F 2 "" H 2300 3400 50  0001 C CNN
F 3 "" H 2300 3400 50  0001 C CNN
	1    2300 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3100 2300 3400
Text GLabel 1150 1300 0    50   Input ~ 0
3.3v
$Comp
L Device:R R?
U 1 1 5D4B6776
P 1400 1300
F 0 "R?" V 1193 1300 50  0000 C CNN
F 1 "10" V 1284 1300 50  0000 C CNN
F 2 "" V 1330 1300 50  0001 C CNN
F 3 "~" H 1400 1300 50  0001 C CNN
	1    1400 1300
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D4B67E5
P 1650 1450
F 0 "C?" H 1765 1496 50  0000 L CNN
F 1 "0.1 uF" H 1765 1405 50  0000 L CNN
F 2 "" H 1688 1300 50  0001 C CNN
F 3 "~" H 1650 1450 50  0001 C CNN
	1    1650 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D4B6874
P 1650 1700
F 0 "#PWR?" H 1650 1450 50  0001 C CNN
F 1 "GND" H 1655 1527 50  0000 C CNN
F 2 "" H 1650 1700 50  0001 C CNN
F 3 "" H 1650 1700 50  0001 C CNN
	1    1650 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1300 1250 1300
Wire Wire Line
	1550 1300 1650 1300
Wire Wire Line
	1650 1600 1650 1700
Connection ~ 1650 1300
Wire Wire Line
	2300 1700 2300 1300
Wire Wire Line
	2300 1300 2200 1300
Wire Wire Line
	2100 1700 2100 1300
Connection ~ 2100 1300
Wire Wire Line
	2100 1300 1950 1300
Wire Wire Line
	2200 1700 2200 1300
Connection ~ 2200 1300
Wire Wire Line
	2200 1300 2100 1300
Wire Wire Line
	1700 2800 850  2800
Wire Wire Line
	850  2800 850  950 
Wire Wire Line
	850  950  1950 950 
Wire Wire Line
	1950 950  1950 1300
Connection ~ 1950 1300
Wire Wire Line
	1950 1300 1650 1300
Wire Notes Line
	4400 600  4400 3750
Wire Notes Line
	4400 3750 600  3750
Wire Notes Line
	600  3750 600  600 
Wire Notes Line
	600  600  4400 600 
Text Notes 1100 800  0    100  ~ 0
GPS Receiver w/ Off-Board Antenna
$Comp
L power:GND #PWR?
U 1 1 5D4B89E6
P 3500 2400
F 0 "#PWR?" H 3500 2150 50  0001 C CNN
F 1 "GND" V 3505 2272 50  0000 R CNN
F 2 "" H 3500 2400 50  0001 C CNN
F 3 "" H 3500 2400 50  0001 C CNN
	1    3500 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 2700 3700 2700
$EndSCHEMATC
