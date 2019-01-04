#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1




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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntityIdsList.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : March 16, 1999
//
// ^CLASS    : EntityIdsList
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


class IFASTCBO_LINKAGE EntityIdsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   EntityIdsList( BFAbstractCBO &parent );
   virtual ~EntityIdsList();

   SEVERITY init ( const DString& entityId, 
                   const DString &entityType,
                   const BFDataGroupId &idDataGroup);
   SEVERITY init ( const DString& entityId,
                   const DString &entityType,
                   const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING);
   SEVERITY init ( BFData &data, 
                   const DString &entityId,
                   const DString &entityType);
   void getEntityId (DString &entityId) const;
   void setEntityType (const DString &entityType);
   void getMandatoryIdsDesc (const BFDataGroupId &idDataGroup, 
                             const DString &dstrMandIds, 
                             DString &dstrIdsDesc);   
   bool isIdTypeExist( const DString& dstrIdType, 
                       const BFDataGroupId& idDataGroup ); //MT535/MT536
   bool isIdTypeExistWithValue( const DString& dstrIdType, 
                       const BFDataGroupId& idDataGroup );
   int getNumIdTypeRecord( const DString& dstrIdType, 
                           const BFDataGroupId& idDataGroup ); //MT535/MT536
   SEVERITY updateParentEntitySIN(const BFDataGroupId &idDataGroup);
   bool EntityIdsList::bCheckIdTypeExistsInDB(DString dstrIdTypeIn );
   SEVERITY getIdByType(const DString& idType, const BFDataGroupId &idDataGroup, DString& id);
protected:
   SEVERITY doCreateObject (const BFData& data, 
      BFCBO*& pObjOut);
   SEVERITY doCreateNewObject (BFCBO *&pBase, 
      DString &strKey, 
      const BFDataGroupId &idDataGroup);
   SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, 
      long lValidateGroup);
   virtual SEVERITY doDeleteObject (const DString &strKey, 
      const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed);
   
private:
   SEVERITY checkForDuplicateClearingPlatform (const DString &clearingPlatformValue, 
                                               const BFDataGroupId &idDataGroup); //MT535/MT536*/

   SEVERITY validateIDsForFundSponsorEntity(const DString &strRelationship,const BFDataGroupId& idDataGroup );
   bool isLinkedWithWhereUsedRelationship(const DString& strRelationship,const BFDataGroupId& idDataGroup);

   DString _entityId,
           _entityType;
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityIdsList.hpp-arc  $ 
 * 
 *    Rev 1.23   Jul 12 2012 18:47:02   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.22   Jul 26 2011 00:41:00   wutipong
 * IN#2473119 - ECF Marketing File - revised
 * 
 *    Rev 1.21   Oct 01 2009 11:39:32   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer, Code review.
 * 
 *    Rev 1.20   Sep 28 2009 07:55:06   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer.
 * 
 *    Rev 1.19   Jan 27 2009 06:12:58   daechach
 * Fix Revision control entries again.
 * 
 *    Rev 1.18   Jan 27 2009 06:06:20   daechach
 * Revision Control Entries.
*/
