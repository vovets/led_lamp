EESchema Schematic File Version 4
EELAYER 30 0
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
L Regulator_Switching:NCP1529A U2
U 1 1 61639064
P 4200 4700
F 0 "U2" H 4200 5067 50  0000 C CNN
F 1 "NCP1529A" H 4200 4976 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 4250 4450 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NCP1529-D.PDF" H 3950 5150 50  0001 C CNN
	1    4200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 61639E0F
P 4200 5050
F 0 "#PWR0101" H 4200 4800 50  0001 C CNN
F 1 "GND" H 4205 4877 50  0000 C CNN
F 2 "" H 4200 5050 50  0001 C CNN
F 3 "" H 4200 5050 50  0001 C CNN
	1    4200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5050 4200 5000
$Comp
L Device:L L1
U 1 1 6163A040
P 4700 4600
F 0 "L1" V 4890 4600 50  0000 C CNN
F 1 "2,2u" V 4799 4600 50  0000 C CNN
F 2 "Inductor_SMD:L_1812_4532Metric" H 4700 4600 50  0001 C CNN
F 3 "~" H 4700 4600 50  0001 C CNN
	1    4700 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 4600 4550 4600
$Comp
L Device:C C2
U 1 1 6163A624
P 5250 4800
F 0 "C2" H 5365 4846 50  0000 L CNN
F 1 "22p" H 5365 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5288 4650 50  0001 C CNN
F 3 "~" H 5250 4800 50  0001 C CNN
	1    5250 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6163ACFB
P 4900 4800
F 0 "R1" H 4970 4846 50  0000 L CNN
F 1 "1,1M" H 4970 4755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4830 4800 50  0001 C CNN
F 3 "~" H 4900 4800 50  0001 C CNN
	1    4900 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6163AF14
P 4900 5250
F 0 "R2" H 4970 5296 50  0000 L CNN
F 1 "270k" H 4970 5205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4830 5250 50  0001 C CNN
F 3 "~" H 4900 5250 50  0001 C CNN
	1    4900 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4600 4900 4600
Wire Wire Line
	4900 4600 4900 4650
Wire Wire Line
	4900 4950 4900 5000
Wire Wire Line
	4500 4700 4500 5000
Wire Wire Line
	4500 5000 4900 5000
Connection ~ 4900 5000
Wire Wire Line
	4900 5000 4900 5050
Wire Wire Line
	4900 4600 5250 4600
Wire Wire Line
	5250 4600 5250 4650
Connection ~ 4900 4600
Wire Wire Line
	5250 4950 5250 5050
Wire Wire Line
	5250 5050 4900 5050
Connection ~ 4900 5050
Wire Wire Line
	4900 5100 4900 5050
$Comp
L Device:C C1
U 1 1 6163C6A3
P 5600 4750
F 0 "C1" H 5715 4796 50  0000 L CNN
F 1 "10u" H 5715 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 4600 50  0001 C CNN
F 3 "~" H 5600 4750 50  0001 C CNN
	1    5600 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4600 5600 4600
Connection ~ 5250 4600
$Comp
L power:GND #PWR0102
U 1 1 6163CF4F
P 5600 4950
F 0 "#PWR0102" H 5600 4700 50  0001 C CNN
F 1 "GND" H 5605 4777 50  0000 C CNN
F 2 "" H 5600 4950 50  0001 C CNN
F 3 "" H 5600 4950 50  0001 C CNN
	1    5600 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6163D098
P 4900 5450
F 0 "#PWR0103" H 4900 5200 50  0001 C CNN
F 1 "GND" H 4905 5277 50  0000 C CNN
F 2 "" H 4900 5450 50  0001 C CNN
F 3 "" H 4900 5450 50  0001 C CNN
	1    4900 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5450 4900 5400
Wire Wire Line
	5600 4950 5600 4900
$Comp
L Device:C C3
U 1 1 6163D5CC
P 3600 4750
F 0 "C3" H 3715 4796 50  0000 L CNN
F 1 "10u" H 3715 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3638 4600 50  0001 C CNN
F 3 "~" H 3600 4750 50  0001 C CNN
	1    3600 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4600 3900 4600
$Comp
L power:GND #PWR0104
U 1 1 6163DDDC
P 3600 4950
F 0 "#PWR0104" H 3600 4700 50  0001 C CNN
F 1 "GND" H 3605 4777 50  0000 C CNN
F 2 "" H 3600 4950 50  0001 C CNN
F 3 "" H 3600 4950 50  0001 C CNN
	1    3600 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4950 3600 4900
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20SU U1
U 1 1 6164609B
P 4550 2800
F 0 "U1" H 4000 2600 50  0000 R CNN
F 1 "ATtiny85-20SU" H 4000 2500 50  0000 R CNN
F 2 "Package_SO:SOIJ-8_5.3x5.3mm_P1.27mm" H 4550 2800 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 4550 2800 50  0001 C CNN
	1    4550 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 61646DDC
