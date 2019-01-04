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
//    Copyright 2005, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCWhereUseTrxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 6, 2005
//
// ^CLASS    : DSTCWhereUseTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCWhereUseTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0331_req.hpp>
#include <ifastdataimpl\dse_dstc0331_vw.hpp>
#include <ifastdataimpl\dse_dstc0331_reqrepeat_record.hpp>
#include "whereused.hpp"
#include "whereusedlist.hpp"
#include "Entity.hpp"



namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest WHEREUSE_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCWhereUseTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId rxCompCode;
//   extern CLASS_IMPORT const BFNumericFieldId Settled;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}


//******************************************************************************
void DSTCWhereUseTrxnBuilder::buildTrxnKey( DString& strKey, Entity* pEntity )
{
   addIDITagValue( strKey, TRXNTAG::WHEREUSEDTAG, TRXNTAG::WHEREUSEDTAG );
   DString entityId;
   pEntity->getEntityId( entityId );
   entityId.stripLeading( '0' );
   entityId.strip();
   addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, entityId );
}
//******************************************************************************
SEVERITY DSTCWhereUseTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;
	Entity* entity = dynamic_cast<Entity*>(pObj);

	if( entity != NULL )
	{
		WhereUsedList* pWhereUsedList = NULL;
		entity->getWhereUsedList ( pWhereUsedList, BF::HOST, false, false );
   
		DString entityId;
		entity->getEntityId( entityId );
		entityId.stripLeading( '0' );
		entityId.strip();

		if( pWhereUsedList != NULL )
		{
			DString keyTypes;   
			addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

			DSTCListTrxnBuilder<WhereUsed*> WhereUsedListTrxnBuilder;
			DString key = I_("WhereUsed") + entityId;

			TRXNINFO WhereUsedTrxnInfo( key , 																		
										DSTC_REQUEST::WHEREUSE_LIST_UPDATE,
									    ifds::DSTC0331_REQ,
										ifds::DSTC0331_REQRepeat_Record,
										ifds::DSTC0331_VW);
			
			WhereUsedListTrxnBuilder.buildTransactions( workSession, 
		 												pTrCont, 
														pWhereUsedList, 
  														WhereUsedTrxnInfo,
														objActivity,
														keyTypes ); 
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCWhereUseTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Dec 02 2005 09:18:08   jankovii
// Incident #468333 - it was not possible to add 2 entites in All entites where use option.
// 
//    Rev 1.3   Nov 30 2005 09:34:52   popescu
// Incindent# 463650 - a dummy where used record was erroneous sent to back-end
// 
//    Rev 1.2   Nov 08 2005 16:18:50   jankovii
// PET1228 - replaced existing code with DSTCListTrxnBuilder support.
// 
//    Rev 1.1   May 03 2005 14:52:44   yingbaol
// Incident302278, desktop should not send dummy record to back end
// 
//    Rev 1.0   Mar 06 2005 15:37:30   yingbaol
// Initial revision.
//


* 
*/