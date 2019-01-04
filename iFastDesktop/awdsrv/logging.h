//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : logging.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 30, 2005
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once

#include "AWDLog.hpp"
#define LOGGING(str)  (AWDLog::getInstance()<<str)
#define LOGGINGWITHTIMESTAMP(str)  (AWDLog::getInstance().addLogWithTimeStamp(str))
#define LOGGINGLOBDATA(x)  (AWDLog::getInstance().logLOBData(x))


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/logging.h-arc  $
//
//   Rev 1.0   Oct 31 2005 15:07:36   yingbaol
//Initial revision.
 * 
 *

 */

