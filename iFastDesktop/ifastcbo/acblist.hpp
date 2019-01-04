#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ACBList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : ACBList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE ACBList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ACBList( BFAbstractCBO &parent );
   virtual ~ACBList( void );

   // Initialize function
   SEVERITY init( const DString& AccountNum, 
                  const DString& FundCode, 
                  const DString& ClassCode,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   //SEVERITY init( const BFData& data );

   SEVERITY getMore();

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup );

private:

   BFData _requestData;
   DString _accountNum;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ACBList.cpp-arc  $
//

