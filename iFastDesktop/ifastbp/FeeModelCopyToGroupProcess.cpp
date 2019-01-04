#include "stdafx.h"
#include "FeeModelCopyToGroupProcess.h"
#include "FeeModelProcessinclude.h"
#include "FeeModelProcess.hpp"
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"

#include <ifastcbo\feemodelcopytogroup.hpp>
#include <ifastcbo\feemodelcopytogrouplist.hpp>
#include <ifastcbo\feeModellist.hpp>
#include <ifastcbo\feeModel.hpp>

#include <ifastcbo\dstcworksession.hpp>

#include <bfproc\genericinterfacecontainer.hpp>

#include <bfcbo\validationcontrol.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEE_MODEL_COPY_TO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_MODEL_COPY_TO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_MODEL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeeModelCopyToGroupProcess > processCreator( CMD_BPROC_FEE_MODEL_COPY_TO );
namespace
{
   const I_CHAR *CLASSNAME = I_( "FeeModelCopyToGroupProcess" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFNumericFieldId FeeModelRecid;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFTextFieldId FeeModelSrc;
   extern CLASS_IMPORT const BFTextFieldId GroupDest;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCopyToGroupHeading;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEE_MODEL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_MODEL_COPY_TO_GROUP;
   extern IFASTBP_LINKAGE const BFContainerId GROUP_MODEL_CONTAINER_OF_FEE_MODEL;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

FeeModelCopyToGroupProcess::FeeModelCopyToGroupProcess(GenericInterfaceContainer* pGIC,
                                                       GenericInterface* pGIParent, 
                                                       const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand)
, _feeModelCode(NULL_STRING)
, _feeModelRecid(NULL_STRING)
, _feeModelDesc(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FEE_MODEL_LIST, true, BF::NullContainerId, true, I_("FeeModel") );
   addContainer( IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP, true, IFASTBP_PROC::FEE_MODEL_LIST, true, I_("FeeModelCopyTo") );

   addFieldDetails( ifds::FeeModelCopyToGroupHeading, IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FeeModelSrc, IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP );
   addFieldDetails( ifds::GroupDest, IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP );
}

//******************************************************************************
FeeModelCopyToGroupProcess::~FeeModelCopyToGroupProcess(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY FeeModelCopyToGroupProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter (I_("FeeModelCode"), _feeModelCode);
      getParameter (I_("FeeModelRecid"), _feeModelRecid);
      getParameter (I_("FeeModelDesc"), _feeModelDesc);
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

//******************************************************************************
E_COMMANDRETURN FeeModelCopyToGroupProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_FEE_MODEL_COPY_TO, PROC_NO_TYPE, true, &_rpChildGI );
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

//******************************************************************************
bool FeeModelCopyToGroupProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   bool bRtn = false;
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
bool FeeModelCopyToGroupProcess::doModelessChildComplete( const Command &cmd )
{
   DString dslCommandKey;
   dslCommandKey = cmd.getKey();
   if( dslCommandKey == CMD_GUI_FEE_MODEL_COPY_TO )
      return(true);  
   else
      return(false); 
}

//******************************************************************************
void *FeeModelCopyToGroupProcess::getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if ( IFASTBP_PROC::FEE_MODEL_LIST == idContainer )
      {
         if (dstcWorkSession)
         {
            FeeModelList *pFeeModelList = nullptr;
            dstcWorkSession->getFeeModelList( pFeeModelList, idDataGroup);

            if (pFeeModelList)
            {
               ptr = pFeeModelList;
            }
         }
      }
      else if( IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP == idContainer )
      {
         FeeModel *pFeeModel = nullptr;
         BFAbstractCBO* pCBOList =  const_cast<FeeModelCopyToGroupProcess*>(this)->getCBOItem(IFASTBP_PROC::FEE_MODEL_LIST, idDataGroup);
         pFeeModel = dynamic_cast<FeeModel*>(pCBOList);

         FeeModelCopyToGroupList* pFeeModelCopyToGroupList = nullptr;

         if (pFeeModel)
         {
            // create a cbo list to store 'copy to a new group info'
            pFeeModel->getFeeModelCopyToGroupList(pFeeModelCopyToGroupList,NULL_STRING,idDataGroup, true);

            if (pFeeModelCopyToGroupList != NULL)
            {
               pFeeModelCopyToGroupList->setField(ifds::FeeModelCode,_feeModelCode, idDataGroup,false,false,false);
               pFeeModelCopyToGroupList->setField(ifds::FeeModelRecid,_feeModelRecid, idDataGroup,false,false,false);
               pFeeModelCopyToGroupList->setField(ifds::FeeModelDesc, _feeModelDesc, idDataGroup,false,false,false);
            }
         }

         assert(pFeeModelCopyToGroupList!=nullptr);

         ptr = pFeeModelCopyToGroupList;
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
// TODO  If severity > warning, throw error returned from above
   return(ptr);
}

//******************************************************************************
bool FeeModelCopyToGroupProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOOK );
   SEVERITY sevReturn = NO_CONDITION;

   const BFDataGroupId idWorkingDataGroupId = getDataGroupId();

   FeeModelList* pFeeModelList = dynamic_cast<FeeModelList*>(getCBOList(IFASTBP_PROC::FEE_MODEL_LIST, idWorkingDataGroupId));
   BFObjIter iterSourceFee(*pFeeModelList, idWorkingDataGroupId);

   iterSourceFee.begin();

   while(!iterSourceFee.end())
   {
      // if there is a child object which keep 'copy to a new group' information,
      // these objects should be moved from a child level of each of fee model record
      // to be a new fee model record which has specific attributes
      FeeModel* pFeeModel = dynamic_cast<FeeModel*>(iterSourceFee.getObject());
      FeeModelCopyToGroupList* pCopyableList = nullptr;

      if (pFeeModel && pFeeModel->getFeeModelCopyToGroupList(pCopyableList,NULL_STRING,idWorkingDataGroupId,false) <= WARNING && 
         pCopyableList)
      {
         sevReturn = pCopyableList->validateAll( idWorkingDataGroupId, 0 );

         if (sevReturn > WARNING) break;

         pFeeModelList->copyFeeModelToNewGroup(pCopyableList, pFeeModelList, idWorkingDataGroupId);
         pFeeModel->removeFeeModelCopyToGroupList(idWorkingDataGroupId);
      }

      ++iterSourceFee;
   }

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/FeeModelCopyToGroupProcess.cpp-arc  $
// 
