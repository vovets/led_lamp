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
L Switch:SW_Push SW1
U 1 1 615E613D
P 5500 3750
F 0 "SW1" V 5546 3702 50  0000 R CNN
F 1 "SW_Push" V 5455 3702 50  0000 R CNN
F 2 "led_lamp:SW_SPST_UNKNOWN" H 5500 3950 50  0001 C CNN
F 3 "~" H 5500 3950 50  0001 C CNN
	1    5500 3750
	1    0    0    -1  
$EndComp
Text Label 5150 3650 0    50   ~ 0
SW
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 615F5B84
P 6450 3600
F 0 "J8" H 6530 3642 50  0000 L CNN
F 1 "Conn_01x01" H 6530 3551 50  0000 L CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 6450 3600 50  0001 C CNN
F 3 "~" H 6450 3600 50  0001 C CNN
	1    6450 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 615F55B4
P 6450 3450
F 0 "J7" H 6530 3492 50  0000 L CNN
F 1 "Conn_01x01" H 6530 3401 50  0000 L CNN
F 2 "led_lamp:SolderWirePad_1x01_SMD_1x2mm" H 6450 3450 50  0001 C CNN
F 3 "~" H 6450 3450 50  0001 C CNN
	1    6450 3450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 621ADD1B
P 4950 3550
F 0 "J6" H 4868 3867 50  0000 C CNN
F 1 "Conn_01x03" H 4868 3776 50  0000 C CNN
F 2 "led_lamp:SolderWirePad_1x03_SMD_1x2mm" H 4950 3550 50  0001 C CNN
F 3 "~" H 4950 3550 50  0001 C CNN
	1    4950 3550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 3550 5700 3550
Wire Wire Line
	6200 3550 6200 3600
Wire Wire Line
	6200 3600 6250 3600
Wire Wire Line
	5150 3650 5300 3650
Wire Wire Line
	5300 3650 5300 3750
Wire Wire Line
	5700 3750 5700 3550
Connection ~ 5700 3550
Wire Wire Line
	5700 3550 6200 3550
Wire Wire Line
	5150 3450 6250 3450
$EndSCHEMATC
