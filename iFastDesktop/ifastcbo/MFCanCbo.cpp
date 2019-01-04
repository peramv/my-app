// MFCanCbo.cpp: 
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mfcancbo.hpp"
#include "mgmtco.hpp"
#include "errmsgruleslist.hpp"
#include "dstcviewtimetxnstatelement.hpp"
#include "ConditionObject.h"

namespace 
{
   const I_CHAR * const BLANK_SUBSTITUTION = I_( " = ;"); // substitution with only one element with tag = value = " " 
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
}


//******************************************************************************
MFCanBFCbo::MFCanBFCbo(BFAbstractCBO &parent)
: BFCBO(&parent)
, _session( parent.getSession() )
, _notifyCondition(NULL)
{
}

//******************************************************************************
MFCanBFCbo::~MFCanBFCbo()
{
   delete _notifyCondition;
}

Condition* MFCanBFCbo::getNotifyCondition() const {
   return( _notifyCondition );
}

void MFCanBFCbo::donotifyResponse ( SEVERITY severity, 
                                    const Condition *condition, 
                                    BFData *receivedData, 
                                    bool moreAvailable,
                                    int callBackOption )
{
   BFCBO::donotifyResponse( severity, condition, receivedData, moreAvailable, callBackOption );
   if( WARNING < severity && NULL != condition ) {
      _notifyCondition = new Condition( *condition );
   }
}


//******************************************************************************
const BFSession &
MFCanBFCbo::getSession() const
{
   return(_session);
}

//******************************************************************************
BFSession &
MFCanBFCbo::getSession()
{
   return(_session);
}

//******************************************************************************
const DSTCGlobalSession &
MFCanBFCbo::getGlobalSession() const
{
   return(dynamic_cast<const DSTCGlobalSession &>(_session.getGlobalSession()));
}

//******************************************************************************
DSTCGlobalSession &
MFCanBFCbo::getGlobalSession()
{
   return(dynamic_cast<DSTCGlobalSession &>(_session.getGlobalSession()));
}

//******************************************************************************
const DSTCWorkSession &
MFCanBFCbo::getWorkSession() const
{
   if( !_session.isBFWorkSession() )
   {
      assert(0);
      throw;
   }
   return(dynamic_cast<const DSTCWorkSession &>(_session));
}

//******************************************************************************
DSTCWorkSession &
MFCanBFCbo::getWorkSession()
{
   if( !_session.isBFWorkSession() )
   {
      assert(0);
      throw;
   }
   return(dynamic_cast<DSTCWorkSession &>(_session));
}

//******************************************************************************
const DSTCUserSession &
MFCanBFCbo::getUserSession() const
{
   return(dynamic_cast<const DSTCUserSession &>(_session.getUserSession()));
}

//******************************************************************************
DSTCUserSession &
MFCanBFCbo::getUserSession()
{
   return(dynamic_cast<DSTCUserSession &>(_session.getUserSession()));
}

//******************************************************************************
const DSTCSecurity *
MFCanBFCbo::getSecurity(const DSTCHost &host) const
{
   return(dynamic_cast<const DSTCSecurity *>(_session.getSecurity(host)));
}

//******************************************************************************
const DSTCSecurity *
MFCanBFCbo::getSecurity() const
{
   return(getSecurity(DSTCHost::getPrimaryHost()));
}

//******************************************************************************
MgmtCo &
MFCanBFCbo::getMgmtCo()
{
   if( _session.isBFWorkSession() )
   {
      return(dynamic_cast<DSTCWorkSession &>(_session).getMgmtCo());
   }
   else if( _session.isBFGlobalSession() )
   {
      return(dynamic_cast<MgmtCo &>(*getTopLevelAncestor()));
   }
   else
   {
      assert(0);
      throw;
   }

}

//******************************************************************************
const MgmtCo &
MFCanBFCbo::getMgmtCo() const
{
   if( _session.isBFWorkSession() )
   {
      return(dynamic_cast<const DSTCWorkSession &>(_session).getMgmtCo());
   }
   else if( _session.isBFGlobalSession() )
   {
      return(dynamic_cast<const MgmtCo &>(*getTopLevelAncestor()));
   }
   else
   {
      assert(0);
      throw;
   }

}

//******************************************************************************
DString &
MFCanBFCbo::getMgmtCoId(DString &outString) const
{
   getMgmtCo().getField(ifds::CompanyId, outString, BF::HOST);
   return(outString);
}


