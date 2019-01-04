#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DailyTransactionsFeeList.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan, 2004
//
// ^CLASS    : DailyTransactionsFeeList
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

//Forward declarations
class DailyTransactionsFee;

class IFASTCBO_LINKAGE DailyTransactionsFeeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DailyTransactionsFeeList(BFAbstractCBO &parent);
   virtual ~DailyTransactionsFeeList();

   // Initialize function
   SEVERITY init( const DString &dstrRecordType,
						const DString &dstrFeeCode,
						const DString &dstrFundCode,
						const DString &dstrClassCode,
						const DString &dstrEffectiveDate,
						const DString &dstrStopDate = I_( "9999/12/31" ),
						const DString &dstrRecId = I_( "0" ),
						const DString &dstrDuplicateCheck = I_("N"),
						const BFDataGroupId &idDataGroup  = BF::HOST, 
						const DString &dstrTrack = I_("N"), 
						const DString &dstrPageName = NULL_STRING );
   
   SEVERITY checkDuplicate( const DString &dstrRecId,
		                      const DailyTransactionsFee *pDailyTransactionsFeeToCheck, 
									 const BFDataGroupId &idDataGroup );

	SEVERITY checkDefaultExists( const DailyTransactionsFee *pDailyTransactionsFeeToCheck, 
									     const BFDataGroupId &idDataGroup );

   SEVERITY getMore();

	SEVERITY getDailyTransactionFee( const DString &dstrRecordType, 
												const DString &dstrFeeCode,
												const DString &dstrFundCode, 
												const DString &dstrClassCode,
												const DString &dstrEffectiveDate,
												const BFDataGroupId &idDataGroup,
												DailyTransactionsFee *&pDailyTransactionsFee );
protected:
   virtual SEVERITY doCreateObject( const BFData& data, 
												BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, 
													DString &strKey, 
													const BFDataGroupId& idDataGroup );
   virtual void getStrKey( DString &strKey, 
									const BFData *data );
private:
   void buildKey( DString &dstrKey, 
						const DString &dstrRecordType, 
						const DString &dstrFeeCode,
						const DString &dstrFundCode, 
						const DString &dstrClassCode,
						const DString &dstrEffectiveDate );

	SEVERITY iterateMemoryForDuplicateCheck( enum BFObjIter::ITERTYPE iterType, 
		                                      const DailyTransactionsFee *pDailyTransactionsFeeToCheck,
														  const DString &dstrRecordType,
														  const DString &dstrFeeCode,
						                          const DString &dstrFundCode,
						                          const DString &dstrClassCode,
						                          const DString &dstrEffectiveDate,
						                          const DString &dstrStopDate,
		                                      const BFDataGroupId &idDataGroup,
		                                      bool &blHasDuplicate );

   BFData *_pRequestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFeeList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:30:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Mar 05 2004 14:43:48   VADEANUM
//PET859 FN23 - ADL - use iterators with specialised type (i.e. ADDED, or DELETED)
//
//   Rev 1.4   Feb 25 2004 15:47:18   VADEANUM
//PET859 FN23 - ADl - separated duplicate check from default existance check.
//
//   Rev 1.3   Feb 25 2004 13:37:06   VADEANUM
//PET859 FN23 - ADL - Layout change for 284, modified signature of DailyTransactionsFeesList::init().
//
//   Rev 1.2   Feb 12 2004 13:25:58   VADEANUM
//PET859 FN23 - ADL - modified signature for init() and checkDuplicate().
//
//   Rev 1.1   Feb 10 2004 16:32:56   VADEANUM
//PET 859 FN23 - ADL - added getDailyTransactionFee()
//
//   Rev 1.0   Jan 28 2004 14:07:04   popescu
//Initial revision.
//
//
 */
