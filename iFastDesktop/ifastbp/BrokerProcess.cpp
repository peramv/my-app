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
// ^FILE   : BrokerProcess.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 18, 2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerProcess
//    This class manages the Broker information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "brokerprocess.hpp"
#include "brokerprocessincludes.h"
#include <ifastcbo\brokerlist.hpp>
#include <ifastcbo\fundbrokerlist.hpp>
#include <ifastcbo\familycodelist.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BROKER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerProcess > processCreator(CMD_BPROC_BROKER);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                     = I_("BrokerProcess");
   const I_CHAR * const PERFORMSEARCH                 = I_("performSearch");
   const I_CHAR * const SEARCH_USING_FUND_BROKER_CODE = I_( "0" );
   const I_CHAR * const SEARCH_USING_FUND_BROKER_NAME = I_( "1" );
   const I_CHAR * const SEARCH_USING_FAMILY_CODE      = I_( "0" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;

   extern const long ERR_BROKER_LIST_EMPTY;
   extern const long ERR_BROKER_NAME_EMPTY;

   extern const long ERR_FUND_BROKER_CODE_EMPTY;
   extern const long ERR_FUND_BROKER_NAME_EMPTY;
   extern const long ERR_FUND_BROKER_NAME_NOT_EXISTING;

   extern const long ERR_FAMILY_CODE_EMPTY;
   extern const long ERR_FAMILY_CODE_OR_NAME_NOT_EXISTING;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundBrokerCode;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFTextFieldId Remarks1;
   extern CLASS_IMPORT const BFTextFieldId FamilyCode;
   extern CLASS_IMPORT const BFTextFieldId FamilyName;
   extern CLASS_IMPORT const BFTextFieldId FamilyType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

BrokerProcess::BrokerProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
_rpChildGI(0), 
_pBrokerList(NULL),
_pFundBrokerList(NULL),
_pFamilyCodeList(NULL),
_dstrCaller(NULL_STRING),
_dstrSearchCodeParameter(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::BROKER_LIST, true);
   addContainer(IFASTBP_PROC::FUND_BROKER_LIST, true);
   addContainer(IFASTBP_PROC::FAMILY_CODE_LIST, true);

   addFieldDetails(ifds::BrokerCode, IFASTBP_PROC::BROKER_LIST);
   addFieldDetails(ifds::BrokerName, IFASTBP_PROC::BROKER_LIST);
   addFieldDetails(ifds::AddrLine1,  IFASTBP_PROC::BROKER_LIST);
   addFieldDetails(ifds::PayInstrComm, IFASTBP_PROC::BROKER_LIST);
   addFieldDetails(ifds::PayInstrTrailer, IFASTBP_PROC::BROKER_LIST);
   addFieldDetails(ifds::NSCCCompliant, IFASTBP_PROC::BROKER_LIST);

   addFieldDetails(ifds::FundBrokerCode, IFASTBP_PROC::FUND_BROKER_LIST);
   addFieldDetails(ifds::Name, IFASTBP_PROC::FUND_BROKER_LIST);
   addFieldDetails(ifds::FirstName, IFASTBP_PROC::FUND_BROKER_LIST);
   addFieldDetails(ifds::Remarks1, IFASTBP_PROC::FUND_BROKER_LIST);

   addFieldDetails(ifds::FamilyCode, IFASTBP_PROC::FAMILY_CODE_LIST);
   addFieldDetails(ifds::FamilyType, IFASTBP_PROC::FAMILY_CODE_LIST);
   addFieldDetails(ifds::FamilyName, IFASTBP_PROC::FAMILY_CODE_LIST);
   addFieldDetails(ifds::EffectiveDate, IFASTBP_PROC::FAMILY_CODE_LIST);
   addFieldDetails(ifds::StopDate, IFASTBP_PROC::FAMILY_CODE_LIST);   
}

//******************************************************************************
BrokerProcess::~BrokerProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   
   if( _dstrCaller == I_("AggregatedOrders") )
   {
      if (_pFundBrokerList)
      {
         delete _pFundBrokerList;
         _pFundBrokerList = NULL;
      }
      setContainer(IFASTBP_PROC::FUND_BROKER_LIST, NULL );      
   }
   else if(_dstrCaller == I_("ShrFamily"))
   {
      if(_pFamilyCodeList)
      {
         delete _pFamilyCodeList;
         _pFamilyCodeList = NULL;
      }
      setContainer(IFASTBP_PROC::FAMILY_CODE_LIST, NULL );      
   }
   else
   {
      if (_pBrokerList)
      {
         delete _pBrokerList;
         _pBrokerList = NULL;
      }
   }
}

