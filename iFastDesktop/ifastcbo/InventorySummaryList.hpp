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
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   :InventorySummaryList
// ^DATE   : Feb 12, 2004
//
// ^CLASS  : InventorySummaryList
// ^PARENT : ListBase
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

class BFData;
class InventoryDetailsList;

class IFASTCBO_LINKAGE InventorySummaryList : public MFCanBFCbo, private boost::noncopyable
{
public:

   //******************************************************************************
   // Constructor
   // @param   BFBase - pointer to the parent BFBase
   //******************************************************************************

   InventorySummaryList( BFAbstractCBO &parent );

   //******************************************************************************
   // Destructor
   //******************************************************************************

   virtual ~InventorySummaryList();

   //******************************************************************************
   // Overloaded Function - Initalize CBO and executes view call
   // @param   const DString& dstrAccountNumber - Account Number ( Required )
   // @param   const DString& dstrFundCode - Fund Code 
   // @param   const DString& dstrClassCode - Class Code 
   // @param   const DString& dstrActiveOnly - Active Only
   // @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
   // @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //******************************************************************************

   SEVERITY init( const DString& strAccountNumber, 
                  const DString& dstrFundCode,
                  const DString& dstrClassCode,
                  const DString& dstrActiveOnly,
                  const DString& dstrTrack= I_("N"),                  
                  const DString& dstrPageName = NULL_STRING );

	 DString getUnitsTotal() { return(m_dstrUnitsTotal);}

    DString getTotalCBFreeUnits() { return( m_dstrTotalCBFreeUnits ); }

   //******************************************************************************
   // getMore retrieves more data.
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.   
   //******************************************************************************

   SEVERITY getMore ( );   

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup );

private:
   BFData *_pRequestData;                //Stores the request data object to be used by getMore
   BFData *_pResponseData;
   DString m_dstrUnitsTotal;
   DString m_dstrTotalCBFreeUnits;
   
   DString m_dstrSortBy,
      m_dstrSortOrder,
      m_dstrAccountNumber,
      m_dstrFundCode,
      m_dstrClassCode,
      m_dstrActiveOnly;
};

///#endif //INVENTORYSUMMARYLIST_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InventorySummaryList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:48:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   May 25 2004 20:12:02   HERNANDO
//PET1046 FN01 - Changed use of TotalCBFreeUnits; changed function getTotalCBFreeUnits.
//
//   Rev 1.4   May 19 2004 17:49:14   HERNANDO
//PET1046 FN01 - Added LSIF/Inventory Details support; made use of InventorySummary.
//
//   Rev 1.3   Mar 10 2004 17:48:38   ZHANGCEL
//PET 1001-FN01: fix crash when clikcing F11
//
//   Rev 1.1   Feb 26 2004 17:16:58   ZHANGCEL
//PET1001 - FN01 Added logic to cope with the UnitsTatol issue
//
//   Rev 1.0   Feb 24 2004 10:41:34   ZHANGCEL
//Initial revision.
//
*/