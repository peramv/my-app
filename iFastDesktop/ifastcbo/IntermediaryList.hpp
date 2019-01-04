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
//******************************************************************************
//
// ^FILE   : IntermediaryList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
// ^CLASS  : IntermediaryList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    Implements View 86.
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

class Intermediary;

class IFASTCBO_LINKAGE IntermediaryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   IntermediaryList( BFAbstractCBO &parent );
   virtual ~IntermediaryList();

   void buildKey( DString &strKey, const DString& strInterCode );
   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   void getInterCodeList( DString &dstList, bool bMakeUppercase);
   bool getIntermediary(const BFDataGroupId& idDataGroup, DString strInterCode, Intermediary *&pIntermediary);
   void getStrKey( DString &strKey, const BFData *data );

   // Initialize function
   SEVERITY init( const DString& dstrIntrCode = NULL_STRING, 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/IntermediaryList.hpp-arc  $
 * 
 *    Rev 1.13   Nov 14 2004 14:48:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Nov 04 2004 17:38:00   popescu
 * PET 1117/06, Trade processing
**/