//******************************************************************************
bool 
MFCanBFCbo::loadSubstitutionList( const BFFieldId& idField, 
                                  const BFDataGroupId& idDataGroup,
                                  const DString& strCodesList,
                                  bool bStripLeadingZeros, /* = false */
                                  bool bAddCodeToDescription /* = false */)
{
   DString strAllSubstList;
   DString strNewSubstList;

   setFieldSubstituteValues( idField, idDataGroup, idField ); //stupid, get the properties from repository
   BFProperties * pBFProperties = getFieldProperties( idField, idDataGroup );
   pBFProperties->getSubstituteValues( strAllSubstList );
   if( strAllSubstList.empty() )
   {
      assert(0);  //substitution list for this field is empty
      return(false);
   }

   getSubstitutionList( strAllSubstList, strCodesList, bStripLeadingZeros, bAddCodeToDescription, strNewSubstList );

   if( strNewSubstList.empty() )
   {
//      assert(0);  //there is no match beetween the values from substitution list and the codes list
      return(false);
   }
   else
   {
      setFieldAllSubstituteValues( idField, idDataGroup, strNewSubstList );
      pBFProperties->setSubstituteValues( NULL );
      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
      return(true);
   }

}

//******************************************************************************
DString MFCanBFCbo::removeItemFromSubtList (
   const BFFieldId &idField, 
   const DString &value,
   const BFDataGroupId &idDataGroup)
{
	DString substList;
   BFProperties *pProperties = getFieldProperties (idField, idDataGroup);

   pProperties->getSubstituteValues (substList);
   return removeItemFromSubtList (substList, value);
}

//******************************************************************************
DString MFCanBFCbo::removeItemFromAllSubtList (
   const BFFieldId &idField, 
   const DString &value,
   const BFDataGroupId &idDataGroup)
{
	DString substList;
   BFProperties *pProperties = getFieldProperties (idField, idDataGroup);

   pProperties->getAllSubstituteValues (substList);
   return removeItemFromSubtList (substList, value);
	  
}

//******************************************************************************
DString MFCanBFCbo::removeItemFromSubtList(
   const DString &substList, 
   const DString &value)
{
   DString returnsubList (substList),
      substList_(substList),
      tmp (value + I_("="));
	int nPos = substList_.find (tmp);
	
   if (nPos != DString::npos)
	{
	  returnsubList = substList_.left (nPos);
	  tmp = substList_.right (substList_.length() - nPos);

     int rnPos = tmp.find (';');

     if (rnPos != DString::npos)
	  {
		  returnsubList += tmp.right (tmp.length() - rnPos - 1) ;
	  }
	}
	return returnsubList;
}

//******************************************************************************
DString MFCanBFCbo::addItemToSubtList( 
   const BFFieldId &idField,
   const DString& dstrValue, 
   const BFDataGroupId& idDataGroup)
{
	DString substList;
	DString returnsubList = substList;
	BFProperties *pProperties = getFieldProperties ( idField, idDataGroup);
    pProperties->getAllSubstituteValues (substList);
	
	int nPos = substList.find( dstrValue );
	if( nPos == DString::npos )
	{
		returnsubList = substList + dstrValue;
	}
	return returnsubList;
}


//******************************************************************************
void MFCanBFCbo::setAllSubstituteValuesForField (
   const BFFieldId &idField,
   const BFDataGroupId &idDataGroup, 
   const BFFieldId &idField2) 
{
   DString substList;	  
   
   BFProperties *pProperties = getFieldProperties (idField2, idDataGroup);
   pProperties->getAllSubstituteValues (substList);
   setFieldAllSubstituteValues (idField, idDataGroup, substList);
}

//***********************************************************************************************************
void MFCanBFCbo::getSubstitutionList( const DString& strAllSubstList, 
                                      DString strCodesList, 
                                      bool bStripLeadingZeros, 
                                      bool bAddCodeToDescription,
                                      DString &strSubstListOut )
{  
   //first, replace in strCodesList the "," with " ", 
   int iPos;
   while( true )
   {
      iPos = strCodesList.find( I_( "," ) );
      if( iPos == DString::npos ) break;
      strCodesList.replace( iPos, 1, I_( " " ) );
   }

   //extract from strCodesList one single strCode;
   //get its description from strAllSubstList;
   //add this pair (strCode, strDescription) to the substitution list
   BFSubst lBFSubst;
   DString strCode;
   DString strDescription;

   int iTotalWords =  strCodesList.words();
   for( int iCurrentWord = 0; iCurrentWord < iTotalWords; iCurrentWord++ )
   {
      strCode = strCodesList.word( iCurrentWord );
      if( bStripLeadingZeros )
         strDescription = DSTCommonFunctions::getDescription( strCode.stripLeading( I_CHAR('0') ), strAllSubstList );
      else
         strDescription = DSTCommonFunctions::getDescription( strCode, strAllSubstList );

      if( strDescription != NULL_STRING )
      {
         if( bAddCodeToDescription )
            lBFSubst.addSubst( strCode, strCode + BLANK_STRING + BLANK_STRING + strDescription );
         else
            lBFSubst.addSubst( strCode, strDescription );
      }
   }

   lBFSubst.getList( strSubstListOut );
//   strSubstListOut.upperCase();  //### Always UPPER ?? NO!
}

