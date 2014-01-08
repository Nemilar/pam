#!/usr/bin/python

import psutil
from time import sleep
import serial

def trueOrFalse(someBool):
	if someBool:
		return "1"
	else:
		return "0"

lastDiskR = 0
lastDiskW = 0
lastNetS = 0
lastNetR = 0
cpu_pct = 0
mem_pct = 0
timer = 0
delay = 1 # seconds per polling interval
cpupollfreq = 2 # seconds per polling interval for CPU and MEM

ser = serial.Serial('/dev/pam', 9600);

while 1:
	# CPU and RAM are polled less frequently than
	# HDD and NET
	if timer >= cpupollfreq:
		cpu_pct = int(psutil.cpu_percent())
		if cpu_pct == 100:
			cpu_pct = 99
		mem_pct = int(psutil.virtual_memory().percent)
		timer = 0

	diskR = psutil.disk_io_counters().read_count
	diskW = psutil.disk_io_counters().write_count

	if diskR > lastDiskR:
		diskR_activity = True
	else:
		diskR_activity = False
	if diskW > lastDiskW:
		diskW_activity = True
	else:
		diskW_activity = False

	lastDiskR = diskR
	lastDiskW = diskW

	netR = psutil.network_io_counters().bytes_recv
	netS = psutil.network_io_counters().bytes_sent

	if netR > lastNetR:
		netR_activity = True
	else:
		netR_activity = False
	if netS > lastNetS:
		netS_activity = True
	else:
		netSActivity = False

	lastNetR = netR
	lastNetS = netS


	print "CPU=" + str(cpu_pct)
	print "MEM=" + str(mem_pct)
	print "DiskR=" + str(diskR_activity)
	print "DiskW=" + str(diskW_activity)	
	print "NetS=" + str(netS_activity)
	print "NetR=" + str(netR_activity) 
	
	c1=cpu_pct/10
	c2=cpu_pct%10
	m1=mem_pct/10
	m2=mem_pct%10

	netHddString = ""
	
	netHddString += trueOrFalse(netR_activity)
	netHddString += trueOrFalse(netS_activity)
	netHddString += trueOrFalse(diskR_activity)
	netHddString += trueOrFalse(diskW_activity)
	
	outString = str(c1) + str(c2) + str(m1) + str(m2) + netHddString
	ser.write(outString)
	sleep(1)
	timer += 1
	print "wrote " + outString
	inc = 0
	cont = False
	print "Cont"
	sleep(delay)
	timer += delay

