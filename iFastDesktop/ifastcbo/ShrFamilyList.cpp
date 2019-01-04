//*****************************************************************************
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
//*****************************************************************************
//
// ^FILE   : ShrFamilyList.cpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 09, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ShrFamilyList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "shrfamilylist.hpp"
#include "shrfamily.hpp"
#include <ifastdataimpl\dse_dstc0233_req.hpp>

#include <ifastdataimpl\dse_dstc0234_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0233_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("ShrFamilyList");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FAMILY;
}

namespace CND
{
   extern const long ERR_DUPLICATE_TYPE_FOR_FAMILY_CODE;
   extern const long ERR_DUPLICATE_RECORD;
}

namespace SHAREHOLDER_TYPE
{
   extern const I_CHAR * const DSC;
   extern const I_CHAR * const MFR_HOUSEHOLDING;
}

//******************************************************************************
ShrFamilyList::ShrFamilyList(BFAbstractCBO &parent) 
: MFCanBFCbo(parent) 
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
ShrFamilyList::~ShrFamilyList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ShrFamilyList::initNew(const DString& shrNum, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFamilyList::init( const DString& shrNum, 
                              const DString& dstrTrack, 
                              const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString mgmtCoIdOut;
   BFData queryData(ifds::DSTC0233_REQ);

   queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   queryData.setElementValue(ifds::ShrNum, shrNum, false, false);
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);
   ReceiveData (DSTC_REQUEST::SHR_FAMILY, queryData, ifds::DSTC0233_VW, DSTCRequestor(getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFamilyList::doCreateNewObject(BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   ShrFamily *shrfamily = new ShrFamily(*this);

   shrfamily->initNew (idDataGroup);
   pBase = shrfamily;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFamilyList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   pObjOut = new ShrFamily(*this);
   ((ShrFamily*) (pObjOut))->init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFamilyList::doValidateAll (const BFDataGroupId& idDataGroup, 
                                       long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));


   std::set< DString > setCharacteristic;
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
      ShrFamily *pShrFamilyToCheck = dynamic_cast<ShrFamily*>(iter.getObject());
      if( pShrFamilyToCheck != NULL )
      {
         checkDuplicate ( pShrFamilyToCheck, idDataGroup );
      }
      ++iter; 
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY ShrFamilyList::checkDuplicate ( const ShrFamily *pShrFamilyToCheck, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));

   DString familyType;

   pShrFamilyToCheck->getField (ifds::FamilyType, familyType, idDataGroup, false);
   familyType.strip().upperCase();

   bool hasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter (*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      ShrFamily *pShrFamily = dynamic_cast<ShrFamily*>(iter.getObject());

      if (pShrFamily != pShrFamilyToCheck)
      {
         DString familyType_;

         pShrFamily->getField (ifds::FamilyType, familyType_, idDataGroup, false);
         if ( familyType == familyType_ )
         {
            hasDuplicate = true;
            break;
         }
      }
      ++iter;
   }
   
   if (hasDuplicate)
   { //check the memory again for possible deleted duplicates
      BFObjIter iterInMemory (*this, idDataGroup);

      while (!iterInMemory.end())
      {
         if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
         {
            DString deletedFamilyType;
            ShrFamily *pDeletedShrFamily = 
               dynamic_cast<ShrFamily*>(iterInMemory.getObject());

            pDeletedShrFamily->getField (ifds::FamilyType, deletedFamilyType, idDataGroup);
            deletedFamilyType.upperCase ();
            if ( familyType == deletedFamilyType )
            {
               hasDuplicate = false;
               break;
            }
         }
         ++iterInMemory;
      }
   }
   if (hasDuplicate)
   {
      ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFamilyList.cpp-arc  $
// 
//    Rev 1.9   Dec 09 2011 22:10:34   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.8   Dec 09 2011 11:45:14   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.7   Nov 09 2011 23:54:58   popescu
// P0188902 FN02 - DYN Household Project, implement duplicate check
// 
//    Rev 1.6   Nov 09 2011 18:35:28   dchatcha
// P0188902 FN02 - DYN Household Project, interim checking in.
// 
//    Rev 1.5   Nov 14 2004 14:55:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   May 22 2003 14:13:16   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.3   Mar 21 2003 18:25:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Jan 14 2003 17:41:08   sanchez
// added  Revision Control Entries
 */