#pragma once
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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCDataBrokerConditions.h
// ^AUTHOR : Mihai Virgil Buzila 
// ^DATE   : 09/22/99
//
// ^CLASS  : DSTCDataBrokerConditions
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <map>

class DSTCDataBrokerConditions  
{
public:
   long getHostErrorCode(long DSTCErrCode);
   static DSTCDataBrokerConditions * getInstance();
   static void killInstance();
private:
   DSTCDataBrokerConditions();
   ~DSTCDataBrokerConditions();
   DSTCDataBrokerConditions &operator=( const DSTCDataBrokerConditions& copy );
   typedef std::map<long, long, std::less<long> >    ERR_TRANSF_MAP;
   typedef ERR_TRANSF_MAP::iterator                  ERR_TRANSF_MAP_ITER;

   ERR_TRANSF_MAP _errTransfMap;
   static DSTCDataBrokerConditions * _pInstance;
};

