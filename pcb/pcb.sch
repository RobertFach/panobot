EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:polulu_a4988
LIBS:pcb-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "PanoBot Electronics"
Date "mar. 31 mars 2015"
Rev "1"
Comp "Mindfab.NET"
Comment1 "<C2017> Robert Fach"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 9350 1350
Text Label 9250 1200 1    60   ~ 0
IOREF
Text Label 8900 1200 1    60   ~ 0
Vin
Text Label 8900 2450 0    60   ~ 0
A0
Text Label 8900 2550 0    60   ~ 0
A1
Text Label 8900 2650 0    60   ~ 0
A2
Text Label 8900 2750 0    60   ~ 0
A3
Text Label 8900 2850 0    60   ~ 0
A4
Text Label 8900 2950 0    60   ~ 0
A5
Text Label 8900 3050 0    60   ~ 0
A6
Text Label 8900 3150 0    60   ~ 0
A7
Text Label 8900 3400 0    60   ~ 0
A8
Text Label 8900 3500 0    60   ~ 0
A9
Text Label 8900 3600 0    60   ~ 0
A10
Text Label 8900 3700 0    60   ~ 0
A11
Text Label 8900 3800 0    60   ~ 0
A12
Text Label 8900 3900 0    60   ~ 0
A13
Text Label 8900 4000 0    60   ~ 0
A14
Text Label 8900 4100 0    60   ~ 0
A15
Text Label 10500 4650 1    60   ~ 0
22
Text Label 10400 4650 1    60   ~ 0
24
Text Label 10300 4650 1    60   ~ 0
26
Text Label 10200 4650 1    60   ~ 0
28
Text Label 10100 4650 1    60   ~ 0
30
Text Label 10000 4650 1    60   ~ 0
32
Text Label 9900 4650 1    60   ~ 0
34
Text Label 9800 4650 1    60   ~ 0
36
Text Label 9700 4650 1    60   ~ 0
38
Text Label 9600 4650 1    60   ~ 0
40
Text Label 9500 4650 1    60   ~ 0
42
Text Label 9400 4650 1    60   ~ 0
44
Text Label 9300 4650 1    60   ~ 0
46
Text Label 9200 4650 1    60   ~ 0
48
Text Label 9100 4650 1    60   ~ 0
50(MISO)
Text Label 9000 4650 1    60   ~ 0
52(SCK)
Text Label 10500 5650 1    60   ~ 0
23
Text Label 10400 5650 1    60   ~ 0
25
Text Label 10300 5650 1    60   ~ 0
27
Text Label 10100 5650 1    60   ~ 0
31
Text Label 10200 5650 1    60   ~ 0
29
Text Label 10000 5650 1    60   ~ 0
33
Text Label 9900 5650 1    60   ~ 0
35
Text Label 9800 5650 1    60   ~ 0
37
Text Label 9700 5650 1    60   ~ 0
39
Text Label 9600 5650 1    60   ~ 0
41
Text Label 9500 5650 1    60   ~ 0
43
Text Label 9400 5650 1    60   ~ 0
45
Text Label 9300 5650 1    60   ~ 0
47
Text Label 9200 5650 1    60   ~ 0
49
Text Label 9100 5750 1    60   ~ 0
51(MOSI)
Text Label 9000 5750 1    60   ~ 0
53(SS)
Text Label 10400 4100 0    60   ~ 0
21(SCL)
Text Label 10400 4000 0    60   ~ 0
20(SDA)
Text Label 10400 3900 0    60   ~ 0
19(Rx1)
Text Label 10400 3800 0    60   ~ 0
18(Tx1)
Text Label 10400 3700 0    60   ~ 0
17(Rx2)
Text Label 10400 3600 0    60   ~ 0
16(Tx2)
Text Label 10400 3500 0    60   ~ 0
15(Rx3)
Text Label 10400 3400 0    60   ~ 0
14(Tx3)
Text Label 10400 1550 0    60   ~ 0
13(**)
Text Label 10400 1650 0    60   ~ 0
12(**)
Text Label 10400 1750 0    60   ~ 0
11(**)
Text Label 10400 1850 0    60   ~ 0
10(**)
Text Label 10400 1950 0    60   ~ 0
9(**)
Text Label 10400 2050 0    60   ~ 0
8(**)
Text Label 10400 2450 0    60   ~ 0
7(**)
Text Label 10400 2550 0    60   ~ 0
6(**)
Text Label 10400 2650 0    60   ~ 0
5(**)
Text Label 10400 2750 0    60   ~ 0
4(**)
Text Label 10400 2850 0    60   ~ 0
3(**)
Text Label 10400 2950 0    60   ~ 0
2(**)
Text Label 10400 3050 0    60   ~ 0
1(Tx0)
Text Label 10400 3150 0    60   ~ 0
0(Rx0)
Text Label 10400 1250 0    60   ~ 0
SDA
Text Label 10400 1150 0    60   ~ 0
SCL
Text Label 10400 1350 0    60   ~ 0
AREF
Text Notes 8375 575  0    60   ~ 0
Shield for Arduino Mega Rev 3
Text Notes 10700 1000 0    60   ~ 0
Holes
$Comp
L CONN_01X01 P8
U 1 1 56D70B71
P 10600 650
F 0 "P8" V 10700 650 31  0000 C CNN
F 1 "CONN_01X01" V 10700 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 10600 650 50  0001 C CNN
F 3 "" H 10600 650 50  0000 C CNN
	1    10600 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P9