P 4550 3450
F 0 "#PWR0105" H 4550 3200 50  0001 C CNN
F 1 "GND" H 4555 3277 50  0000 C CNN
F 2 "" H 4550 3450 50  0001 C CNN
F 3 "" H 4550 3450 50  0001 C CNN
	1    4550 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3450 4550 3400
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 61649662
P 2050 3600
F 0 "J2" H 1968 3817 50  0000 C CNN
F 1 "Conn_01x01" H 1968 3726 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 2050 3600 50  0001 C CNN
F 3 "~" H 2050 3600 50  0001 C CNN
	1    2050 3600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2250 3100 2450 3100
Wire Wire Line
	2450 3100 2450 3050
$Comp
L power:+BATT #PWR0107
U 1 1 6164BE69
P 2450 3550
F 0 "#PWR0107" H 2450 3400 50  0001 C CNN
F 1 "+BATT" H 2465 3723 50  0000 C CNN
F 2 "" H 2450 3550 50  0001 C CNN
F 3 "" H 2450 3550 50  0001 C CNN
	1    2450 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3600 2450 3600
Wire Wire Line
	2450 3600 2450 3550
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 6164CA1C
P 2050 4100
F 0 "J3" H 1968 4317 50  0000 C CNN
F 1 "Conn_01x01" H 1968 4226 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 2050 4100 50  0001 C CNN
F 3 "~" H 2050 4100 50  0001 C CNN
	1    2050 4100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6164D119
P 2300 4150
F 0 "#PWR0108" H 2300 3900 50  0001 C CNN
F 1 "GND" H 2305 3977 50  0000 C CNN
F 2 "" H 2300 4150 50  0001 C CNN
F 3 "" H 2300 4150 50  0001 C CNN
	1    2300 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4150 2300 4100
Wire Wire Line
	2300 4100 2250 4100
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 616519ED
P 7100 2600
F 0 "J4" H 7180 2592 50  0000 L CNN
F 1 "Conn_01x04" H 7180 2501 50  0000 L CNN
F 2 "led_lamp:SolderWirePad_1x04_SMD_1x2mm" H 7100 2600 50  0001 C CNN
F 3 "~" H 7100 2600 50  0001 C CNN
	1    7100 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 6164C6C4
P 6850 2900
F 0 "#PWR0109" H 6850 2650 50  0001 C CNN
F 1 "GND" H 6855 2727 50  0000 C CNN
F 2 "" H 6850 2900 50  0001 C CNN
F 3 "" H 6850 2900 50  0001 C CNN
	1    6850 2900
	1    0    0    -1  
$EndComp
$Comp
L led_lamp:Vreg #PWR0110
U 1 1 6164C936
P 6850 2450
F 0 "#PWR0110" H 6850 2300 50  0001 C CNN
F 1 "Vreg" H 6865 2623 50  0000 C CNN
F 2 "" H 6850 2450 50  0001 C CNN
F 3 "" H 6850 2450 50  0001 C CNN
	1    6850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2450 6850 2500
Wire Wire Line
	6850 2500 6900 2500
$Comp
L led_lamp:Vreg #PWR0111
U 1 1 6164D7BF
P 5600 4550
F 0 "#PWR0111" H 5600 4400 50  0001 C CNN
F 1 "Vreg" H 5615 4723 50  0000 C CNN
F 2 "" H 5600 4550 50  0001 C CNN
F 3 "" H 5600 4550 50  0001 C CNN
	1    5600 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4550 5600 4600
Connection ~ 5600 4600
$Comp
L led_lamp:FDN306P Q1
U 1 1 6165001D
P 2800 3700
F 0 "Q1" V 3142 3700 50  0000 C CNN
F 1 "FDN306P" V 3051 3700 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3000 3625 50  0001 L CIN
F 3 "" H 2800 3700 50  0001 L CNN
	1    2800 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 3550 3050 3600
Wire Wire Line
	3050 3600 3000 3600
Wire Wire Line
	2600 3600 2450 3600
Connection ~ 2450 3600
$Comp
L led_lamp:Vin #PWR0112
U 1 1 616611D4
P 3050 3550
F 0 "#PWR0112" H 3050 3400 50  0001 C CNN
F 1 "Vin" H 3065 3723 50  0000 C CNN
F 2 "" H 3050 3550 50  0001 C CNN
F 3 "" H 3050 3550 50  0001 C CNN
	1    3050 3550
	1    0    0    -1  
