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
//******************************************************************************
//
// ^FILE   : ShrFamilyProcess.cpp
// ^AUTHOR : 
// ^DATE   : 09/01/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ShrFamilyProcess
//    This class manages the Shareholer Family information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "shrfamilyprocessincludes.h"
#include "shrfamilyprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\shrfamilylist.hpp>
#include <ifastcbo\shrfamily.hpp>
#include <ifastcbo\familycodelist.hpp>
#include <ifastcbo\familycode.hpp>

#include <ifastcbo\shareholder.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SHR_FAMILY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_FAMILY;

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\genericinterface.hpp>

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShrFamilyProcess > processCreator( CMD_BPROC_SHR_FAMILY );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ShrFamilyProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace SHRFAMILYLIST
{
   const I_CHAR * const SHR_FAMILY  = I_( "FamilyCodeExist" );
   const I_CHAR * const SHR_NUM     = I_( "ShareholderNum" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId ShrFamilyStatus;
   extern CLASS_IMPORT const BFDecimalFieldId ShrFamilyRid;
   extern CLASS_IMPORT const BFDecimalFieldId FamilyRId;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHR_FAMILY;
   extern CLASS_IMPORT I_CHAR * const SYS_FAMILY;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319ShrFamilyProcess::ShrFamilyProcess() : 
ShrFamilyProcess::ShrFamilyProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI (NULL)
, _pFamilyCodeList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::SHAREHOLDER,        false,   BF::NullContainerId, false, I_("Shareholder") );
   addContainer( IFASTBP_PROC::FAMILY_LIST,        true,    IFASTBP_PROC::SHAREHOLDER, true, I_("FamilyCodeExist") );
   addContainer( IFASTBP_PROC::FAMILY_CODE_LIST,   true,    BF::NullContainerId, false, I_("SystemFamilyCode") );

   addFieldDetails( ifds::ShrNum,            IFASTBP_PROC::SHAREHOLDER );

   addFieldDetails( ifds::FamilyType,        IFASTBP_PROC::FAMILY_LIST );
   addFieldDetails( ifds::FamilyCode,        IFASTBP_PROC::FAMILY_LIST );
   addFieldDetails( ifds::FamilyName,        IFASTBP_PROC::FAMILY_LIST );
   addFieldDetails( ifds::Role,              IFASTBP_PROC::FAMILY_LIST );
   addFieldDetails( ifds::ShrFamilyRid,      IFASTBP_PROC::FAMILY_LIST );

   addFieldDetails (ifds::FamilyRId,         IFASTBP_PROC::FAMILY_CODE_LIST);
}

//******************************************************************************
ShrFamilyProcess::~ShrFamilyProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pFamilyCodeList)
   {
      delete _pFamilyCodeList;
      _pFamilyCodeList = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY ShrFamilyProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter( SHRFAMILYLIST::SHR_NUM, _strShrNum );
   getParameter( SHRFAMILYLIST::ACCOUNT_NUM, s_AcctNum );

   SEVERITY sevRtn=NO_CONDITION;
   Shareholder * pShareholder = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( dstcWorkSession->getShareholder( getDataGroupId(), _strShrNum, pShareholder, true ) 
       <= WARNING && pShareholder )
   {
      setContainer( IFASTBP_PROC::SHAREHOLDER, pShareholder );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool ShrFamilyProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_SHR_FAMILY);
}