U 1 1 56D70C9B
P 10700 650
F 0 "P9" V 10800 650 31  0000 C CNN
F 1 "CONN_01X01" V 10800 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 10700 650 50  0001 C CNN
F 3 "" H 10700 650 50  0000 C CNN
	1    10700 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P10
U 1 1 56D70CE6
P 10800 650
F 0 "P10" V 10900 650 31  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 10800 650 50  0001 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P11
U 1 1 56D70D2C
P 10900 650
F 0 "P11" V 11000 650 31  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 10900 650 50  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P12
U 1 1 56D711A2
P 11000 650
F 0 "P12" V 11100 650 31  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 11000 650 50  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P13
U 1 1 56D711F0
P 11100 650
F 0 "P13" V 11200 650 31  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Mega:Arduino_1pin" H 11100 650 50  0001 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10600 850 
NoConn ~ 10700 850 
NoConn ~ 10800 850 
NoConn ~ 10900 850 
NoConn ~ 11000 850 
NoConn ~ 11100 850 
$Comp
L CONN_01X08 P2
U 1 1 56D71773
P 9550 1700
F 0 "P2" H 9550 2150 50  0000 C CNN
F 1 "Power" V 9650 1700 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x08" H 9550 1700 50  0001 C CNN
F 3 "" H 9550 1700 50  0000 C CNN
	1    9550 1700
	1    0    0    -1  
$EndComp
Text Notes 9650 1350 0    60   ~ 0
1
$Comp
L +3.3V #PWR01
U 1 1 56D71AA9
P 9100 1200
F 0 "#PWR01" H 9100 1050 50  0001 C CNN
F 1 "+3.3V" H 9100 1340 50  0000 C CNN
F 2 "" H 9100 1200 50  0000 C CNN
F 3 "" H 9100 1200 50  0000 C CNN
	1    9100 1200
	1    0    0    -1  
$EndComp
Text Label 8600 1550 0    60   ~ 0
Reset
$Comp
L +5V #PWR02
U 1 1 56D71D10
P 9000 1050
F 0 "#PWR02" H 9000 900 50  0001 C CNN
F 1 "+5V" H 9000 1190 50  0000 C CNN
F 2 "" H 9000 1050 50  0000 C CNN
F 3 "" H 9000 1050 50  0000 C CNN
	1    9000 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 56D721E6
P 9250 2150
F 0 "#PWR03" H 9250 1900 50  0001 C CNN
F 1 "GND" H 9250 2000 50  0000 C CNN
F 2 "" H 9250 2150 50  0000 C CNN
F 3 "" H 9250 2150 50  0000 C CNN
	1    9250 2150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P5
U 1 1 56D72368
P 9950 1600
F 0 "P5" H 9950 2150 50  0000 C CNN
F 1 "PWM" V 10050 1600 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x10" H 9950 1600 50  0001 C CNN
F 3 "" H 9950 1600 50  0000 C CNN
	1    9950 1600
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 56D72A3D
P 10250 2150
F 0 "#PWR04" H 10250 1900 50  0001 C CNN
F 1 "GND" H 10250 2000 50  0000 C CNN
F 2 "" H 10250 2150 50  0000 C CNN
F 3 "" H 10250 2150 50  0000 C CNN
	1    10250 2150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P3
U 1 1 56D72F1C
P 9550 2800
F 0 "P3" H 9550 3250 50  0000 C CNN
F 1 "Analog" V 9650 2800 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x08" H 9550 2800 50  0001 C CNN
F 3 "" H 9550 2800 50  0000 C CNN
	1    9550 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P6
U 1 1 56D734D0
P 9950 2800
F 0 "P6" H 9950 3250 50  0000 C CNN
F 1 "PWM" V 10050 2800 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x08" H 9950 2800 50  0001 C CNN
F 3 "" H 9950 2800 50  0000 C CNN
	1    9950 2800
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X08 P4
U 1 1 56D73A0E
P 9550 3750
F 0 "P4" H 9550 4200 50  0000 C CNN
F 1 "Analog" V 9650 3750 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x08" H 9550 3750 50  0001 C CNN
F 3 "" H 9550 3750 50  0000 C CNN
	1    9550 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P7
U 1 1 56D73F2C
P 9950 3750
F 0 "P7" H 9950 4200 50  0000 C CNN
F 1 "Communication" V 10050 3750 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_1x08" H 9950 3750 50  0001 C CNN
F 3 "" H 9950 3750 50  0000 C CNN
	1    9950 3750
	-1   0    0    -1  
$EndComp
$Comp
L CONN_02X18 P1
U 1 1 56D743B5
P 9750 5100
F 0 "P1" H 9750 6050 50  0000 C CNN
F 1 "Digital" V 9750 5100 50  0000 C CNN
F 2 "Socket_Arduino_Mega:Socket_Strip_Arduino_2x18" H 9750 4050 50  0001 C CNN
F 3 "" H 9750 4050 50  0000 C CNN
	1    9750 5100
	0    -1   1    0   
$EndComp
Wire Wire Line
	9100 1200 9100 1650
Wire Wire Line
	9250 1450 9250 1200
Wire Wire Line
	9350 1450 9250 1450
Wire Notes Line
	10450 1000 10450 500 
Wire Notes Line
	11200 1000 10450 1000
Wire Notes Line
	9850 650  9850 475 
Wire Notes Line
	8350 650  9850 650 
Wire Wire Line
	9100 1650 9350 1650
Wire Wire Line
	9000 1050 9000 1750
Wire Wire Line
	9000 1750 9350 1750
Wire Wire Line
	9350 2050 8900 2050
Wire Wire Line
	8900 2050 8900 1200
Wire Wire Line
	8600 1550 9350 1550
Wire Wire Line
	9350 1850 9250 1850