//*****************************************************************************
SEVERITY MFCanBFCbo::getErrMsg ( const DString &errorCode,
                                 long lErrConditionId, 
                                 long lWarnConditionId, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &idiStr /*=NULL_STRING*/
                               )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           I_("MFCanBFCbo"), 
                           I_("getErrMsg")
                         );
   ErrMsgRulesList *pErrMsgRulesList = NULL;

   if ( getMgmtCo ().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
        pErrMsgRulesList
      )
   {
      pErrMsgRulesList->getEWI ( errorCode, 
                                 lErrConditionId, 
                                 lWarnConditionId, 
                                 idDataGroup, 
                                 idiStr
                               );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
//Impelemting configurable error for the new condition objects ..robs...

//*****************************************************************************
SEVERITY MFCanBFCbo::getErrMsg ( const DString &errorCode,
                                 CConditionObject &errrObject, 
                                 CConditionObject &warnObject, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &idiStr /*=NULL_STRING*/
                               )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           I_("MFCanBFCbo"), 
                           I_("getErrMsg")
                         );
   ErrMsgRulesList *pErrMsgRulesList = NULL;

   if ( getMgmtCo ().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
        pErrMsgRulesList )
     {    
        pErrMsgRulesList->getEWI ( errorCode, 
                                   errrObject, 
                                   warnObject, 
                                   idDataGroup, 
                                   idiStr
                                 );
    }
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
// return -1 if not found.
// return  1 if include.
// return  0 if exclude.
//***************************************************************************************
int MFCanBFCbo::isCodeAllowed  (const DString& dstrCode, const DString& dstrCodeList) 
{
   DString dstrCopyCodeList = dstrCodeList;
   int iPos = dstrCopyCodeList.find(',');     
   int iFound = -1;
   DString dstrCurrentCode;
   if  (iPos < 0) {
      //Final state, only one element in list.
      dstrCurrentCode = dstrCopyCodeList;
   } else {
      // If an exclude code is found, we will simply return exclude.
      iFound = isCodeAllowed  (dstrCode, dstrCopyCodeList.right  (dstrCopyCodeList.length() - iPos - 1));
      if  (iFound == 0)
         return 0;
      dstrCurrentCode = dstrCopyCodeList.left  (iPos);
   }   
   int iExcludePos = dstrCurrentCode.find('!');

   dstrCurrentCode.strip();
   if  (iExcludePos >= 0) {
      dstrCurrentCode.strip ('!');
      if  (dstrCurrentCode == dstrCode)
         return 0;
      else {
         return iFound;
      }
   } else if  (dstrCurrentCode == I_("*")){ //ALL
      return  (iFound < 0)?1:iFound;
   } else if  (dstrCode == dstrCurrentCode) {
      return 1;
   } else {
      return iFound;
   }
}

//***************************************************************************************
bool MFCanBFCbo::isCodeInList (const DString& dstrCode, const DString& dstrCodeList) 
{
   int iResult = isCodeAllowed  (dstrCode, dstrCodeList);
   return  (iResult > 0);

}

//***********************************************************************************************************
SEVERITY MFCanBFCbo::ReceiveData ( const BFRequest &request,
                                   BFData &queryData,
                                   BFData &receivedData,
                                   BFRequestor &requestor,
                                   bool bInsertLast
                                 )
{
   try {
      const DSTCRequest& dstcRequest = dynamic_cast< const DSTCRequest& >( request );
      DSTCRequestor& dstcRequestor = dynamic_cast< DSTCRequestor& >( requestor );
      dstcRequestor.setRecycleOnReceive( dstcRequest.isQueryRequest() );
   } 
   catch( ... ) {}

   return BFCBO::ReceiveData (request, queryData, receivedData, requestor, bInsertLast);
}

