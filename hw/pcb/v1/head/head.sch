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
L Regulator_Linear:TPS73601DBV U1
U 1 1 615CC615
P 5500 2500
F 0 "U1" H 5500 2867 50  0000 C CNN
F 1 "TPS73601DBV" H 5500 2776 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 5500 2825 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/tps736.pdf" H 5500 2450 50  0001 C CNN
	1    5500 2500
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6001R U2
U 1 1 615CCB44
P 6300 3250
F 0 "U2" H 5800 3200 50  0000 C CNN
F 1 "MCP6001R" H 5700 3100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 6300 3250 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 6300 3450 50  0001 C CNN
	1    6300 3250
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 615CD142
P 6350 4000
F 0 "R1" V 6250 3900 50  0000 L CNN
F 1 "36k" V 6250 4050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6280 4000 50  0001 C CNN
F 3 "~" H 6350 4000 50  0001 C CNN
	1    6350 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 615CD6E4
P 6950 4000
F 0 "R2" V 7050 4000 50  0000 L CNN
F 1 "1k" V 7050 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6880 4000 50  0001 C CNN
F 3 "~" H 6950 4000 50  0001 C CNN
	1    6950 4000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 615CDC27
P 5500 2850
F 0 "#PWR0102" H 5500 2600 50  0001 C CNN
F 1 "GND" H 5505 2677 50  0000 C CNN
F 2 "" H 5500 2850 50  0001 C CNN
F 3 "" H 5500 2850 50  0001 C CNN
	1    5500 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 615CE175
P 6400 3600
F 0 "#PWR0103" H 6400 3350 50  0001 C CNN
F 1 "GND" H 6405 3427 50  0000 C CNN
F 2 "" H 6400 3600 50  0001 C CNN
F 3 "" H 6400 3600 50  0001 C CNN
	1    6400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2800 5500 2850
Wire Wire Line
	6400 3550 6400 3600
Wire Wire Line
	6600 3350 6650 3350
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 615CF6A2
P 4150 2500
F 0 "J1" H 4068 2817 50  0000 C CNN
F 1 "Conn_01x04" H 4068 2726 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x04_SMD_1x2mm" H 4150 2500 50  0001 C CNN
F 3 "~" H 4150 2500 50  0001 C CNN
	1    4150 2500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 615CFA25
P 4400 2800
F 0 "#PWR0104" H 4400 2550 50  0001 C CNN
F 1 "GND" H 4405 2627 50  0000 C CNN
F 2 "" H 4400 2800 50  0001 C CNN
F 3 "" H 4400 2800 50  0001 C CNN
	1    4400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2500 5050 2500
Wire Wire Line
	5050 2500 5050 2400
Connection ~ 5050 2400
Wire Wire Line
	5050 2400 5100 2400
$Comp
L led_lamp:Vreg #PWR0105
U 1 1 615D0590
P 5000 2350
F 0 "#PWR0105" H 5000 2200 50  0001 C CNN
F 1 "Vreg" H 5015 2523 50  0000 C CNN
F 2 "" H 5000 2350 50  0001 C CNN
F 3 "" H 5000 2350 50  0001 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2350 5000 2400
Connection ~ 5000 2400
Wire Wire Line
	5000 2400 5050 2400
$Comp
L led_lamp:Vreg #PWR0106
U 1 1 615D0DC7
P 6400 2900
F 0 "#PWR0106" H 6400 2750 50  0001 C CNN
F 1 "Vreg" H 6415 3073 50  0000 C CNN
F 2 "" H 6400 2900 50  0001 C CNN
F 3 "" H 6400 2900 50  0001 C CNN
	1    6400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2900 6400 2950
$Comp
L Device:R R4
U 1 1 615D15AF
P 6650 2800
F 0 "R4" H 6720 2846 50  0000 L CNN
F 1 "100k" H 6720 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6580 2800 50  0001 C CNN
F 3 "~" H 6650 2800 50  0001 C CNN
	1    6650 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 615D1B84