Wire Wire Line
	9250 1850 9250 2150
Wire Wire Line
	9350 1950 9250 1950
Connection ~ 9250 1950
Wire Wire Line
	10150 1150 10400 1150
Wire Wire Line
	10400 1250 10150 1250
Wire Wire Line
	10150 1350 10400 1350
Wire Wire Line
	10150 1550 10400 1550
Wire Wire Line
	10400 1650 10150 1650
Wire Wire Line
	10150 1750 10400 1750
Wire Wire Line
	10150 1850 10400 1850
Wire Wire Line
	10400 1950 10150 1950
Wire Wire Line
	10150 2050 10400 2050
Wire Wire Line
	10250 2150 10250 1450
Wire Wire Line
	10250 1450 10150 1450
Wire Wire Line
	9350 2450 8900 2450
Wire Wire Line
	8900 2550 9350 2550
Wire Wire Line
	9350 2650 8900 2650
Wire Wire Line
	8900 2750 9350 2750
Wire Wire Line
	9350 2850 8900 2850
Wire Wire Line
	8900 2950 9350 2950
Wire Wire Line
	9350 3050 8900 3050
Wire Wire Line
	8900 3150 9350 3150
Wire Wire Line
	10400 2450 10150 2450
Wire Wire Line
	10150 2550 10400 2550
Wire Wire Line
	10400 2650 10150 2650
Wire Wire Line
	10150 2750 10400 2750
Wire Wire Line
	10400 2850 10150 2850
Wire Wire Line
	10150 2950 10400 2950
Wire Wire Line
	10400 3050 10150 3050
Wire Wire Line
	10150 3150 10400 3150
Wire Wire Line
	9350 3400 8900 3400
Wire Wire Line
	8900 3500 9350 3500
Wire Wire Line
	9350 3600 8900 3600
Wire Wire Line
	8900 3700 9350 3700
Wire Wire Line
	9350 3800 8900 3800
Wire Wire Line
	8900 3900 9350 3900
Wire Wire Line
	9350 4000 8900 4000
Wire Wire Line
	8900 4100 9350 4100
Wire Wire Line
	10400 3400 10150 3400
Wire Wire Line
	10150 3500 10400 3500
Wire Wire Line
	10400 3600 10150 3600
Wire Wire Line
	10150 3700 10400 3700
Wire Wire Line
	10400 3800 10150 3800
Wire Wire Line
	10150 3900 10400 3900
Wire Wire Line
	10400 4000 10150 4000
Wire Wire Line
	10150 4100 10400 4100
Wire Wire Line
	10500 4850 10500 4650
Wire Wire Line
	10400 4850 10400 4650
Wire Wire Line
	10300 4850 10300 4650
Wire Wire Line
	10200 4850 10200 4650
Wire Wire Line
	10100 4850 10100 4650
Wire Wire Line
	10000 4850 10000 4650
Wire Wire Line
	9900 4850 9900 4650
Wire Wire Line
	9800 4850 9800 4650
Wire Wire Line
	9700 4850 9700 4650
Wire Wire Line
	9600 4850 9600 4650
Wire Wire Line
	9500 4850 9500 4650
Wire Wire Line
	9400 4850 9400 4650
Wire Wire Line
	9300 4850 9300 4650
Wire Wire Line
	9200 4850 9200 4650
Wire Wire Line
	9100 4850 9100 4650
Wire Wire Line
	9000 4850 9000 4650
Wire Wire Line
	10500 5350 10500 5650
Wire Wire Line
	10400 5350 10400 5650
Wire Wire Line
	10300 5350 10300 5650
Wire Wire Line
	10200 5350 10200 5650
Wire Wire Line
	10100 5350 10100 5650
Wire Wire Line
	10000 5350 10000 5650
Wire Wire Line
	9900 5350 9900 5650
Wire Wire Line
	9800 5350 9800 5650
Wire Wire Line
	9700 5350 9700 5650
Wire Wire Line
	9600 5350 9600 5650
Wire Wire Line
	9500 5350 9500 5650
Wire Wire Line
	9400 5350 9400 5650
Wire Wire Line
	9300 5350 9300 5650
Wire Wire Line
	9200 5350 9200 5650
Wire Wire Line
	9100 5350 9100 5750
Wire Wire Line
	9000 5350 9000 5750
Wire Wire Line
	8900 4850 8650 4850
$Comp
L GND #PWR05
U 1 1 56D758F6
P 8650 5750
F 0 "#PWR05" H 8650 5500 50  0001 C CNN
F 1 "GND" H 8650 5600 50  0000 C CNN
F 2 "" H 8650 5750 50  0000 C CNN
F 3 "" H 8650 5750 50  0000 C CNN
	1    8650 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 5350 8650 5350
Connection ~ 8650 5350
Wire Wire Line
	10750 5350 10600 5350
Wire Wire Line
	10750 4850 10600 4850
$Comp
L +5V #PWR06
U 1 1 56D75AB8
P 10750 4550
F 0 "#PWR06" H 10750 4400 50  0001 C CNN
F 1 "+5V" H 10750 4690 50  0000 C CNN
F 2 "" H 10750 4550 50  0000 C CNN
F 3 "" H 10750 4550 50  0000 C CNN
	1    10750 4550
	1    0    0    -1  
$EndComp
Connection ~ 10750 4850
Wire Wire Line
	10750 4550 10750 5350
Wire Wire Line
	8650 4850 8650 5750
Wire Notes Line
	11200 6050 8350 6050
Wire Notes Line
	8350 6050 8350 500 
