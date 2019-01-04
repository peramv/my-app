#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FundLmtOverrideList.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 09, 2003
//
// ^CLASS    : FundLmtOverrideList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundLmtOverride;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundLmtOverrideList : public MFCanBFCbo, private boost::noncopyable
{

public:
   FundLmtOverrideList( BFAbstractCBO &parent );
   virtual ~FundLmtOverrideList( void );

   // Initialize function
   SEVERITY init( const DString &fundCode, 
                  const DString &classCode, 
                  const DString &transType, 
                  const DString &dstrTrack = I_("N"),
                  const DString &dstrPageName = NULL_STRING
                );
   SEVERITY getFundLmtOverride ( const DSTCWorkSession &workSession,
                                 const DString &accountNum,
                                 const DString &limitationCode,
                                 FundLmtOverride *&pFundLmtOverride,
                                 const BFDataGroupId &idDataGroup
                               );
   SEVERITY getFundLevelFundLmtOverride ( const DSTCWorkSession &workSession,
                                          const DString &limitationCode,
                                          FundLmtOverride *&pFundLmtOverride,
                                          const BFDataGroupId &idDataGroup);
protected:   
   SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
private :
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundLmtOverrideList.hpp-arc  $
//
//   Rev 1.9   Nov 14 2004 14:42:44   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Nov 04 2004 17:37:40   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.7   Jun 25 2004 19:05:16   popescu
//PTS 10031525, Fund limitation overrides issue
//
//   Rev 1.6   Jun 25 2004 16:38:22   popescu
//PST 10031525, fund limitation override issues
//
//   Rev 1.5   Nov 26 2003 10:56:20   linmay
//added isCodeInList().. for PTS#10024397
//
//   Rev 1.4   Mar 21 2003 18:11:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Mar 08 2003 12:46:26   WINNIE
//Bug fix : Need new parameter LimitationCode to locate the corresponding record. Existing logic stop as soon as the first record is found even though the record is for different purposes. Move method to private. 
//
//   Rev 1.2   Jan 30 2003 19:05:00   WINNIE
//Call by reference for input parameters of getStopFlag, override and minimum amount 
//
//   Rev 1.1   Jan 21 2003 18:28:50   WINNIE
//add method getMinAmountFlag for Systematic minimum edit check
//
//   Rev 1.0   Jan 12 2003 16:05:38   WINNIE
//Initial revision.

*/