//******************************************************************************
SEVERITY BrokerProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);

   if(_dstrCaller == I_("ShrFamily"))
   {
      getParameter(I_("FamilyCodeSearchParam"),_dstrSearchCodeParameter);
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool BrokerProcess::doRefresh(GenericInterface *rpGICaller, 
                              const I_CHAR *szOriginalCommand)
{
   return false;
}

//******************************************************************************
SEVERITY BrokerProcess::performSearch(GenericInterface *rpGICaller, 
                                      const BFContainerId& idSearch, 
                                      E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH);
   
   const BFDataGroupId& idDataGroup = getDataGroupId();

   try
   {
      switch( eSearchAction )
      {
         case SEARCH_START:
         {
            if( idSearch == IFASTBP_PROC::FUND_BROKER_LIST )
            {
               DString fundBrokerCode, fundBrokerName;
               getParameter(I_("FundBrokerCode"), fundBrokerCode);
               getParameter(I_("FundBrokerName"), fundBrokerName);
         
               if ( (fundBrokerCode != NULL_STRING) || (fundBrokerName != NULL_STRING) )
               {
                  setContainer(IFASTBP_PROC::FUND_BROKER_LIST, NULL );
                  if ( _pFundBrokerList != NULL )
                  {
                     delete _pFundBrokerList;
                     _pFundBrokerList = NULL;
                  }
                  _pFundBrokerList = new FundBrokerList( *getBFWorkSession() );
                  
                  if ( _pFundBrokerList->init (fundBrokerCode, fundBrokerName, idDataGroup, I_("N"), NULL_STRING ) <= WARNING )
                  {
                     BFObjIter iter( *_pFundBrokerList, idDataGroup );
   
                     if( !(iter.getNumberOfItemsInList() > 0) )
                     {
                        ADDCONDITIONFROMFILE ( CND::ERR_FUND_BROKER_NAME_NOT_EXISTING );
                     }
                     else
                     {
                        setContainer(IFASTBP_PROC::FUND_BROKER_LIST, _pFundBrokerList);
                     }
                  }
                  else
                  {
                     setContainer(IFASTBP_PROC::FUND_BROKER_LIST, NULL );
                  }           
               }   // end fundbrokercode != NULL_STRING
               else 
               {
                  DString dstrSearchUsing;
                  getParameter(I_("FundBrokerSearchUsing"), dstrSearchUsing);
                  if( dstrSearchUsing == SEARCH_USING_FUND_BROKER_CODE )
                  {
                     ADDCONDITIONFROMFILE(CND::ERR_FUND_BROKER_CODE_EMPTY);
                  }
                  else if( dstrSearchUsing == SEARCH_USING_FUND_BROKER_NAME )
                  {
                     ADDCONDITIONFROMFILE(CND::ERR_FUND_BROKER_NAME_EMPTY);
                  }
               }
            }   // end fund broker list - search start
            else if( idSearch == IFASTBP_PROC::BROKER_LIST )
            {
               DString brokerName;
               getParameter(I_("BrokerName"), brokerName);
               if (brokerName != NULL_STRING)
               {
                  if (_pBrokerList != NULL)
                  {
                     delete _pBrokerList;
                     _pBrokerList = NULL;
                  }
                  _pBrokerList = new BrokerList(*getBFWorkSession());
                  if (_pBrokerList->init(NULL_STRING, brokerName, I_("S"), I_("N"), NULL_STRING, false ) <= WARNING)
                  {
                     BFObjIter iter(*_pBrokerList, getDataGroupId());

                     if (iter.getNumberOfItemsInList() > 0)
                     {
                        setContainer(IFASTBP_PROC::BROKER_LIST, _pBrokerList);
                     }
                     else
                     {
                        ADDCONDITIONFROMFILE(CND::ERR_BROKER_LIST_EMPTY);
                     }
                  }
               }     // end brokername != NULL_STRING
               else
               {
                  ADDCONDITIONFROMFILE(CND::ERR_BROKER_NAME_EMPTY);
               }
            } // end broker list - search start
            else if( idSearch == IFASTBP_PROC::FAMILY_CODE_LIST )
            {
               getParameter(I_("FamilyCodeSearchUsing"), _dstrSearchCodeParameter);
               if(!_dstrSearchCodeParameter.empty())
               {
                  if(_pFamilyCodeList)
                  {
                     setContainer(IFASTBP_PROC::FAMILY_CODE_LIST, NULL);
                     delete _pFamilyCodeList;
                     _pFamilyCodeList = NULL;
                  }

                  _pFamilyCodeList = new FamilyCodeList(*getBFWorkSession());

                  DString strSearchParam;

                  if(_dstrSearchCodeParameter == SEARCH_USING_FAMILY_CODE)
                  {
                     getParameter(I_("FamilyCode"), strSearchParam);

                     _pFamilyCodeList->init(strSearchParam, NULL_STRING, I_("N"), getDataGroupId());

                  }

                  // search using ?
                  if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
                  {
                     BFObjIter iter(*_pFamilyCodeList, getDataGroupId());

                     if (iter.getNumberOfItemsInList() > 0)
                     {
                        setContainer(IFASTBP_PROC::FAMILY_CODE_LIST, _pFamilyCodeList);
                     }
                     else
                     {
                        // some error on business process level for family code
                        ADDCONDITIONFROMFILE(CND::ERR_FAMILY_CODE_OR_NAME_NOT_EXISTING);
                     }
                  }
               }
            }
         }  //  end case SEARCH_START
         break;

         case SEARCH_NEXT_BLOCK:
         {
            if( idSearch == IFASTBP_PROC::FUND_BROKER_LIST )
            {
               _pFundBrokerList->getMore();
            }
            else if( idSearch == IFASTBP_PROC::BROKER_LIST )
            {
               _pBrokerList->getMore();
            }
            else if( idSearch == IFASTBP_PROC::FAMILY_CODE_LIST )
            {
               _pFamilyCodeList->getMore();
            }
         } // end case SEARCH_NEXT_BLOCK:
         break;

         default:
            break;
      }  // end switch case
      
   }  // end try
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN BrokerProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
      //setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      rtn = invokeCommand(this, CMD_GUI_BROKER, getProcessType(), 
         isModal(), &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool BrokerProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_BROKER;
}