$Comp
L POLOLU_A4988 U1
U 1 1 59F1166C
P 6150 1450
F 0 "U1" H 6150 1900 60  0000 C CNN
F 1 "POLOLU_A4988" V 6150 1450 50  0000 C CNN
F 2 "" H 6150 1450 60  0001 C CNN
F 3 "" H 6150 1450 60  0001 C CNN
	1    6150 1450
	1    0    0    -1  
$EndComp
$Comp
L POLOLU_A4988 U2
U 1 1 59F11701
P 6150 3000
F 0 "U2" H 6150 3450 60  0000 C CNN
F 1 "POLOLU_A4988" V 6150 3000 50  0000 C CNN
F 2 "" H 6150 3000 60  0001 C CNN
F 3 "" H 6150 3000 60  0001 C CNN
	1    6150 3000
	1    0    0    -1  
$EndComp
Text Notes 5950 3550 0    60   ~ 0
TILT Stepper
Text Notes 5900 2000 0    60   ~ 0
PAN Stepper
Wire Wire Line
	6750 1200 7100 1200
Wire Wire Line
	6750 1100 7100 1100
Text Label 7000 1200 0    60   ~ 0
24
Text Label 7000 1100 0    60   ~ 0
25
Wire Wire Line
	6750 2650 7100 2650
Wire Wire Line
	6750 2750 7100 2750
Text Label 6950 2750 0    60   ~ 0
26
Text Label 6950 2650 0    60   ~ 0
27
Wire Wire Line
	6750 2850 6750 2950
Wire Wire Line
	6750 1300 6750 1400
$Comp
L GND #PWR07
U 1 1 59F1257C
P 1050 6300
F 0 "#PWR07" H 1050 6050 50  0001 C CNN
F 1 "GND" H 1050 6150 50  0000 C CNN
F 2 "" H 1050 6300 50  0001 C CNN
F 3 "" H 1050 6300 50  0001 C CNN
	1    1050 6300
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x05_Odd_Even J1
U 1 1 59F126DA
P 1450 5900
F 0 "J1" H 1500 6200 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1500 5600 50  0000 C CNN
F 2 "" H 1450 5900 50  0001 C CNN
F 3 "" H 1450 5900 50  0001 C CNN
	1    1450 5900
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x05_Odd_Even J2
U 1 1 59F127A5
P 1450 6800
F 0 "J2" H 1500 7100 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1500 6500 50  0000 C CNN
F 2 "" H 1450 6800 50  0001 C CNN
F 3 "" H 1450 6800 50  0001 C CNN
	1    1450 6800
	1    0    0    -1  
$EndComp
Text Notes 1450 6350 0    60   ~ 0
Display - Exp1
Text Notes 1450 7250 0    60   ~ 0
Display - Exp2
Wire Wire Line
	1050 6300 1050 6100
Wire Wire Line
	1050 6100 1250 6100
$Comp
L GND #PWR08
U 1 1 59F12AD7
P 1050 7350
F 0 "#PWR08" H 1050 7100 50  0001 C CNN
F 1 "GND" H 1050 7200 50  0000 C CNN
F 2 "" H 1050 7350 50  0001 C CNN
F 3 "" H 1050 7350 50  0001 C CNN
	1    1050 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 7350 1050 7000
Wire Wire Line
	1050 7000 1250 7000
Wire Wire Line
	1750 5700 2100 5700
Text Label 1950 5700 0    60   ~ 0
44
Wire Wire Line
	1750 6900 2100 6900
Text Label 1950 6900 0    60   ~ 0
45
Wire Wire Line
	1250 6700 950  6700
Wire Wire Line
	1250 6800 950  6800
Text Label 1050 6700 0    60   ~ 0
A8
Text Label 1050 6800 0    60   ~ 0
A9
Wire Wire Line
	1750 5800 2100 5800
Text Label 1950 5800 0    60   ~ 0
34
Wire Wire Line
	1250 5800 950  5800
Wire Wire Line
	1250 5900 950  5900
Text Label 1100 5900 0    60   ~ 0
52(SCK)
Text Label 1100 5800 0    60   ~ 0
51(MOSI)
NoConn ~ 1750 5900
NoConn ~ 1250 6000
NoConn ~ 1750 6000
NoConn ~ 1250 6600
NoConn ~ 1750 6600
NoConn ~ 1750 6700
NoConn ~ 1750 6800
NoConn ~ 1750 7000
NoConn ~ 1250 6900
$Comp
L L7809 U3
U 1 1 59F4D1D7
P 2400 1400
F 0 "U3" H 2250 1525 50  0000 C CNN
F 1 "L7809" H 2400 1525 50  0000 L CNN
F 2 "" H 2425 1250 50  0001 L CIN
F 3 "" H 2400 1350 50  0001 C CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 59F4D538
P 2400 2150
F 0 "#PWR09" H 2400 1900 50  0001 C CNN
F 1 "GND" H 2400 2000 50  0000 C CNN
F 2 "" H 2400 2150 50  0001 C CNN
F 3 "" H 2400 2150 50  0001 C CNN
	1    2400 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1700 2400 2150
$Comp
L C C2
U 1 1 59F4D68B
P 1850 1750
F 0 "C2" H 1875 1850 50  0000 L CNN
F 1 "0.33uF" H 1875 1650 50  0000 L CNN
F 2 "" H 1888 1600 50  0001 C CNN
F 3 "" H 1850 1750 50  0001 C CNN
	1    1850 1750
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 59F4D794
P 3000 1750
F 0 "C3" H 3025 1850 50  0000 L CNN
F 1 "0.1uF" H 3025 1650 50  0000 L CNN
F 2 "" H 3038 1600 50  0001 C CNN
F 3 "" H 3000 1750 50  0001 C CNN
	1    3000 1750
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 59F4D80C
P 1450 1750
F 0 "C1" H 1475 1850 50  0000 L CNN
F 1 "100uF" H 1475 1650 50  0000 L CNN
F 2 "" H 1488 1600 50  0001 C CNN
F 3 "" H 1450 1750 50  0001 C CNN
	1    1450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2000 3400 2000