P 7000 2850
F 0 "R3" H 7070 2896 50  0000 L CNN
F 1 "1k" H 7070 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6930 2850 50  0001 C CNN
F 3 "~" H 7000 2850 50  0001 C CNN
	1    7000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2950 6650 3150
Wire Wire Line
	6650 3150 6600 3150
Wire Wire Line
	7000 3000 7000 3150
Wire Wire Line
	7000 3150 6650 3150
Wire Wire Line
	6000 2500 6000 3250
Connection ~ 6000 3250
Wire Wire Line
	6650 2650 6650 2600
Wire Wire Line
	6650 2600 5900 2600
Wire Wire Line
	4600 2700 4350 2700
$Comp
L Device:R R6
U 1 1 615E2ECF
P 7250 2750
F 0 "R6" H 7320 2796 50  0000 L CNN
F 1 "0,1" H 7320 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7180 2750 50  0001 C CNN
F 3 "~" H 7250 2750 50  0001 C CNN
	1    7250 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 615E3E98
P 7250 2950
F 0 "#PWR0107" H 7250 2700 50  0001 C CNN
F 1 "GND" H 7255 2777 50  0000 C CNN
F 2 "" H 7250 2950 50  0001 C CNN
F 3 "" H 7250 2950 50  0001 C CNN
	1    7250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2950 7250 2900
Wire Wire Line
	7250 2600 7250 2550
Wire Wire Line
	7250 2550 7300 2550
Wire Wire Line
	7250 2550 7000 2550
Wire Wire Line
	7000 2550 7000 2700
Connection ~ 7250 2550
Wire Wire Line
	7300 2400 5900 2400
$Comp
L Switch:SW_Push SW1
U 1 1 615E613D
P 4900 2800
F 0 "SW1" V 4946 2752 50  0000 R CNN
F 1 "SW_Push" V 4855 2752 50  0000 R CNN
F 2 "led_lamp:SW_SPST_UNKNOWN" H 4900 3000 50  0001 C CNN
F 3 "~" H 4900 3000 50  0001 C CNN
	1    4900 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 615E7075
P 4900 3050
F 0 "#PWR0108" H 4900 2800 50  0001 C CNN
F 1 "GND" H 4905 2877 50  0000 C CNN
F 2 "" H 4900 3050 50  0001 C CNN
F 3 "" H 4900 3050 50  0001 C CNN
	1    4900 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3050 4900 3000
$Comp
L power:GND #PWR0109
U 1 1 615E7A6C
P 7150 4150
F 0 "#PWR0109" H 7150 3900 50  0001 C CNN
F 1 "GND" H 7155 3977 50  0000 C CNN
F 2 "" H 7150 4150 50  0001 C CNN
F 3 "" H 7150 4150 50  0001 C CNN
	1    7150 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2500 6000 2500
Wire Wire Line
	5900 2600 5900 3350
Wire Wire Line
	5900 3350 4600 3350
Connection ~ 6650 3150
Wire Wire Line
	4350 2400 5000 2400
$Comp
L led_lamp:Vreg #PWR0101
U 1 1 615FEBD3
P 4300 3650
F 0 "#PWR0101" H 4300 3500 50  0001 C CNN
F 1 "Vreg" H 4315 3823 50  0000 C CNN
F 2 "" H 4300 3650 50  0001 C CNN
F 3 "" H 4300 3650 50  0001 C CNN
	1    4300 3650
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 615FF4CF
P 4300 3700
F 0 "#FLG0101" H 4300 3775 50  0001 C CNN
F 1 "PWR_FLAG" H 4300 3873 50  0000 C CNN
F 2 "" H 4300 3700 50  0001 C CNN
F 3 "" H 4300 3700 50  0001 C CNN
	1    4300 3700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 615FFB08
