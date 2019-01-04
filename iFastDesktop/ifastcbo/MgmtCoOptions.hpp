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
// ^FILE   : Demographics.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 10/14/1999
//
// ^CLASS    : MgmtCoOptions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MgmtCoOptions : public MFCanBFCbo, private boost::noncopyable
{
public:
   MgmtCoOptions (BFAbstractCBO &parent);
   virtual ~MgmtCoOptions();
   SEVERITY init ( const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING 
                 );
   virtual void getField( const BFFieldId& idField, 
                          DString& strFieldValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const;
};