Wire Wire Line
	1850 1900 1850 2800
Connection ~ 2400 2000
Wire Wire Line
	1450 1900 1450 2150
Connection ~ 1850 2000
Wire Wire Line
	3000 2000 3000 1900
Wire Wire Line
	3000 1400 3000 1600
Wire Wire Line
	2700 1400 3800 1400
Wire Wire Line
	1850 1400 1850 1600
Connection ~ 1850 1400
Wire Wire Line
	1450 1400 1450 1600
Connection ~ 3000 1400
Text Label 3650 1400 0    60   ~ 0
Vin
Connection ~ 1450 1400
$Comp
L D D1
U 1 1 59F4E5B7
P 1150 1400
F 0 "D1" H 1150 1500 50  0000 C CNN
F 1 "1N4007" H 1150 1300 50  0000 C CNN
F 2 "" H 1150 1400 50  0001 C CNN
F 3 "" H 1150 1400 50  0001 C CNN
	1    1150 1400
	-1   0    0    1   
$EndComp
$Comp
L CP C4
U 1 1 59F4EB1D
P 3400 1750
F 0 "C4" H 3425 1850 50  0000 L CNN
F 1 "100uF" H 3425 1650 50  0000 L CNN
F 2 "" H 3438 1600 50  0001 C CNN
F 3 "" H 3400 1750 50  0001 C CNN
	1    3400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2000 3400 1900
Connection ~ 3000 2000
Wire Wire Line
	3400 1600 3400 1400
Connection ~ 3400 1400
$Comp
L D D2
U 1 1 59F4EF7B
P 2400 1000
F 0 "D2" H 2400 1100 50  0000 C CNN
F 1 "1N4007" H 2400 900 50  0000 C CNN
F 2 "" H 2400 1000 50  0001 C CNN
F 3 "" H 2400 1000 50  0001 C CNN
	1    2400 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1000 2800 1000
Wire Wire Line
	2800 1000 2800 1400
Connection ~ 2800 1400
Wire Wire Line
	2250 1000 2050 1000
Wire Wire Line
	2050 1000 2050 1400
Connection ~ 2050 1400
Wire Wire Line
	1750 6100 2100 6100
Text Label 2000 6100 0    60   ~ 0
+5V
Wire Wire Line
	1300 1400 2100 1400
NoConn ~ 10150 1950
NoConn ~ 10150 1850
Text Label 10650 1950 0    60   ~ 0
HostShield
Text Label 10700 1850 0    60   ~ 0
HostShield
$Comp
L Conn_01x02 J3
U 1 1 59F5C373
P 1250 2350
F 0 "J3" H 1250 2450 50  0000 C CNN
F 1 "Conn_01x02" H 1250 2150 50  0000 C CNN
F 2 "" H 1250 2350 50  0001 C CNN
F 3 "" H 1250 2350 50  0001 C CNN
	1    1250 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 2150 1150 2150
Wire Wire Line
	1000 1150 1000 2150
Wire Wire Line
	1450 2150 1250 2150
Connection ~ 1450 2000
Text Notes 1200 2550 0    60   ~ 0
Cooling Fan
$Comp
L Conn_01x06 J4
U 1 1 59F5CCA5
P 1450 4850
F 0 "J4" H 1450 5150 50  0000 C CNN
F 1 "Conn_01x06" H 1450 4450 50  0000 C CNN
F 2 "" H 1450 4850 50  0001 C CNN
F 3 "" H 1450 4850 50  0001 C CNN
	1    1450 4850
	-1   0    0    1   
$EndComp
Wire Notes Line
	500  5300 6950 5300
Wire Notes Line
	3050 4100 3050 7450
Text Notes 1000 5450 0    60   ~ 0
Full Graphic LCD Connector
Wire Notes Line
	500  4100 8350 4100
Text Notes 1200 4250 0    60   ~ 0
GPS Connector
$Comp
L GND #PWR010
U 1 1 59F5D0FD
P 1900 5050
F 0 "#PWR010" H 1900 4800 50  0001 C CNN
F 1 "GND" H 1900 4900 50  0000 C CNN
F 2 "" H 1900 5050 50  0001 C CNN
F 3 "" H 1900 5050 50  0001 C CNN
	1    1900 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5050 1650 5050
Wire Wire Line
	1650 4950 2100 4950
Text Label 1950 4950 0    60   ~ 0
+5V
Wire Wire Line
	1650 4850 2350 4850
Text Label 2300 4850 0    60   ~ 0
18(Tx1)
Wire Wire Line
	1650 4750 2350 4750
Text Label 2300 4750 0    60   ~ 0
19(Rx1)
Wire Wire Line
	1650 4650 2100 4650
Wire Wire Line
	1650 4550 2100 4550
Text Label 2050 4650 0    60   ~ 0
20(SDA)
Text Label 2050 4550 0    60   ~ 0
21(SCL)
Wire Notes Line
	4100 4100 4100 550 
Text Notes 1650 650  0    60   ~ 0
External Power Supply
Wire Wire Line
	1250 5700 950  5700