//***********************************************************************************************************
SEVERITY MFCanBFCbo::ReceiveData ( const BFRequest &request,
                                   BFData &queryData,
                                   long responseDataSetId,
                                   BFRequestor &requestor,
                                   bool bInsertLast
                                 )
{
   try {
      const DSTCRequest& dstcRequest = dynamic_cast< const DSTCRequest& >( request );
      DSTCRequestor& dstcRequestor = dynamic_cast< DSTCRequestor& >( requestor );
      dstcRequestor.setRecycleOnReceive( dstcRequest.isQueryRequest() );
   } 
   catch( ... ) {}

   return BFCBO::ReceiveData (request, queryData, responseDataSetId, requestor, bInsertLast);
}
//**********************************************************************************************************
void 
MFCanBFCbo::replaceSubstitutionList(const DString &newList, 
                                             const BFFieldId& idFieldFrom,
                                             const BFFieldId& idFieldTo, 
                                             const BFDataGroupId& idDataGroup)
{//P0186486_FN15_The Source of Funds
   //set particular list 
   loadSubstitutionList( idFieldFrom , idDataGroup, newList );

   //replace the existing list with the new one
   DString newlist_;
   BFProperties *pBFProperties = getFieldProperties (idFieldFrom, idDataGroup); 
   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (newlist_);

      setFieldAllSubstituteValues (idFieldTo, idDataGroup, newlist_);
      pBFProperties->setSubstituteValues(NULL);
   } 

}

