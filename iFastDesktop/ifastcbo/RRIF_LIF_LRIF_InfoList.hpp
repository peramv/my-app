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
//******************************************************************************
//
// ^FILE   : RRIF_LIF_LRIF_InfoList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 07, 2000
//
// ^CLASS  : RRIF_LIF_LRIF_InfoList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//    implements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class BankList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RRIF_LIF_LRIF_InfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RRIF_LIF_LRIF_InfoList( BFAbstractCBO &parent );
   virtual ~RRIF_LIF_LRIF_InfoList();

   // Initialize function
   SEVERITY init( const DString& dstrAccountNum );
   SEVERITY init();

   SEVERITY search( bool bFirstRetrieve );

   void getBachParam(DString& strBachTrace,DString& strBatchName,DString& dstrEffectDate);
   void setPermit(bool &bPermit){_bPermit =  bPermit;};
   bool hasPermission(){return(_bPermit == true);};

   void AddCopy( DString& orgKey, DString& destKey, const BFDataGroupId& idDataGroup );

   SEVERITY setOverrideUnusedAmtApplicable( const BFDataGroupId& idDataGroup  );
   bool areAllRRIFRecordsInactive (const BFDataGroupId& idDataGroup);//added for CHG0041174

protected:
//	virtual void getStrKey ( DString &dstrKey, const Data *data );
   virtual SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, 
                               const BFDataGroupId& idDataGroup );
   SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY  EnquiryDataFromHost(bool bFirst,  const DString& dstrTrack= I_("N"),
                                 const DString& dstrPageName = NULL_STRING    );

private:
   SEVERITY setBatchParam();
   DString _strAccountNum;
   bool  _bPermit;
   BFData*   _pRequestDataRRIF_INFO;
   //BFData*   _pRequestDataRRIF_Alloc;
   //BFData*   _pRecvDataRRIF_LIF_LRIF_Alloc;
   BFData*   _pRecvDataRRIF_LIF_LRIF_Info;

   DString _dstrBatchTrace;
   DString _dstrBatchName;
   DString _dstrEffectiveDate;
};

///#endif // RRIF_LIF_LRIF_INFOLIST_HPP


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_InfoList.hpp-arc  $
 * 
 *    Rev 1.19   Sep 07 2006 16:56:48   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt. 
 * 
 *    Rev 1.18   Nov 14 2004 14:53:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.17   Mar 21 2003 18:22:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:53:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Aug 06 2002 09:56:34   KOVACSRO
 * Release 48. Converted allocations.
 * 
 *    Rev 1.13   22 May 2002 18:20:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Mar 2002 13:18:18   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.11   Nov 01 2001 10:22:44   YINGBAOL
 * remove sorting according to QA's requirement
 * 
 *    Rev 1.10   03 May 2001 14:04:48   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Apr 03 2001 15:49:00   YINGBAOL
 * change banklist due to VIEW100 has been changed
 * 
 *    Rev 1.8   Jan 18 2001 16:12:38   YINGBAOL
 * add etrack
 * 
 *    Rev 1.7   Nov 03 2000 11:33:24   YINGBAOL
 * take out morerecordsexist()
 * 
 *    Rev 1.6   Nov 02 2000 13:21:44   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.5   Oct 17 2000 14:55:28   YINGBAOL
 * add addcopy function and fix ither issues
 * 
 *    Rev 1.4   Sep 28 2000 14:58:58   YINGBAOL
 * a lot of changes in order to make things to work...
 * 
 *    Rev 1.3   Jun 09 2000 18:01:46   PETOLESC
 * Save work.
 * 
 *    Rev 1.2   Mar 31 2000 16:20:32   YINGBAOL
 * chnage
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
// 
*/


