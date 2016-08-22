#!/bin/bash
myProcServScript=/home/pi/epics/RaspPi/startup/procServ/start_RaspPi_IOC_procServ.sh
#procServ -q -L /home/pi/epics/Temperatur/startup/procServ/start_RaspPi_IOC_procServ.log --logstamp -n apfelControlIOC -l 4814 4813 ${myProcServScript} 
sudo procServ -q -n RaspPiIOC -l 4814 4813 ${myProcServScript}