//******************************************************************************
bool ShrFamilyProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   DString  strShrNum;
   bool bRtn = false;

   try
   {
      //assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      getParameter( SHRFAMILYLIST::SHR_NUM, strShrNum );
      if( strShrNum != _strShrNum )
      {
         _strShrNum = strShrNum;
         setContainer( IFASTBP_PROC::SHAREHOLDER, NULL );

         if( isValidModelessInterface( _rpChildGI ) )
         {  // Only if child still exists
            bRtn = _rpChildGI->refresh( this, NULL );
         }
      }

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN ShrFamilyProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter (SHRFAMILYLIST::SHR_NUM, _strShrNum);
   setParameter (SHRFAMILYLIST::ACCOUNT_NUM, s_AcctNum);

   try
   {
      rtn = invokeCommand( this, CMD_GUI_SHR_FAMILY, getProcessType(), isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
bool ShrFamilyProcess::doOk( GenericInterface *rpGICaller )
{
   Shareholder *pShareholder = NULL;
   DString familyFlag = I_( "N" );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (dstcWorkSession->getShareholder (idDataGroup, _strShrNum, pShareholder) <= WARNING)
   {
      ShrFamilyList *pShrFamilyList;

      if( pShareholder->getShrFamilyList( pShrFamilyList, idDataGroup ) <= WARNING )
      {
         BFObjIter iter( *pShrFamilyList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               familyFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         pShareholder->setField( ifds::FamilyCodeExist, familyFlag, idDataGroup, false );
      }
   }

   return true;
}

//******************************************************************************
void *ShrFamilyProcess::getPtrForContainer( const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::SHAREHOLDER == idContainer)
      {
         {
            Shareholder *pShareholder;

            if (dstcWorkSession->getShareholder (getDataGroupId(), _strShrNum, pShareholder) <= WARNING && 
                pShareholder)
            {
               ptr = pShareholder;
            }
         }
      }
      else if (IFASTBP_PROC::FAMILY_LIST == idContainer)
      {
         {
            Shareholder *pShareholder (NULL);
            ShrFamilyList *pShrFamilyList (NULL);

            if (dstcWorkSession->getShareholder (idDataGroup, _strShrNum, pShareholder) <= WARNING)
            {
               if (pShareholder->getShrFamilyList (pShrFamilyList, idDataGroup) <= WARNING)
               {
                  ptr = pShrFamilyList;
               }
            }
         }
      }
      else if (IFASTBP_PROC::FAMILY_CODE_LIST == idContainer)
      {
         ShrFamily *pShrFamily = 
            dynamic_cast <ShrFamily*> (getCBOItem (IFASTBP_PROC::FAMILY_LIST, idDataGroup));

         if (pShrFamily)
         {
            if (_pFamilyCodeList)
            {
               delete _pFamilyCodeList;
               _pFamilyCodeList = NULL;
            }
            _pFamilyCodeList = new FamilyCodeList (*dstcWorkSession);
            DString dstrFamilyCode;

            pShrFamily->getField (ifds::FamilyCode, dstrFamilyCode, idDataGroup, false);

            if (_pFamilyCodeList->init (dstrFamilyCode, NULL, I_("Y"), idDataGroup) <= WARNING)
            {
               ptr = _pFamilyCodeList;
            }
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return (ptr);
}

/******************************************************************************
bool ShrFamilyProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || _pRemarksList == NULL ) ? 
   false : _pRemarksList->doMoreRecordsExist();
}

*/

//******************************************************************************
SEVERITY ShrFamilyProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                    HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), 
      dstrShrFamilyRecord,
      dstrFamilyRecord,
      dstrFamilyCode,
      dstrFamilyType,
      dstrShrNum;

   getField ( this, IFASTBP_PROC::FAMILY_CODE_LIST, ifds::FamilyRId, dstrFamilyRecord, false );
   getField ( this, IFASTBP_PROC::FAMILY_LIST, ifds::FamilyCode, dstrFamilyCode, false );
   addIDITagValue (keyStringIDI, I_("FamilyCode"), dstrFamilyCode);
   HistoricalElement historicalElementFamily( dstrFamilyRecord, AUDITTYPE::SYS_FAMILY, keyStringIDI );
   vectorHistorical.push_back( historicalElementFamily );

   keyStringIDI = NULL_STRING;

   getField( this, IFASTBP_PROC::FAMILY_LIST, ifds::ShrFamilyRid, dstrShrFamilyRecord, false );
   getField( this, IFASTBP_PROC::SHAREHOLDER, ifds::ShrNum, dstrShrNum, false );
   getField( this, IFASTBP_PROC::FAMILY_LIST, ifds::FamilyType, dstrFamilyType, false );
   addIDITagValue( keyStringIDI, I_("FamilyCode"), dstrFamilyCode );
   addIDITagValue( keyStringIDI, I_("Prkey"), dstrShrNum );
   addIDITagValue( keyStringIDI, I_("FamilyType"), dstrFamilyType );
   HistoricalElement historicalElementShrFamily( dstrShrFamilyRecord, AUDITTYPE::SHR_FAMILY, keyStringIDI );
   vectorHistorical.push_back( historicalElementShrFamily );

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFamilyProcess.cpp-arc  $
// 
//    Rev 1.15   Mar 20 2012 18:54:02   popescu
// Incident 2889121 - shareholder family screen freeze
// 
//    Rev 1.14   Mar 20 2012 18:35:48   popescu
// Incident 2889121 - shareholder family screen freeze
// 
//    Rev 1.13   Dec 09 2011 11:31:50   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.12   Nov 21 2011 12:11:40   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.11   Nov 17 2011 19:14:52   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.10   Nov 16 2011 19:19:40   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.9   Nov 15 2011 18:38:32   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.8   Nov 09 2011 19:34:30   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.7   Nov 08 2011 11:54:46   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.6   Mar 21 2003 17:48:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Mar 03 2003 11:10:06   sanchez
// Added a break statements to match the case statements in
// void *ShrFamilyProcess::getPtrForContainer()
// 
//    Rev 1.4   Jan 15 2003 16:48:06   sanchez
// added const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" ) to namespace SHRFAMILYLIST
// 
//    Rev 1.3   Jan 14 2003 17:33:04   sanchez
// added //******************************************************************************
// //              Revision Control Entries
// //******************************************************************************
// /* $Log
//  * /
 */