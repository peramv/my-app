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
// ^FILE   : PaymentInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : PaymentInstructionsList
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
class PaymentInstructions;

class IFASTCBO_LINKAGE PaymentInstructionsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   PaymentInstructionsList(BFAbstractCBO &parent);
   virtual ~PaymentInstructionsList();

   // Initialize function
   SEVERITY init( const DString &dstrBrokerCode = NULL_STRING,
                  const DString &dstrBranchCode = NULL_STRING,
                  const DString &dstrSalesRepCode = NULL_STRING,
                  const DString &dstrPaymentFor = NULL_STRING,
		            const DString &dstrSearchTypeMgmt = NULL_STRING,
                  const DString &dstrDuplicateCheck = I_("N"),
		            const DString &dstrEffectiveDate  = NULL_STRING,
		            const DString &dstrPayInstructionsId = NULL_STRING,
                  const DString &dstrStopDate = NULL_STRING,
                  const BFDataGroupId &idDataGroup = BF::HOST, 
                  const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
   SEVERITY checkDuplicate ( const PaymentInstructions *pPaymentInstructionsToCheck, 
                             const BFDataGroupId &idDataGroup,
                             bool bDuplicateError = true);
   SEVERITY getMore();
	bool isNotDeleted( const BFDataGroupId &idDataGroup,
							 const DString &pairPayInstructRID);

	bool isNotAdded( const BFDataGroupId &idDataGroup,
						  const DString &dstrBrokerCode,
						  const DString &dstrBranchCode,
						  const DString &dstrSalesRepCode,
						  const DString &lookingForPaymentFor,
						  const DString &dstrEffectiveDate,
						  const DString &dstrStopDate);

protected:
   virtual SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, 
                                       const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
   virtual void getStrKey (DString &strKey, const BFData *data);
	SEVERITY doValidateAll ( const BFDataGroupId& idDataGroup, 
                            long lValidateGroup
									 );
	
private:
   void buildKey( DString& dstrKey, 
                  const DString &brokerCode, 
                  const DString &branchCode, 
                  const DString &balesRepCode, 
                  const DString &paymentForCode,
		          const DString &companyCode,
				  const DString& dstrEffectiveDate,
				  const DString& dstrStopDate);
   BFData *_pRequestData;
	DString _searchTypeMgmt;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PaymentInstructionsList.hpp-arc  $
//
//   Rev 1.11   May 01 2007 10:25:38   jankovii
//IN 862766 - Payment instr.
//
//   Rev 1.10   Nov 03 2006 16:21:16   ZHANGCEL
//Incident 731541 -- Add logice to check Pair
//
//   Rev 1.9   Oct 20 2006 18:14:54   popescu
//Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
//
//   Rev 1.8   Sep 10 2006 17:59:12   popescu
//STP 2192/12
//
//   Rev 1.7   Aug 28 2006 15:40:04   ZHANGCEL
//PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
//
//   Rev 1.6   Jul 27 2006 18:01:00   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.5   Nov 14 2004 14:50:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Jul 11 2003 20:07:40   popescu
//strip all and uppercase the br,bra, slsrep codes
//
//   Rev 1.3   Jul 11 2003 13:47:00   popescu
//fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
//
//   Rev 1.2   Jul 10 2003 22:21:06   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.1   Jul 09 2003 21:56:58   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.0   Jul 01 2003 18:17:18   popescu
//Initial revision.
//
//   Rev 1.0   Jun 27 2003 18:16:52   popescu
//Initial revision.
//
 */