$EndComp
$Comp
L led_lamp:Vin #PWR0113
U 1 1 61661251
P 2450 3050
F 0 "#PWR0113" H 2450 2900 50  0001 C CNN
F 1 "Vin" H 2465 3223 50  0000 C CNN
F 2 "" H 2450 3050 50  0001 C CNN
F 3 "" H 2450 3050 50  0001 C CNN
	1    2450 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 61661E47
P 3750 2350
F 0 "C4" H 3865 2396 50  0000 L CNN
F 1 "0,1u" H 3865 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3788 2200 50  0001 C CNN
F 3 "~" H 3750 2350 50  0001 C CNN
	1    3750 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2200 3750 2150
Wire Wire Line
	3750 2150 4550 2150
Wire Wire Line
	4550 2150 4550 2200
$Comp
L led_lamp:Vin #PWR0114
U 1 1 6166349E
P 4550 2100
F 0 "#PWR0114" H 4550 1950 50  0001 C CNN
F 1 "Vin" H 4565 2273 50  0000 C CNN
F 2 "" H 4550 2100 50  0001 C CNN
F 3 "" H 4550 2100 50  0001 C CNN
	1    4550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2100 4550 2150
Connection ~ 4550 2150
$Comp
L power:GND #PWR0115
U 1 1 6166413D
P 3750 2550
F 0 "#PWR0115" H 3750 2300 50  0001 C CNN
F 1 "GND" H 3755 2377 50  0000 C CNN
F 2 "" H 3750 2550 50  0001 C CNN
F 3 "" H 3750 2550 50  0001 C CNN
	1    3750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2550 3750 2500
Text Label 5150 2700 0    50   ~ 0
~SW
$Comp
L Device:R R3
U 1 1 61664D69
P 6250 2800
F 0 "R3" V 6000 2800 50  0000 C CNN
F 1 "10k" V 6100 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6180 2800 50  0001 C CNN
F 3 "~" H 6250 2800 50  0001 C CNN
	1    6250 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 6166524A
P 6500 3200
F 0 "C5" H 6615 3246 50  0000 L CNN
F 1 "0,1u" H 6615 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6538 3050 50  0001 C CNN
F 3 "~" H 6500 3200 50  0001 C CNN
	1    6500 3200
	1    0    0    -1  
$EndComp
Text Label 6600 2800 0    50   ~ 0
Vpwm
$Comp
L power:GND #PWR0116
U 1 1 61669D62
P 6500 3400
F 0 "#PWR0116" H 6500 3150 50  0001 C CNN
F 1 "GND" H 6505 3227 50  0000 C CNN
F 2 "" H 6500 3400 50  0001 C CNN
F 3 "" H 6500 3400 50  0001 C CNN
	1    6500 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3400 6500 3350
Wire Wire Line
	5450 3900 2800 3900
Wire Wire Line
	5150 2800 5300 2800
Wire Wire Line
	5300 2800 5300 4250
Wire Wire Line
	5300 4250 3850 4250
Wire Wire Line
	3850 4250 3850 4700
Wire Wire Line
	3850 4700 3900 4700
Text Label 5150 2500 0    50   ~ 0
~BATBYP
Text Label 5150 2800 0    50   ~ 0
LEDON
Text Notes 7850 2400 0    100  ~ 0
R2 = 240k\nR1 = 1M\nVreg = 3,1 V
NoConn ~ 5150 2900
NoConn ~ 5150 3000
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 616780C4
P 6350 4300
F 0 "#FLG0101" H 6350 4375 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 4473 50  0000 C CNN
F 2 "" H 6350 4300 50  0001 C CNN
F 3 "~" H 6350 4300 50  0001 C CNN
	1    6350 4300
	1    0    0    1   
$EndComp
Wire Wire Line
	6350 4250 6350 4300
$Comp
L led_lamp:Vin #PWR0118
U 1 1 6167A407
P 3600 4550
F 0 "#PWR0118" H 3600 4400 50  0001 C CNN
F 1 "Vin" H 3615 4723 50  0000 C CNN
F 2 "" H 3600 4550 50  0001 C CNN
F 3 "" H 3600 4550 50  0001 C CNN
	1    3600 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4550 3600 4600
Connection ~ 3600 4600
$Comp
L led_lamp:Vreg #PWR0117
U 1 1 6167C3B4
P 6350 4250
F 0 "#PWR0117" H 6350 4100 50  0001 C CNN
F 1 "Vreg" H 6365 4423 50  0000 C CNN
F 2 "" H 6350 4250 50  0001 C CNN
F 3 "" H 6350 4250 50  0001 C CNN
	1    6350 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0119
U 1 1 6167CC46
P 6800 4250
F 0 "#PWR0119" H 6800 4100 50  0001 C CNN
F 1 "+BATT" H 6815 4423 50  0000 C CNN
F 2 "" H 6800 4250 50  0001 C CNN
F 3 "" H 6800 4250 50  0001 C CNN
	1    6800 4250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6167D40E
