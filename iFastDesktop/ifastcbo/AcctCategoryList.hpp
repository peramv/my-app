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
// ^FILE   : AcctCategoryList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : Jan 21, 2003
//
// ^CLASS    : AcctCategoryList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif
class ErrMsgRulesList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

class IFASTCBO_LINKAGE AcctCategoryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   AcctCategoryList( BFAbstractCBO &parent );
   virtual ~AcctCategoryList();
   SEVERITY init( const DString&  dstrTrack = I_("N"),
                  const DString&  dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   bool isCategoryExist( const BFDataGroupId& idDataGroup, const DString& dstrCategoryType );

   SEVERITY getErrMsgValue( DString dstrErrNum,       
								  const BFDataGroupId& idDataGroup, 
								  DString& dstrErrValue ) ;
   void getDescriptions( const BFDataGroupId&, DString&);;

protected:
   void setAggregationType( const BFDataGroupId& idDataGroup );
   void getDefaultAggregationType( const DString& dstrCurrCategory, DString& dstrDefaultAggrMod ,
                                   const BFDataGroupId& idDataGroup );
   private:
   ErrMsgRulesList* _pErrMsgRulesList;


   //******************************************************************************
   // This method will execute when a CBO item is deleted from the list.   It will 
   // check to see if the deleted CBO has a AcctCategory of WRAP (04).  If it is
   // WRAP, it will call MFAccount::setWRAPAcctDefaults (false,idDataGroup) to reset
   // the defaults set when the WRAP category was added.
   // @param   const DSTring& strKey - key of CBO being deleted.
   //          const BFDataGroupId& idDataGroup - current data group id.
   //          bool bIsObjectDestroyed - is object being destroyed?
   // @returns SEVERITY - should always be NO_CONDITION
   //******************************************************************************
   SEVERITY doDeleteObject ( const DString&  strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed );
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCategoryList.hpp-arc  $
//
//   Rev 1.5   Sep 12 2004 15:09:18   HERNANDO
//PET1117 FN02 - Display account categories in the Trade Cautions combo box change.  Added fn. to retrieve a comma-delimited list of category descriptions.
//
//   Rev 1.4   Aug 11 2004 12:00:00   AGUILAAM
//PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
//
//   Rev 1.3   Mar 21 2003 17:55:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 15:03:32   HSUCHIN
//added doDeleteObject to reset MFAccount default values for WRAP accounts and changed validateAll to set MFAccount defaults for WRAP accounts.
//
//   Rev 1.1   Jan 25 2003 17:01:52   KOVACSRO
//Added isCategoryExist
//
//   Rev 1.0   Jan 21 2003 14:26:24   KOVACSRO
//Initial revision.

 */