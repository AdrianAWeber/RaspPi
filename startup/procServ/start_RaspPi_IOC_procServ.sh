#!/bin/bash

#if available start EPICS's caRepeater
which caRepeater >/dev/null 2>&1 
if [ $? -eq 0 ] 
then
 pgrep caRepeater || caRepeater &
fi

export myIOCBOOT=/home/pi/epics/RaspPi/iocBoot/iocRaspPi_Registers_IO
export myARCH=linux-arm
cd ${myIOCBOOT} && LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+$LD_LIBRARY_PATH:}../../lib/${myARCH} HOSTNAME=$(hostname) ../../bin/${myARCH}/RaspPi st.cmd