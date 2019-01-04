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
// ^FILE   : ShrFamilyList.hpp
// ^AUTHOR : Claudio Snachez
// ^DATE   : January, 2003
//
// ^CLASS    : ShrFamilyList.hpp
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

class ShrFamily;

class IFASTCBO_LINKAGE ShrFamilyList : public MFCanBFCbo, private boost::noncopyable
{
public:
   ShrFamilyList( BFAbstractCBO &parent );
   virtual ~ShrFamilyList();
   //used to initialize from the shareholder object, when shareholder is new,
   //the param here is passed for convenience
   SEVERITY initNew(const DString& shrNum, const BFDataGroupId& idDataGroup = BF::HOST);
   SEVERITY init(const DString& shrNum, const DString&  dstrTrack = I_("N"),
      const DString&  dstrPageName = NULL_STRING);
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY checkDuplicate ( const ShrFamily *pShrFamilyToCheck, 
                             const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFamilyList.hpp-arc  $
//
//   Rev 1.7   Nov 09 2011 23:55:12   popescu
//P0188902 FN02 - DYN Household Project, implement duplicate check
//
//   Rev 1.6   Nov 09 2011 18:33:44   dchatcha
//P0188902 FN02 - DYN Household Project, interim checking in.
//
//   Rev 1.5   Nov 14 2004 14:55:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 22 2003 14:13:16   popescu
//Replaced name 'BankInstr' with 'BankInstructions'; 
//simplified child lists getters for the Shareholder object
//
//   Rev 1.3   Mar 21 2003 18:25:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Jan 14 2003 17:41:28   sanchez
//added  Revision Control Entries
 */