P 6800 4300
F 0 "#FLG0102" H 6800 4375 50  0001 C CNN
F 1 "PWR_FLAG" H 6800 4473 50  0000 C CNN
F 2 "" H 6800 4300 50  0001 C CNN
F 3 "~" H 6800 4300 50  0001 C CNN
	1    6800 4300
	1    0    0    1   
$EndComp
Wire Wire Line
	6800 4300 6800 4250
Wire Wire Line
	6500 2800 6900 2800
Wire Wire Line
	6400 2800 6500 2800
$Comp
L Device:R R4
U 1 1 6168BCD8
P 5800 2300
F 0 "R4" H 5870 2346 50  0000 L CNN
F 1 "100k" H 5870 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5730 2300 50  0001 C CNN
F 3 "~" H 5800 2300 50  0001 C CNN
	1    5800 2300
	1    0    0    -1  
$EndComp
$Comp
L led_lamp:Vin #PWR0120
U 1 1 6168C2A7
P 5800 2100
F 0 "#PWR0120" H 5800 1950 50  0001 C CNN
F 1 "Vin" H 5815 2273 50  0000 C CNN
F 2 "" H 5800 2100 50  0001 C CNN
F 3 "" H 5800 2100 50  0001 C CNN
	1    5800 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 6169CED8
P 2050 3100
F 0 "J1" H 1968 3317 50  0000 C CNN
F 1 "Conn_01x01" H 1968 3226 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 2050 3100 50  0001 C CNN
F 3 "~" H 2050 3100 50  0001 C CNN
	1    2050 3100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 616A7F56
P 7250 4300
F 0 "#PWR0106" H 7250 4050 50  0001 C CNN
F 1 "GND" H 7255 4127 50  0000 C CNN
F 2 "" H 7250 4300 50  0001 C CNN
F 3 "" H 7250 4300 50  0001 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 616A858F
P 7250 4250
F 0 "#FLG0103" H 7250 4325 50  0001 C CNN
F 1 "PWR_FLAG" H 7250 4423 50  0000 C CNN
F 2 "" H 7250 4250 50  0001 C CNN
F 3 "~" H 7250 4250 50  0001 C CNN
	1    7250 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4250 7250 4300
$Comp
L led_lamp:Vin #PWR0122
U 1 1 616AC74D
P 7700 4250
F 0 "#PWR0122" H 7700 4100 50  0001 C CNN
F 1 "Vin" H 7715 4423 50  0000 C CNN
F 2 "" H 7700 4250 50  0001 C CNN
F 3 "" H 7700 4250 50  0001 C CNN
	1    7700 4250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 616ACEB1
P 7700 4300
F 0 "#FLG0104" H 7700 4375 50  0001 C CNN
F 1 "PWR_FLAG" H 7700 4473 50  0000 C CNN
F 2 "" H 7700 4300 50  0001 C CNN
F 3 "~" H 7700 4300 50  0001 C CNN
	1    7700 4300
	1    0    0    1   
$EndComp
Wire Wire Line
	7700 4300 7700 4250
Text Label 4600 5000 0    50   ~ 0
FB
Wire Wire Line
	5150 2700 5800 2700
Connection ~ 6500 2800
Wire Wire Line
	6500 2800 6500 3050
Wire Wire Line
	5800 2100 5800 2150
Wire Wire Line
	5800 2450 5800 2700
Connection ~ 5800 2700
Wire Wire Line
	6900 2600 6850 2600
Wire Wire Line
	6850 2600 6850 2900
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 616A88BB
P 2050 4650
F 0 "J5" H 1968 4867 50  0000 C CNN
F 1 "Conn_01x01" H 1968 4776 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 2050 4650 50  0001 C CNN
F 3 "~" H 2050 4650 50  0001 C CNN
	1    2050 4650
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 616A88C1
P 2300 4700
F 0 "#PWR0123" H 2300 4450 50  0001 C CNN
F 1 "GND" H 2305 4527 50  0000 C CNN
F 2 "" H 2300 4700 50  0001 C CNN
F 3 "" H 2300 4700 50  0001 C CNN
	1    2300 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4700 2300 4650
Wire Wire Line
	2300 4650 2250 4650
Wire Wire Line
	5800 2700 6900 2700
Wire Wire Line
	5150 2500 5450 2500
Wire Wire Line
	5450 2500 5450 3900
Wire Wire Line
	5150 2600 5600 2600
Wire Wire Line
	5600 2600 5600 2800
Wire Wire Line
	5600 2800 6100 2800
Text Label 5150 2600 0    50   ~ 0
OC1A
$EndSCHEMATC