//******************************************************************************
void BrokerProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   if (bSuccessFlag)
   {
      BFContainerId idContainer = BF::NullContainerId;
      BFFieldId idField = ifds::NullFieldId;
      
      if( _dstrCaller == I_("AggregatedOrders") )
      {
         idContainer = IFASTBP_PROC::FUND_BROKER_LIST; 
         idField = ifds::FundBrokerCode;  
      }
      else if(_dstrCaller == I_("ShrFamily"))
      {
         idContainer = IFASTBP_PROC::FAMILY_CODE_LIST; 
         idField = ifds::FamilyCode;
      }
      else
      {
         idContainer = IFASTBP_PROC::BROKER_LIST;  
         idField = ifds::BrokerCode;        
      }
      
      DString brokerCode;

      if (getNumberOfItemsInList(rpGICaller, idContainer) > 0)
      {
         getField(rpGICaller, idContainer, idField, brokerCode);
         if(_dstrCaller == I_("ShrFamily"))
         {
            setParameter(I_("FamilyCode"), brokerCode);
         }
         else
         {
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
         }
      }
   } // end if bSuccessFlag
}

//***********************************************************************************
bool BrokerProcess::doMoreRecordsExist(GenericInterface *rpGICaller,
                                       const BFContainerId& idSearch)
{
   if( idSearch == IFASTBP_PROC::BROKER_LIST )
   {
      return ( _pBrokerList == NULL ? false : _pBrokerList->doMoreRecordsExist() );
   }
   else if( idSearch == IFASTBP_PROC::FUND_BROKER_LIST )
   {
      return ( _pFundBrokerList == NULL ? false : _pFundBrokerList->doMoreRecordsExist() );
   }
   else if( idSearch == IFASTBP_PROC::FAMILY_CODE_LIST )
   {
      return ( _pFamilyCodeList == NULL ? false : _pFamilyCodeList->doMoreRecordsExist() );
   }

   return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerProcess.cpp-arc  $
 * 
 *    Rev 1.21   Dec 09 2011 11:30:34   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.20   Nov 09 2011 19:25:06   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.19   Nov 08 2011 11:58:10   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.18   Apr 07 2009 01:06:42   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.17   Apr 06 2009 04:17:10   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.16   Mar 26 2009 01:39:40   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - correct code review rev1.5.
 * 
 *    Rev 1.14   Mar 25 2009 07:25:14   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
 * 
 *    Rev 1.13   Jul 06 2005 10:55:30   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.12   Jul 10 2003 22:19:32   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.11   Mar 21 2003 17:37:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Sep 16 2002 16:06:56   KOVACSRO
 * condition split fix.
 * 
 *    Rev 1.8   Sep 04 2002 15:45:44   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.7   Aug 29 2002 16:42:48   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.6   Aug 29 2002 12:54:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:24:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   27 Mar 2002 19:54:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   03 May 2001 14:05:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   15 Dec 2000 12:43:22   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.1   Mar 06 2000 16:40:28   DT24433
 * removed substitute lists
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Jan 24 2000 18:11:32   POPESCUS
// some fixes
// 
//    Rev 1.1   Jan 22 2000 15:42:12   WINNIE
// To get search work
 
*/ 
