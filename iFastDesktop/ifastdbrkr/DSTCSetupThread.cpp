//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DSTCSetupThread.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : DSTCSetupThread
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include <srcprag.h>

#include "dstcsetupthread.hpp"
#include <bfdata\bfdata.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFDataId DSTC0001_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0001_VW;
   extern CLASS_IMPORT const BFDataId DSTC0001_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0064_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0064_VW;
   extern CLASS_IMPORT const BFDataId DSTC0064_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0063_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0063_VW;
   extern CLASS_IMPORT const BFDataId DSTC0063_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0056_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0056_VW;
   extern CLASS_IMPORT const BFDataId DSTC0056_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0136_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0136_VW;
   extern CLASS_IMPORT const BFDataId DSTC0136_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0083_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0083_VW;
   extern CLASS_IMPORT const BFDataId DSTC0149_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0149_VW;
   extern CLASS_IMPORT const BFDataId DSTC0087_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0087_VW;
   extern CLASS_IMPORT const BFDataId DSTC0087_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0003_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0003_VW;
   extern CLASS_IMPORT const BFDataId DSTC0003_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0004_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0004_VW;
   extern CLASS_IMPORT const BFDataId DSTC0004_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0050_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0050_VW;
   extern CLASS_IMPORT const BFDataId DSTC0050_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0061_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0061_VW;
   extern CLASS_IMPORT const BFDataId DSTC0061_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0020_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0020_VW;
   extern CLASS_IMPORT const BFDataId DSTC0020_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0069_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0069_VW;
   extern CLASS_IMPORT const BFDataId DSTC0069_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0043_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0043_VW;
   extern CLASS_IMPORT const BFDataId DSTC0043_VWRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0053_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0053_VW;
   extern CLASS_IMPORT const BFDataId DSTC0053_VWRepeat_Record;
//   extern CLASS_IMPORT const BFDataId DSTC0101_REQ;
   extern CLASS_IMPORT const BFDataId DSTC0101_VW;
   extern CLASS_IMPORT const BFDataId DSTC0101_VWRepeat_Record;

}

void DSTCSetupThread::run() 
{   
   setPriority ( THREAD_PRIORITY_LOWEST );   
   {BFData data( ifds::DSTC0001_REQ);}
   {BFData data( ifds::DSTC0001_VW);}
   {BFData data( ifds::DSTC0001_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0064_REQ);}
   {BFData data( ifds::DSTC0064_VW);}
   {BFData data( ifds::DSTC0064_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0063_REQ);}
   {BFData data( ifds::DSTC0063_VW);}
   {BFData data( ifds::DSTC0063_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0056_REQ);}
   {BFData data( ifds::DSTC0056_VW);}
   {BFData data( ifds::DSTC0056_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0136_REQ);}
   {BFData data( ifds::DSTC0136_VW);}
   {BFData data( ifds::DSTC0136_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0083_REQ);}
   {BFData data( ifds::DSTC0083_VW);}
//   {BFData data( ifds::DSTC0149_REQ);}
   {BFData data( ifds::DSTC0149_VW);}   
//   {BFData data( ifds::DSTC0087_REQ);}
   {BFData data( ifds::DSTC0087_VW);}
   {BFData data( ifds::DSTC0087_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0003_REQ);}
   {BFData data( ifds::DSTC0003_VW);}
   {BFData data( ifds::DSTC0003_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0004_REQ);}
   {BFData data( ifds::DSTC0004_VW);}
   {BFData data( ifds::DSTC0004_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0050_REQ);}
   {BFData data( ifds::DSTC0050_VW);}
   {BFData data( ifds::DSTC0050_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0061_REQ);}
   {BFData data( ifds::DSTC0061_VW);}
   {BFData data( ifds::DSTC0061_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0020_REQ);}
   {BFData data( ifds::DSTC0020_VW);}
   {BFData data( ifds::DSTC0020_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0069_REQ);}
   {BFData data( ifds::DSTC0069_VW);}
   {BFData data( ifds::DSTC0069_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0043_REQ);}
   {BFData data( ifds::DSTC0043_VW);}
   {BFData data( ifds::DSTC0043_VWRepeat_Record);}
//   {BFData data( ifds::DSTC0053_REQ);}
   {BFData data( ifds::DSTC0053_VW);}
   {BFData data( ifds::DSTC0053_VWRepeat_Record);}
   {BFData data( ifds::DSTC0101_VW);}
   {BFData data( ifds::DSTC0101_VWRepeat_Record);}
}