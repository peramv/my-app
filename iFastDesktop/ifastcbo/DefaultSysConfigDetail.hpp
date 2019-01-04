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
// ^FILE   : DefaultSysConfigDetailDetail.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfigDetailDetail
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for a field with multiple keys
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

class IFASTCBO_LINKAGE DefaultSysConfigDetail : public MFCanBFCbo, private boost::noncopyable
{
public: 
   DefaultSysConfigDetail( BFAbstractCBO &parent );
   virtual ~DefaultSysConfigDetail( void );
   SEVERITY init ( const BFData &viewData  );
 
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigDetail.hpp-arc  $   

*/