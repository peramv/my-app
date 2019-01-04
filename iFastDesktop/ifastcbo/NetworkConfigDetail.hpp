#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : NetworkConfigDetail.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 04 April 2013
//
// ^CLASS    : NetworkConfigDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the Network Config Details
//
//******************************************************************************
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
//robs OCRI
class IFASTCBO_LINKAGE NetworkConfigDetail : public MFCanBFCbo, private boost::noncopyable
{
public: 
   NetworkConfigDetail( BFAbstractCBO &parent );
   virtual ~NetworkConfigDetail( void );
   SEVERITY init ( const BFData &viewData  );
 
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfig.hpp-arc  $

*/