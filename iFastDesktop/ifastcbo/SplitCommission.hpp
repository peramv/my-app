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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SplitCommission.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : February  26, 2001
//
// ^CLASS    : SplitCommission
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

class IFASTCBO_LINKAGE SplitCommission : public MFCanBFCbo, private boost::noncopyable
{
friend class SplitCommissionList;
public:
   //the below static methods check for the commission type,
   //a general control option, field 'CommissionType'
   static bool isTypeZERO(DSTCWorkSession &rpDSTCWorkSession);
   static bool isTypeONE (DSTCWorkSession &rpDSTCWorkSession);
   static bool isTypeTWO (DSTCWorkSession &rpDSTCWorkSession);
public:
   SplitCommission (BFAbstractCBO &parent);
   virtual ~SplitCommission();
   SEVERITY init (const BFData &data);
   SEVERITY checkDateStatus (const DString& dstrStopDate, long lcondition, 
      const BFDataGroupId& idDataGroup);
   SEVERITY initNew (const BFDataGroupId& idDataGroup);
   virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false) const;
   void changeFieldsForRebook();
protected:
   SEVERITY doValidateField(
      const BFFieldId& idField, 
      const DString& strValue, 
      const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges (
      const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);   
   void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);

   virtual SEVERITY doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup);

private:
   void calculateTheCommissionAmount (const BFDataGroupId& idDataGroup);
   SEVERITY checkBroker (const DString& brokerCode, 
                          const BFDataGroupId& idDataGroup, 
                          bool condition_returned);

   SEVERITY checkBranches (const DString& branchCode, 
                            const BFDataGroupId& idDataGroup, 
                            bool condition_returned);

   SEVERITY checkAgents(const DString& slsRepCode, 
                         const BFDataGroupId& idDataGroup, 
                         bool condition_returned);

   bool slsRepByBranch (const BFDataGroupId& idDataGroup);

   DString _salesRepByBranch;
   DString _brokerName;
   DString _branchName;
   DString _agentName;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SplitCommission.hpp-arc  $
//
//   Rev 1.22   Jul 08 2005 09:31:52   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.21   Jun 30 2005 12:39:10   popescu
//Incident # 338532 - fixed nbr of decimals on the split commission screen for amounts and percentages  - amount fields are formatted to 2 decimals, percentages to 4
//
//   Rev 1.20   Nov 14 2004 14:56:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.19   Dec 08 2003 15:28:22   popescu
//PTS 10023645, split commission re-work
//
//   Rev 1.18   Oct 22 2003 09:47:02   popescu
//PTS 10022763, the comm amount failed to be calculated when discounting the fee at the trade level
//
//   Rev 1.17   May 13 2003 10:06:08   popescu
//Split commission re-work
//
//   Rev 1.16   Apr 29 2003 17:08:08   popescu
//PTS 10016204
//
//   Rev 1.15   Apr 25 2003 16:33:14   popescu
//PTS Work:10016245,
//
//   Rev 1.14   Apr 04 2003 10:18:42   popescu
//split commsion work
//
//   Rev 1.13   Mar 21 2003 18:25:08   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.12   Oct 09 2002 23:55:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.11   Aug 29 2002 12:53:42   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.10   22 May 2002 18:19:52   PURDYECH
//BFData Implementation
//
//   Rev 1.9   19 Mar 2002 13:18:32   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.8   07 Nov 2001 15:38:00   HSUCHIN
//clean up and added global commission type
//
//   Rev 1.7   26 Sep 2001 11:47:24   HSUCHIN
//added function check status to check broker/branch/slsrep status (active/inactive) 
//
//   Rev 1.6   03 May 2001 14:04:54   SMITHDAV
//Session management restructuring.
//
//   Rev 1.5   Mar 22 2001 14:13:42   HSUCHIN
//added transaction allocations hook up
//
//   Rev 1.4   Mar 19 2001 15:04:12   HSUCHIN
//additional processing and validation
//
//   Rev 1.3   Mar 13 2001 09:14:20   HSUCHIN
//Check in for Zijian
//
//   Rev 1.2   Mar 08 2001 15:33:04   YINGZ
//make it work
//
//   Rev 1.1   Feb 27 2001 15:49:44   YINGZ
//for robert
 * 
 */
