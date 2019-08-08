EESchema Schematic File Version 4
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
L Connector:Micro_SD_Card J?
U 1 1 5D4B7154
P 2100 2300
F 0 "J?" H 2050 1483 50  0000 C CNN
F 1 "Micro_SD_Card" H 2050 1574 50  0000 C CNN
F 2 "" H 3250 2600 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 2100 2300 50  0001 C CNN
	1    2100 2300
	-1   0    0    1   
$EndComp
Text Notes 1750 1400 0    100  ~ 0
Micro SD Storage
Text GLabel 3150 2500 2    50   Input ~ 0
SD_CS
Text GLabel 3150 2400 2    50   Input ~ 0
SD_MOSI
Wire Wire Line
	3000 2500 3150 2500
Wire Wire Line
	3000 2400 3150 2400
Text GLabel 3150 2200 2    50   Input ~ 0
SD_SCLK
Text GLabel 3150 2000 2    50   Input ~ 0
SD_MISO
Wire Wire Line
	3000 2000 3150 2000
Wire Wire Line
	3000 2200 3150 2200
Text GLabel 3150 2300 2    50   Input ~ 0
+3.3v
Wire Wire Line
	3000 2300 3150 2300
$Comp
L power:GND #PWR?
U 1 1 5D4B7356
P 3150 2100
F 0 "#PWR?" H 3150 1850 50  0001 C CNN
F 1 "GND" V 3155 1972 50  0000 R CNN
F 2 "" H 3150 2100 50  0001 C CNN
F 3 "" H 3150 2100 50  0001 C CNN
	1    3150 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 2100 3150 2100
Wire Notes Line
	1000 1200 1000 3100
Wire Notes Line
	1000 3100 3800 3100
Wire Notes Line
	3800 3100 3800 1200
Wire Notes Line
	3800 1200 1000 1200
$EndSCHEMATC
