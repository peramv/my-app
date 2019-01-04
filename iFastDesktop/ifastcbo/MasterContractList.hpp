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
// ^FILE   : MasterContractList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : April 3, 2000
//
// ^CLASS    : MasterContractList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

class IFASTCBO_LINKAGE MasterContractList : public MFCanBFCbo, private boost::noncopyable
{
public:
   MasterContractList( BFAbstractCBO &parent );
   virtual ~MasterContractList();

   SEVERITY init( const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY initWithPortfolio( const DString& dstrGroupCode,
                               const DString& dstrProdPortfolioUUID,
                               const DString& dstrTrack= I_("N"), 
                               const DString& dstrPageName = NULL_STRING );

   void getStrKey( DString &strKey, const BFData *data );
   bool getFieldByGroupAndContractType( DString &GroupCode, DString &ContractType, const BFFieldId &idField, DString &dstrValue, const BFDataGroupId &idDataGroup, bool bFormatted );

private:
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MasterContractList.hpp-arc  $
//
//   Rev 1.14   Jan 09 2012 10:08:08   dchatcha
//P0186484 - FN 05 - work on Contract Information Screen
// 