Text Label 1000 5700 0    60   ~ 0
43
$Comp
L LTV-827 U4
U 1 1 59F5EE68
P 4800 6500
F 0 "U4" H 4600 6900 50  0000 L CNN
F 1 "LTV-827" H 4800 6900 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 4600 6150 50  0001 L CIN
F 3 "" H 4800 6400 50  0001 L CNN
	1    4800 6500
	-1   0    0    1   
$EndComp
$Comp
L Audio-Jack-3 J6
U 1 1 59F5EF7B
P 3750 6400
F 0 "J6" H 3700 6575 50  0000 C CNN
F 1 "Audio-Jack-3" H 3850 6330 50  0000 C CNN
F 2 "" H 4000 6500 50  0001 C CNN
F 3 "" H 4000 6500 50  0001 C CNN
	1    3750 6400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J8
U 1 1 59F5F00C
P 4700 1500
F 0 "J8" H 4700 1700 50  0000 C CNN
F 1 "Conn_01x04" H 4700 1200 50  0000 C CNN
F 2 "" H 4700 1500 50  0001 C CNN
F 3 "" H 4700 1500 50  0001 C CNN
	1    4700 1500
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x04 J9
U 1 1 59F5F172
P 4700 3050
F 0 "J9" H 4700 3250 50  0000 C CNN
F 1 "Conn_01x04" H 4700 2750 50  0000 C CNN
F 2 "" H 4700 3050 50  0001 C CNN
F 3 "" H 4700 3050 50  0001 C CNN
	1    4700 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 1600 4900 1600
Wire Wire Line
	4900 1500 5550 1500
Wire Wire Line
	5550 1400 4900 1400
Wire Wire Line
	5550 1300 4900 1300
Wire Wire Line
	4900 3150 5550 3150
Wire Wire Line
	5550 3050 4900 3050
Wire Wire Line
	4900 2950 5550 2950
Wire Wire Line
	5550 2850 4900 2850
$Comp
L CP C5
U 1 1 59F5FACF
P 5300 1850
F 0 "C5" H 5325 1950 50  0000 L CNN
F 1 "100uF" H 5325 1750 50  0000 L CNN
F 2 "" H 5338 1700 50  0001 C CNN
F 3 "" H 5300 1850 50  0001 C CNN
	1    5300 1850
	-1   0    0    1   
$EndComp
$Comp
L CP C6
U 1 1 59F5FB59
P 5300 3400
F 0 "C6" H 5325 3500 50  0000 L CNN
F 1 "100uF" H 5325 3300 50  0000 L CNN
F 2 "" H 5338 3250 50  0001 C CNN
F 3 "" H 5300 3400 50  0001 C CNN
	1    5300 3400
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J5
U 1 1 59F605B7
P 600 1250
F 0 "J5" H 600 1350 50  0000 C CNN
F 1 "Conn_01x02" H 600 1050 50  0000 C CNN
F 2 "" H 600 1250 50  0001 C CNN
F 3 "" H 600 1250 50  0001 C CNN
	1    600  1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	800  1150 1000 1150
Connection ~ 1000 1400
Wire Wire Line
	800  1250 800  2800
Wire Wire Line
	800  2800 1850 2800
Text Label 900  1150 0    60   ~ 0
ExtVcc
Wire Wire Line
	5000 3250 5550 3250
Wire Wire Line
	5550 3350 5550 3550
Wire Wire Line
	5550 3550 5300 3550
$Comp
L GND #PWR011
U 1 1 59F60DC8
P 5000 3700
F 0 "#PWR011" H 5000 3450 50  0001 C CNN
F 1 "GND" H 5000 3550 50  0000 C CNN
F 2 "" H 5000 3700 50  0001 C CNN
F 3 "" H 5000 3700 50  0001 C CNN
	1    5000 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3700 5000 3250
Connection ~ 5300 3250
Wire Wire Line
	5550 1700 5300 1700
Wire Wire Line
	5550 2000 5550 1800
Wire Wire Line
	4250 2000 5550 2000
Connection ~ 5300 2000
Wire Wire Line
	5300 3550 5300 3950
Wire Wire Line
	5300 3950 4350 3950
Wire Wire Line
	4350 3950 4350 2000
Connection ~ 4350 2000
Text Label 4250 1950 0    60   ~ 0
ExtVcc
Text Notes 4450 2700 0    60   ~ 0
Tilt Stepper
Text Notes 4450 1150 0    60   ~ 0
Pan Stepper
$Comp
L GND #PWR012
U 1 1 59F619D0
P 5550 2550
F 0 "#PWR012" H 5550 2300 50  0001 C CNN
F 1 "GND" H 5550 2400 50  0000 C CNN
F 2 "" H 5550 2550 50  0001 C CNN
F 3 "" H 5550 2550 50  0001 C CNN
	1    5550 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 2550 5550 2650
$Comp
L GND #PWR013
U 1 1 59F61C38
P 5550 1000
F 0 "#PWR013" H 5550 750 50  0001 C CNN
F 1 "GND" H 5550 850 50  0000 C CNN
F 2 "" H 5550 1000 50  0001 C CNN
F 3 "" H 5550 1000 50  0001 C CNN
	1    5550 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 1000 5550 1100
Wire Wire Line
	5550 2750 5300 2750
Wire Wire Line
	5300 2750 5300 2400
Wire Wire Line
	5550 1200 5350 1200
Wire Wire Line
	5350 1200 5350 850 
