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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundGroupSubList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/09/02
//
// ^CLASS    : FundGroupSubList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <bfutil\bfcritsec.hpp>

#ifndef _MAP_
   #include <map>
#endif 


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundGroupSubList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FundGroupSubList( BFAbstractCBO &parent );
   virtual ~FundGroupSubList( void );

   // Initialize function
   SEVERITY init( const DString& strType );

   DString getFundGroupSubList( const DString& strType );
   bool doesFundGroupExist( const DString &dstrFundGroup );

protected:
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   DString buildSubList( const DString& strBankType );

   BFCritSec _csFundGroupSubList;
   DString m_strFundType;
};

