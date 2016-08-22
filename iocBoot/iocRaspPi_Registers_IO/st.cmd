#!../../bin/linux-arm/RaspPi

< envPaths
#cd ${TOP}
epicsEnvSet("STREAM_PROTOCOL_PATH", "../../protocols")
epicsEnvSet("PATH","${PATH}:../../bin/linux-arm")

## Register all support components
dbLoadDatabase "../../dbd/RaspPi.dbd"

RaspPi_registerRecordDeviceDriver (pdbbase)

drvAsynSerialPortConfigure("hadcon2","/dev/ttyUSB0",0,0,0)
   asynSetOption("hadcon2",0,"baud","115200")
   asynSetOption("hadcon2",0,"bits","8")
   asynSetOption("hadcon2",0,"parity","none")
   asynSetOption("hadcon2",0,"stop","1")
   asynSetOption("hadcon2",0,"clocal","Y")
   asynSetOption("hadcon2",0,"crtscts","N")

## Load record instances
##
dbLoadRecords  ("../../db/hadcon_temp_global.db", "HADCON=HADES:RICH:TEMP, PREFIX=HADES:RICH:TEMP:, DESC_PREFIX_RAW=temperature, SUFFIX=, device=hadcon2")
dbLoadTemplate ("../../db/hadcon_oneWire_temp.substitutions")
dbLoadRecords("../../db/DHT22oneWire.db","ID=HADES:RICH:Humidity, user=piHost")

##dbLoadRecords ("../../db/hadcon_atmel_register_IO_ports.db", "device=hadcon2, HADCON=HADES:RICH:TEMP")

#cd $(TOP)

## Set this to see messages from streamDev, already while init
## Run this to trace the stages of iocInit
#traceIocInit

#cd ${TOP}/iocBoot/${IOC}
iocInit