Text Label 5150 950  0    60   ~ 0
+5V
Text Label 5100 2500 0    60   ~ 0
+5V
NoConn ~ 6750 1800
NoConn ~ 6750 3350
$Comp
L R R4
U 1 1 59F62163
P 7000 3550
F 0 "R4" V 7080 3550 50  0000 C CNN
F 1 "100k" V 7000 3550 50  0000 C CNN
F 2 "" V 6930 3550 50  0001 C CNN
F 3 "" H 7000 3550 50  0001 C CNN
	1    7000 3550
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 59F62200
P 7000 2050
F 0 "R3" V 7080 2050 50  0000 C CNN
F 1 "100k" V 7000 2050 50  0000 C CNN
F 2 "" V 6930 2050 50  0001 C CNN
F 3 "" H 7000 2050 50  0001 C CNN
	1    7000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3250 7250 3250
Wire Wire Line
	7000 1700 7000 1900
Wire Wire Line
	7000 3250 7000 3400
$Comp
L GND #PWR014
U 1 1 59F6247F
P 7000 3800
F 0 "#PWR014" H 7000 3550 50  0001 C CNN
F 1 "GND" H 7000 3650 50  0000 C CNN
F 2 "" H 7000 3800 50  0001 C CNN
F 3 "" H 7000 3800 50  0001 C CNN
	1    7000 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 59F624F3
P 7000 2300
F 0 "#PWR015" H 7000 2050 50  0001 C CNN
F 1 "GND" H 7000 2150 50  0000 C CNN
F 2 "" H 7000 2300 50  0001 C CNN
F 3 "" H 7000 2300 50  0001 C CNN
	1    7000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2200 7000 2300
Wire Wire Line
	7000 3700 7000 3800
$Comp
L Jumper_NO_Small JP6
U 1 1 59F6278A
P 7350 3250
F 0 "JP6" H 7350 3330 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 3190 50  0000 C CNN
F 2 "" H 7350 3250 50  0001 C CNN
F 3 "" H 7350 3250 50  0001 C CNN
	1    7350 3250
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP5
U 1 1 59F62881
P 7350 3150
F 0 "JP5" H 7350 3230 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 3090 50  0000 C CNN
F 2 "" H 7350 3150 50  0001 C CNN
F 3 "" H 7350 3150 50  0001 C CNN
	1    7350 3150
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP4
U 1 1 59F62928
P 7350 3050
F 0 "JP4" H 7350 3130 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 2990 50  0000 C CNN
F 2 "" H 7350 3050 50  0001 C CNN
F 3 "" H 7350 3050 50  0001 C CNN
	1    7350 3050
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 59F62C6C
P 7650 2850
F 0 "R6" V 7730 2850 50  0000 C CNN
F 1 "4.7k" V 7650 2850 50  0000 C CNN
F 2 "" V 7580 2850 50  0001 C CNN
F 3 "" H 7650 2850 50  0001 C CNN
	1    7650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3050 7250 3050
Wire Wire Line
	6750 3150 7250 3150
Connection ~ 7000 1700
Wire Wire Line
	7450 3050 7650 3050
Wire Wire Line
	7650 3000 7650 3250
Wire Wire Line
	7650 3150 7450 3150
Connection ~ 7650 3050
Wire Wire Line
	7650 3250 7450 3250
Connection ~ 7650 3150
Wire Wire Line
	7650 2700 7650 2400
Text Label 7650 2500 0    60   ~ 0
+5V
$Comp
L Jumper_NO_Small JP1
U 1 1 59F63AC8
P 7350 1500
F 0 "JP1" H 7350 1580 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 1440 50  0000 C CNN
F 2 "" H 7350 1500 50  0001 C CNN
F 3 "" H 7350 1500 50  0001 C CNN
	1    7350 1500
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP2
U 1 1 59F63C6A
P 7350 1600
F 0 "JP2" H 7350 1680 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 1540 50  0000 C CNN
F 2 "" H 7350 1600 50  0001 C CNN
F 3 "" H 7350 1600 50  0001 C CNN
	1    7350 1600
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP3
U 1 1 59F63CF5
P 7350 1700
F 0 "JP3" H 7350 1780 50  0000 C CNN
F 1 "Jumper_NO_Small" H 7360 1640 50  0000 C CNN
F 2 "" H 7350 1700 50  0001 C CNN
F 3 "" H 7350 1700 50  0001 C CNN
	1    7350 1700
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59F63D8F
P 7650 1300
F 0 "R5" V 7730 1300 50  0000 C CNN
F 1 "4.7k" V 7650 1300 50  0000 C CNN
F 2 "" V 7580 1300 50  0001 C CNN
F 3 "" H 7650 1300 50  0001 C CNN
	1    7650 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 1150 7650 750 
Text Label 7650 850  0    60   ~ 0
+5V
Wire Wire Line
	6750 1700 7250 1700
Wire Wire Line
	7450 1700 7650 1700
Wire Wire Line
	7650 1700 7650 1450
Wire Wire Line
	7450 1600 7650 1600
Connection ~ 7650 1600
Wire Wire Line
	7450 1500 7650 1500
Connection ~ 7650 1500
Wire Wire Line
	7250 1600 6750 1600
Wire Wire Line
	7250 1500 6750 1500
$Comp
L R R2
U 1 1 59F64FD1
P 5450 6800
F 0 "R2" V 5530 6800 50  0000 C CNN
F 1 "1k" V 5450 6800 50  0000 C CNN
F 2 "" V 5380 6800 50  0001 C CNN
F 3 "" H 5450 6800 50  0001 C CNN
	1    5450 6800
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 59F651B9
P 5450 6500
F 0 "R1" V 5530 6500 50  0000 C CNN
F 1 "1k" V 5450 6500 50  0000 C CNN
F 2 "" V 5380 6500 50  0001 C CNN
F 3 "" H 5450 6500 50  0001 C CNN
	1    5450 6500
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 6500 5300 6500
Wire Wire Line
	5100 6800 5300 6800
