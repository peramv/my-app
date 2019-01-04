#include "stdafx.h"
#include "valuevariationprocess.h"

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mfaccount.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_VALUE_VARIATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_VALUE_VARIATION;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ValueVariationProcess > processCreator( CMD_BPROC_VALUE_VARIATION );
namespace
{
   const I_CHAR *CLASSNAME = I_( "ValueVariationProcess" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId InitialDate;
   extern CLASS_IMPORT const BFDecimalFieldId InitialMarketValue;
   extern CLASS_IMPORT const BFDecimalFieldId NetTransAmt;
   extern CLASS_IMPORT const BFDateFieldId NetTransAmtAsOfDate;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId Name1;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCOUNT_GROUPING
{
	extern CLASS_IMPORT const long VALUE_VARIATION;
}

ValueVariationProcess::ValueVariationProcess(GenericInterfaceContainer* pGIC,      
                                             GenericInterface* pGIParent, 
                                             const Command& rCommand)
      :AbstractProcess(pGIC, pGIParent, rCommand)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer( IFASTBP_PROC::MFACCOUNT, false, BF::NullContainerId, true );

   addFieldDetails( ifds::InitialDate, IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::InitialMarketValue, IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::NetTransAmt, IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::NetTransAmtAsOfDate, IFASTBP_PROC::MFACCOUNT );

}
ValueVariationProcess::~ValueVariationProcess(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

SEVERITY ValueVariationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      DString dstrAccountNum;
      getParameter(I_("AccountNum"), dstrAccountNum);

      MFAccount *pMFAccount = NULL;
      
      dstcWorkSession-> getMFAccount ( 
         getDataGroupId(), dstrAccountNum, pMFAccount);

      setContainer( IFASTBP_PROC::MFACCOUNT, pMFAccount );
   } 
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch(...)
   {
       throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETHIGHESTSEVERITY();
}

E_COMMANDRETURN ValueVariationProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      DString dstrAccountNum, dstrName;
      BFAbstractCBO* cbo = getCBOItem(IFASTBP_PROC::MFACCOUNT, getDataGroupId());
      MFAccount *pMFAccount = dynamic_cast<MFAccount*>(cbo);
      pMFAccount->getField( ifds::AccountNum, dstrAccountNum, getDataGroupId() );
      pMFAccount->getAcctName(dstrName, getDataGroupId());

      DString caption = I_("Account ") + dstrAccountNum + I_("; ") + dstrName;
      setParameter(I_("caption"), caption);

      rtn = invokeCommand( this, CMD_GUI_VALUE_VARIATION, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

bool ValueVariationProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   bool bRtn = false;
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

bool ValueVariationProcess::doModelessChildComplete( const Command &cmd )
{
   DString dslCommandKey;
   dslCommandKey = cmd.getKey();
   if( dslCommandKey == CMD_GUI_VALUE_VARIATION )
      return(true);  
   else
      return(false); 
   
}

SEVERITY ValueVariationProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("doValidateAll") );

   BFAbstractCBO* cbo = getCBOItem(IFASTBP_PROC::MFACCOUNT, idDataGroup);
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(cbo);

   pMFAccount->validateAll( idDataGroup, ACCOUNT_GROUPING::VALUE_VARIATION);
  
   return GETCURRENTHIGHESTSEVERITY();
}