/******************************************************************************
 * Device Support for a DHT22 Humidity and Temperatur sensor at a	      *
 * Raspberry Pi Model B.						      *
 * The used Librarys are from ADAFRUIT.					      *
*******************************************************************************/

/*_____ I N C L U D E S ______________________________________________________*/

/* ANSI C includes  */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* EPICS includes */
#include <aiRecord.h>
#include <alarm.h>
#include <dbAccess.h>
#include <dbScan.h>
#include <devSup.h>
#include <errlog.h>
#include <epicsExport.h>
#include <epicsTypes.h>
#include <iocLog.h>
#include <iocsh.h>
#include <recGbl.h>

/* Includes of DHT22 */
#include "./pi_2_dht_read.h"
#include "./common_dht_read.h"

/*_____ D E F I N I T I O N S ________________________________________________*/

/* Forward declarations */
static long init_record( aiRecord *prec );
static long read_ai( aiRecord *prec );

/*
 * Device Support Entry Table
 */
struct {
  long   number;                /* number of device support routines */
  DEVSUPFUN   report;           /* print reports */
  DEVSUPFUN   init;             /* initialization of device support module */
  DEVSUPFUN   init_record;      /* initialization of single record instances */
  DEVSUPFUN   get_ioint_info;   /* get I/O interrupt info */
  DEVSUPFUN   process;          /* read/write value */
  DEVSUPFUN   special_linconv;  /* Calculate ESLO from EGUL and EGUF for ai/ao records */
} dev_ai_DHT22ow = {
  6,
  NULL,
  NULL,
  init_record,
  NULL,
  read_ai,
  NULL
};


/*_____ G L O B A L S ________________________________________________________*/

/*_____ L O C A L S __________________________________________________________*/

/*_____ F U N C T I O N S ____________________________________________________*/

/*------------------------------------------------------------------------------
 * @brief   Print error message to IOCshell
 *
 * Prints an error message to STDERR of the IOCshell and sets the
 * status and severity of the record which caused the error.
 *
 * @param   [in]  prec    Address of record
 * @param   [in]  status  Reason of error
 *----------------------------------------------------------------------------*/
static void errMsg( aiRecord *prec, long status ) {
  epicsAlarmCondition stat = READ_ALARM;
  epicsAlarmSeverity sevr  = INVALID_ALARM;

  switch( status ) {
  case -1:
    stat = READ_ALARM;
    fprintf( stderr, "\033[31;1m%s: Timeout failure. No response from device.\n",
						 prec->name );
    break;

  case -2:
    stat = READ_ALARM;
    fprintf( stderr, "\033[31;1m%s: Checksum is not correct. \n", prec->name );
    break;

  case -3:
    stat = READ_ALARM;
    fprintf( stderr, "\033[31;1m%s: Argument has a error. \n", prec->name );
    break;

  case -4:
    stat = READ_ALARM;
    fprintf( stderr, "\033[31;1m%s: Problem with GPIO. \n", prec->name );
    break;

  default:
    stat = READ_ALARM;
    fprintf( stderr, "\033[31;1m%s: Unknown error\033[0m\n", prec->name );
  }
  recGblSetSevr( prec, stat, sevr );
}


/*------------------------------------------------------------------------------
 * @brief   Initialization of the record
 *
 * @param   [in]  precord  Address of the record calling this function
 *
 * @return  In case of error return -1, otherwise return 2 (no conversion)
 *----------------------------------------------------------------------------*/
static long init_record( aiRecord *prec ) {

  float humidity = 0;
  float temperature = 0;
  long status = 0;

  /* disable record */
  prec->pact = (epicsUInt8)true; 

  status = pi_2_dht_read(22, 4, &humidity, &temperature);
  if ( status ) {
    errMsg ( prec, status );
   return status;
  }

  if ( strcmp(prec->inp.value.instio.string,"Temperatur")== 0)
    {
  	prec->val = temperature;
    }
  else if ( strcmp(prec->inp.value.instio.string,"Humidity") == 0)
    {
        prec->val = humidity;
    }

  /* Set values of record */
  //prec->dpvt = pinfo;
  prec->linr = 0;
  prec->udf  = FALSE;
  /* enable record */
  prec->pact = (epicsUInt8)false; 

  return 2;
}


/*------------------------------------------------------------------------------
 * @brief   Read routine of the record
 *
 * @param   [in]  precord  Address of the record calling this function
 *
 * @return  In case of error return -1, otherwise return 2 (no conversion)
 *----------------------------------------------------------------------------*/
static long read_ai( aiRecord *prec ) {

  long status = 0;
  float temperature = 0;
  float humidity = 0;


  status = pi_2_dht_read(22, 4, &humidity, &temperature);

  if ( status ) {
    errMsg ( prec, status );
    return status;
  }


  if ( strcmp(prec->inp.value.instio.string,"Temperatur") == 0)
    {
  	prec->val = temperature;
    }
  else   if ( strcmp(prec->inp.value.instio.string,"Humidity") == 0)
    {
        prec->val = humidity;
    }

  return 2;
}

/*------------------------------------------------------------------------------
 * @brief   Export address of Device Support Entry Table to EPICS IOCshell
 *----------------------------------------------------------------------------*/
epicsExportAddress( dset, dev_ai_DHT22ow );

/* EOF */