//DS//***********************************************************************************************************
//DS//***********************************************************************************************************
//DSMFCanWSCbo::MFCanWSCbo( DSTCWorkSession &parent )
//DS: MFCanBFCbo( parent )
//DS, workSession_( parent )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanWSCbo::MFCanWSCbo( MFCanWSCbo &parent )
//DS: MFCanBFCbo( parent )
//DS, workSession_( parent.getWorkSession() )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanWSCbo::~MFCanWSCbo()
//DS{
//DS}
//DS
//DS//******************************************************************************
//DSconst BFSession &
//DSMFCanWSCbo::getSession() const
//DS{
//DS   return workSession_;
//DS}
//DS
//DS//******************************************************************************
//DSBFSession &
//DSMFCanWSCbo::getSession()
//DS{
//DS   return workSession_;
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCGlobalSession &
//DSMFCanWSCbo::getGlobalSession() const
//DS{
//DS   return dynamic_cast<const DSTCGlobalSession &>(workSession_.getGlobalSession());
//DS}
//DS
//DS//******************************************************************************
//DSDSTCGlobalSession &
//DSMFCanWSCbo::getGlobalSession()
//DS{
//DS   return dynamic_cast<DSTCGlobalSession &>(workSession_.getGlobalSession());
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCWorkSession &
//DSMFCanWSCbo::getWorkSession() const
//DS{
//DS   return workSession_;
//DS}
//DS
//DS//******************************************************************************
//DSDSTCWorkSession &
//DSMFCanWSCbo::getWorkSession()
//DS{
//DS   return workSession_;
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCUserSession &
//DSMFCanWSCbo::getUserSession() const
//DS{
//DS   return dynamic_cast<const DSTCUserSession &>(workSession_.getUserSession());
//DS}
//DS
//DS//******************************************************************************
//DSDSTCUserSession &
//DSMFCanWSCbo::getUserSession()
//DS{
//DS   return dynamic_cast<DSTCUserSession &>(workSession_.getUserSession());
//DS}
//DS
//DS//******************************************************************************
//DSMgmtCo &
//DSMFCanWSCbo::getMgmtCo()
//DS{
//DS   return workSession_.getMgmtCo();
//DS}
//DS
//DS//******************************************************************************
//DSconst MgmtCo &
//DSMFCanWSCbo::getMgmtCo() const
//DS{
//DS   return workSession_.getMgmtCo();
//DS}
//DS
//DS//******************************************************************************
//DSDString &
//DSMFCanWSCbo::getMgmtCoId(DString &outString) const
//DS{
//DS   getMgmtCo().getField(ifds::CompanyId, outString, BF::HOST);
//DS   return outString;
//DS}
//DS
//DS//***********************************************************************************************************
//DS//***********************************************************************************************************
//DSMFCanGSCbo::MFCanGSCbo( DSTCGlobalSession &parent )
//DS: MFCanBFCbo( parent )
//DS, globalSession_( parent )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanGSCbo::MFCanGSCbo( MFCanGSCbo &parent )
//DS: MFCanBFCbo( parent )
//DS, globalSession_( parent.getGlobalSession() )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanGSCbo::~MFCanBFCbo()
//DS{
//DS}
//DS
//DS//******************************************************************************
//DSconst BFSession &
//DSMFCanGSCbo::getSession() const
//DS{
//DS  return globalSession_;
//DS}
//DS
//DS//******************************************************************************
//DSBFSession &
//DSMFCanGSCbo::getSession()
//DS{
//DS  return globalSession_;
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCGlobalSession &
//DSMFCanGSCbo::getGlobalSession() const
//DS{
//DS  return globalSession_;
//DS}
//DS
//DS//******************************************************************************
//DSDSTCGlobalSession &
//DSMFCanGSCbo::getGlobalSession()
//DS{
//DS  return globalSession_;
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCUserSession &
//DSMFCanGSCbo::getUserSession() const
//DS{
//DS   return dynamic_cast<const DSTCUserSession &>(globalSession_.getUserSession());
//DS}
//DS
//DS//******************************************************************************
//DSDSTCUserSession &
//DSMFCanGSCbo::getUserSession()
//DS{
//DS   return dynamic_cast<DSTCUserSession &>(globalSession_.getUserSession());
//DS}
//DS
//DS//******************************************************************************
//DSMgmtCo &
//DSMFCanGSCbo::getMgmtCo()
//DS{
//DS   return dynamic_cast<MgmtCo &>(*getTopLevelAncestor());
//DS}
//DS
//DS//******************************************************************************
//DSconst MgmtCo &
//DSMFCanGSCbo::getMgmtCo() const
//DS{
//DS   return dynamic_cast<const MgmtCo &>(*getTopLevelAncestor());
//DS}
//DS
//DS//******************************************************************************
//DSDString &
//DSMFCanGSCbo::getMgmtCoId(DString &outString) const
//DS{
//DS   getMgmtCo().getField(ifds::CompanyId, outString, BF::HOST);
//DS   return outString;
//DS}
//DS
//DS//***********************************************************************************************************
//DS//***********************************************************************************************************
//DSMFCanUSCbo::MFCanUSCbo( DSTCUserSession &parent )
//DS: MFCanBFCbo( parent )
//DS, userSession_( parent )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanUSCbo::MFCanUSCbo( MFCanUSCbo &parent )
//DS: MFCanBFCbo( parent )
//DS, userSession_( parent.getUserSession() )
//DS{
//DS}
//DS
//DS//***********************************************************************************************************
//DSMFCanUSCbo::~MFCanUSCbo()
//DS{
//DS}
//DS
//DS//******************************************************************************
//DSconst BFSession &
//DSMFCanUSCbo::getSession() const
//DS{
//DS  return userSession_;
//DS}
//DS
//DS//******************************************************************************
//DSBFSession &
//DSMFCanUSCbo::getSession()
//DS{
//DS  return userSession_;
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCGlobalSession &
//DSMFCanUSCbo::getGlobalSession() const
//DS{
//DS   return dynamic_cast<const DSTCGlobalSession &>(userSession_.getGlobalSession());
//DS}
//DS
//DS//******************************************************************************
//DSDSTCGlobalSession &
//DSMFCanUSCbo::getGlobalSession()
//DS{
//DS   return dynamic_cast<DSTCGlobalSession &>(userSession_.getGlobalSession());
//DS}
//DS
//DS//******************************************************************************
//DSconst DSTCUserSession &
//DSMFCanUSCbo::getUserSession() const
//DS{
//DS  return userSession_;
//DS}
//DS
//DS//******************************************************************************
//DSDSTCUserSession &
//DSMFCanUSCbo::getUserSession()
//DS{
//DS  return userSession_;
//DS}
//DS


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFCanCbo.cpp-arc  $
// 
//    Rev 1.17   May 04 2012 09:41:00   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.16   Oct 21 2009 10:46:58   purdyech
// LDAP Authorization Support
// 
//    Rev 1.15   Mar 12 2007 12:05:46   purdyech
// Implemented changes for "RecycleOnReceive" logic.
// 
//    Rev 1.14   Nov 14 2004 14:50:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Nov 09 2004 16:49:48   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.12   Nov 04 2004 17:38:04   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.11   May 09 2004 20:10:18   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.10   Apr 05 2004 17:29:44   FENGYONG
// PET944 FN01, release 56.1 NSCC Broker Matrix
// 
//    Rev 1.9   Feb 10 2004 16:35:22   VADEANUM
// PET 859 FN23 - ADL - added removeItemFromSubtList()
// 
//    Rev 1.8   Mar 21 2003 18:18:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:54:46   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:56:12   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:29:02   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   22 Mar 2002 15:28:08   PURDYECH
// Commented out the silly MFCanBFCbo stuff
// 
//    Rev 1.3   19 Mar 2002 13:22:00   PURDYECH
// Use #pragma once as an include guard
// Remove compile time "including..." message.
// 
//    Rev 1.2   Feb 25 2002 18:55:48   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.1   10 May 2001 11:38:08   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.0   03 May 2001 14:48:56   SMITHDAV
// Initial revision.
 * 
 */
