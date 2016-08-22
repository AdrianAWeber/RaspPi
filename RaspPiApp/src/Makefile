TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

LIBRARY_IOC += DHT22oneWire

DBD += DHT22oneWire.dbd
DHT22oneWire_SRCS += DHT22oneWire.c
DHT22oneWire_SRCS += pi_2_dht_read.h
DHT22oneWire_SRCS += pi_2_mmio.h
DHT22oneWire_SRCS += common_dht_read.h
DHT22oneWire_LIBS += $(EPICS_BASE_IOC_LIBS)
#=============================
# Build the IOC support library

PROD_LIBS += stream
PROD_LIBS += asyn
###PROD_LIBS += calc

LIBRARY_IOC += RaspPiSupport

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
RaspPiSupport_SRCS += initTrace.c
RaspPiSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = RaspPi
# RaspPi.dbd will be created and installed
DBD += RaspPi.dbd

# RaspPi.dbd will be made up from these files:
RaspPi_DBD += base.dbd
RaspPi_DBD += asyn.dbd
RaspPi_DBD += stream.dbd
RaspPi_DBD += RaspPiInclude.dbd
RaspPi_DBD += initTrace.dbd
RaspPi_DBD += DHT22oneWire.dbd
RaspPi_DBD += drvAsynSerialPort.dbd

# RaspPi_registerRecordDeviceDriver.cpp derives from RaspPi.dbd
RaspPi_SRCS += RaspPi_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
RaspPi_SRCS_DEFAULT += RaspPiMain.cpp
RaspPi_SRCS_vxWorks += -nil-

# Link in the code from the support library
RaspPi_LIBS += RaspPiSupport
RaspPi_LIBS += DHT22oneWire

# Finally link to the EPICS Base libraries
RaspPi_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
ifneq ($(findstring linux-arm,$(T_A)),)
BIN_INSTALLS += $(EPICS_BASE_BIN)/caRepeater
LIB_INSTALLS += $(ASYN)/lib/linux-arm/libasyn.so
LIB_INSTALLS += $(STREAM)/lib/linux-arm/libstream.so
LIB_INSTALLS += $(SNCSEQ)/lib/linux-arm/libseq.so
LIB_INSTALLS += $(SNCSEQ)/lib/linux-arm/libpv.so
endif

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

#ifdef T_A
#ifeq($(T_A), linux-cris_v10)
#deploy: build.$(T_A)	
#	echo scp $(TOP) hadaq@lxhadesdaq:/var/diskless/etrax/EPICS/epics_apps
#else
#
#endif
#endif