Wire Wire Line
	5600 6500 6100 6500
Wire Wire Line
	5600 6800 6100 6800
Wire Wire Line
	4500 6600 3550 6600
Wire Wire Line
	3550 6600 3550 6500
Wire Wire Line
	4500 6500 4300 6500
Wire Wire Line
	4300 6500 4300 6300
Wire Wire Line
	4300 6300 3950 6300
Wire Wire Line
	3950 6400 4200 6400
Wire Wire Line
	4200 6400 4200 6800
Wire Wire Line
	4200 6800 4500 6800
Wire Wire Line
	4500 6300 4450 6300
Wire Wire Line
	4450 6300 4450 6600
Connection ~ 4450 6600
$Comp
L GND #PWR016
U 1 1 59F66394
P 6500 6600
F 0 "#PWR016" H 6500 6350 50  0001 C CNN
F 1 "GND" H 6500 6450 50  0000 C CNN
F 2 "" H 6500 6600 50  0001 C CNN
F 3 "" H 6500 6600 50  0001 C CNN
	1    6500 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 6600 5100 6600
Wire Wire Line
	6500 6600 6500 6300
Wire Wire Line
	6500 6300 5100 6300
Wire Notes Line
	6950 4100 6950 6500
Text Notes 4150 5550 0    60   ~ 0
Remote Focus/Shutter Canon (et.al)
Text Label 3950 6250 0    60   ~ 0
focus
Text Label 3950 6400 0    60   ~ 0
shutter
Text Label 5950 6500 0    60   ~ 0
22
Text Label 5950 6800 0    60   ~ 0
23
Text Notes 5750 650  0    60   ~ 0
Motion/Stepper Control
$Comp
L GND #PWR017
U 1 1 59F67AD2
P 4300 5050
F 0 "#PWR017" H 4300 4800 50  0001 C CNN
F 1 "GND" H 4300 4900 50  0000 C CNN
F 2 "" H 4300 5050 50  0001 C CNN
F 3 "" H 4300 5050 50  0001 C CNN
	1    4300 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5050 4300 5050
Wire Wire Line
	4100 4950 4600 4950
Text Label 4500 4950 0    60   ~ 0
+5V
Wire Wire Line
	4100 4850 4950 4850
Wire Wire Line
	4100 4750 4950 4750
Text Label 4850 4850 0    60   ~ 0
16(Tx2)
Text Label 4850 4750 0    60   ~ 0
17(Rx2)
$Comp
L Conn_02x04_Top_Bottom J7
U 1 1 59F68717
P 3800 4850
F 0 "J7" H 3850 5050 50  0000 C CNN
F 1 "Conn_02x04_Top_Bottom" H 3850 4550 50  0000 C CNN
F 2 "" H 3800 4850 50  0001 C CNN
F 3 "" H 3800 4850 50  0001 C CNN
	1    3800 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 5050 4150 5050
Connection ~ 4150 5050
Wire Wire Line
	3600 4950 4150 4950
Connection ~ 4150 4950
Wire Wire Line
	3600 4850 3200 4850
Wire Wire Line
	3600 4750 3200 4750
Text Label 3250 4850 0    60   ~ 0
14(Tx3)
Text Label 3250 4750 0    60   ~ 0
15(Rx3)
Text Notes 3700 4300 0    60   ~ 0
Serial Aux
Wire Notes Line
	5400 4100 5400 5300
$Comp
L Conn_02x06_Odd_Even J?
U 1 1 59F6901C
P 6150 4800
F 0 "J?" H 6200 5100 50  0000 C CNN
F 1 "Conn_02x06_Odd_Even" H 6200 4400 50  0000 C CNN
F 2 "" H 6150 4800 50  0001 C CNN
F 3 "" H 6150 4800 50  0001 C CNN
	1    6150 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4600 5600 4600
Text Label 5650 4600 0    60   ~ 0
A10
Wire Wire Line
	5950 4700 5600 4700
Text Label 5650 4700 0    60   ~ 0
A11
Wire Wire Line
	5950 4800 5600 4800
Wire Wire Line
	5950 4900 5600 4900
Wire Wire Line
	5950 5000 5600 5000
Wire Wire Line
	5950 5100 5600 5100
Text Label 5650 4800 0    60   ~ 0
A12
Text Label 5650 4900 0    60   ~ 0
A13
Text Label 5650 5000 0    60   ~ 0
A14
Text Label 5650 5100 0    60   ~ 0
+5V
$Comp
L GND #PWR?
U 1 1 59F69D09
P 6800 5100
F 0 "#PWR?" H 6800 4850 50  0001 C CNN
F 1 "GND" H 6800 4950 50  0000 C CNN
F 2 "" H 6800 5100 50  0001 C CNN
F 3 "" H 6800 5100 50  0001 C CNN
	1    6800 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 5100 6450 5100
Wire Wire Line
	6450 4600 6800 4600
Wire Wire Line
	6450 4700 6800 4700
Wire Wire Line
	6450 4800 6800 4800
Wire Wire Line
	6450 4900 6800 4900
Wire Wire Line
	6450 5000 6800 5000
Text Label 6600 4600 0    60   ~ 0
40
Text Label 6600 4700 0    60   ~ 0
41
Text Label 6600 4800 0    60   ~ 0
42
Text Label 6600 4900 0    60   ~ 0
43
Text Label 6600 5000 0    60   ~ 0
44
Text Notes 6050 4250 0    60   ~ 0
I/O Aux
$EndSCHEMATC