P 4700 3700
F 0 "#PWR0110" H 4700 3450 50  0001 C CNN
F 1 "GND" H 4705 3527 50  0000 C CNN
F 2 "" H 4700 3700 50  0001 C CNN
F 3 "" H 4700 3700 50  0001 C CNN
	1    4700 3700
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 61600094
P 4700 3650
F 0 "#FLG0102" H 4700 3725 50  0001 C CNN
F 1 "PWR_FLAG" H 4700 3823 50  0000 C CNN
F 2 "" H 4700 3650 50  0001 C CNN
F 3 "" H 4700 3650 50  0001 C CNN
	1    4700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3650 4700 3700
Wire Wire Line
	4300 3650 4300 3700
Text Label 4650 2600 0    50   ~ 0
SW
Text Label 4600 3150 1    50   ~ 0
Vpwm
Wire Wire Line
	4600 2700 4600 3350
Text Label 6600 2400 0    50   ~ 0
OUT
Text Label 5950 2500 0    50   ~ 0
FB
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 615F55B4
P 7500 2400
F 0 "J2" H 7580 2442 50  0000 L CNN
F 1 "Conn_01x01" H 7580 2351 50  0000 L CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 7500 2400 50  0001 C CNN
F 3 "~" H 7500 2400 50  0001 C CNN
	1    7500 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 615F5B84
P 7500 2550
F 0 "J3" H 7580 2592 50  0000 L CNN
F 1 "Conn_01x01" H 7580 2501 50  0000 L CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 7500 2550 50  0001 C CNN
F 3 "~" H 7500 2550 50  0001 C CNN
	1    7500 2550
	1    0    0    -1  
$EndComp
$Comp
L led_lamp:Vreg #PWR0111
U 1 1 6160FC2D
P 5500 3600
F 0 "#PWR0111" H 5500 3450 50  0001 C CNN
F 1 "Vreg" H 5515 3773 50  0000 C CNN
F 2 "" H 5500 3600 50  0001 C CNN
F 3 "" H 5500 3600 50  0001 C CNN
	1    5500 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61610B38
P 5500 3800
F 0 "C1" H 5615 3846 50  0000 L CNN
F 1 "100n" H 5615 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5538 3650 50  0001 C CNN
F 3 "~" H 5500 3800 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 616113B0
P 5500 4000
F 0 "#PWR0112" H 5500 3750 50  0001 C CNN
F 1 "GND" H 5505 3827 50  0000 C CNN
F 2 "" H 5500 4000 50  0001 C CNN
F 3 "" H 5500 4000 50  0001 C CNN
	1    5500 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3950 5500 4000
Wire Wire Line
	5500 3600 5500 3650
Wire Wire Line
	4900 2600 4350 2600
Wire Wire Line
	4350 2500 4400 2500
Wire Wire Line
	4400 2500 4400 2800
Wire Wire Line
	6200 4000 6000 4000
Wire Wire Line
	6000 3250 6000 4000
Wire Wire Line
	6500 4000 6650 4000
Wire Wire Line
	6650 3350 6650 4000
Wire Wire Line
	6650 4000 6700 4000
Connection ~ 6650 4000
Wire Wire Line
	7100 4000 7150 4000
Wire Wire Line
	7150 4000 7150 4150
$Comp
L Device:C C2
U 1 1 61A6D9ED
P 6350 4350
F 0 "C2" V 6098 4350 50  0000 C CNN
F 1 "1n" V 6189 4350 50  0000 C CNN
F 2 "" H 6388 4200 50  0001 C CNN
F 3 "~" H 6350 4350 50  0001 C CNN
	1    6350 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 4350 6000 4350
Wire Wire Line
	6000 4350 6000 4000
Connection ~ 6000 4000
Wire Wire Line
	6700 4350 6700 4000
Wire Wire Line
	6500 4350 6700 4350
Connection ~ 6700 4000
Wire Wire Line
	6700 4000 6800 4000
$EndSCHEMATC
