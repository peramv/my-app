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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DefaultSysConfigDetailList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfigDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for all fields based on the DefConfigDetails table
//
//******************************************************************************
#include "stdafx.h"
#include "DefaultSysConfigDetailList.hpp"
#include "DefaultSysConfigDetail.hpp"
#include "DefaultSysConfigList.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0455_req.hpp>
#include <ifastdataimpl\dse_dstc0455_vw.hpp>
#include <ifastdataimpl\dse_dstc0455_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEFAULT_SYSTEM_CONFIG_DETAIL; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME           = I_("DefaultSysConfigDetailList");
   const I_CHAR * const KEY_FIELD1          = I_("KeyField1");
   const I_CHAR * const KEY_FIELD2          = I_("KeyField2");
   const I_CHAR * const KEY_FIELD3          = I_("KeyField3");
   const I_CHAR * const KEY_FIELD4          = I_("KeyField4");
   const I_CHAR * const KEY_FIELD5          = I_("KeyField5");
   const I_CHAR * const FIELD_NAME          = I_("FldName");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FldName;
   extern CLASS_IMPORT const BFTextFieldId DefValue;
   extern CLASS_IMPORT const BFTextFieldId StatCode;
}
namespace STATUS_CODE
{
 const I_CHAR * const ACTIVE		= I_("01");
 const I_CHAR * const INACTIVE		= I_("02");
}
//******************************************************************************
DefaultSysConfigDetailList::DefaultSysConfigDetailList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0455_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
DefaultSysConfigDetailList::~DefaultSysConfigDetailList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY DefaultSysConfigDetailList::init (const DString& dstrFldName,
									 const DString& dstrTrack,
									 const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData *receivedData = new BFData (ifds::DSTC0455_VW);
   DString mgmtCoIdOut;
   m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   m_requestData.setElementValue (ifds::Track, dstrTrack);
   m_requestData.setElementValue (ifds::Activity, dstrPageName);
   m_requestData.setElementValue( ifds::FldName,  dstrFldName );
   ReceiveData ( DSTC_REQUEST::DEFAULT_SYSTEM_CONFIG_DETAIL, 
                 m_requestData, 
                 *receivedData, 
                 DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DefaultSysConfigDetailList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DefaultSysConfigDetail * pDefaultSysConfigDetail = new DefaultSysConfigDetail( *this );
   pDefaultSysConfigDetail->init( data );
   pObjOut = pDefaultSysConfigDetail;       
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void DefaultSysConfigDetailList::buildKey (const DString& dstrFieldName,const DString& dstrKeyField1, const DString& dstrKeyField2,
										   const DString& dstrKeyField3, const DString& dstrKeyField4, const DString& dstrKeyField5,
										   DString &dstrKeyOut)
{	
	dstrKeyOut = NULL_STRING;
	dstrKeyOut = dstrFieldName + I_("$") + dstrKeyField1 + I_("$")  + dstrKeyField2 + I_("$")  + 
		         dstrKeyField3 + I_("$") + dstrKeyField4 + I_("$")  + dstrKeyField5 ;
}
//******************************************************************************
void  DefaultSysConfigDetailList::getStrKey ( DString& dstrKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstrFldName, dstrKeyField1, dstrKeyField2, dstrKeyField3, dstrKeyField4, dstrKeyField5;
      dstrFldName	= data->getElementValue( FIELD_NAME );
	  dstrKeyField1	= data->getElementValue( KEY_FIELD1 );
	  dstrKeyField2	= data->getElementValue( KEY_FIELD2 );
	  dstrKeyField3	= data->getElementValue( KEY_FIELD3 );
	  dstrKeyField4	= data->getElementValue( KEY_FIELD4 );
	  dstrKeyField5	= data->getElementValue( KEY_FIELD5 );

	  buildKey(dstrFldName.stripAll(), dstrKeyField1.stripAll(), dstrKeyField2.stripAll(), dstrKeyField3.stripAll(), 
			   dstrKeyField4.stripAll(), dstrKeyField5.stripAll(), dstrKey); 	
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL );
   }
}
//******************************************************************************
void DefaultSysConfigDetailList::getFieldDefaultValue( const BFFieldId& idField , const BFDataGroupId& idDataGroup, DString& dstrDefValue, 
													   bool bformattedReturn , const DString& dstrKeyField1, const DString& dstrKeyField2,
													   const DString& dstrKeyField3, const DString& dstrKeyField4, const DString& dstrKeyField5 ) 
{
	dstrDefValue = NULL_STRING;
	DefaultSysConfigList* pDefaultSysConfigList = NULL;
	DefaultSysConfigDetail* pDefaultSysConfigDetail = NULL;
	assert(	idField != ifds::NullFieldId ); 	
	DString dstrKey, dstrSysDefault, dstrMatrixDefault;
	bool bfound = false;
	bool bUseMatrixDefault = false;
	//call the sys level config as default 
	getMgmtCo().getDefaultSysConfigList(pDefaultSysConfigList);
	if( pDefaultSysConfigList )
	    pDefaultSysConfigList->getFieldDefaultValue(idField, idDataGroup, dstrSysDefault, bfound, false );  
    if( !bfound )	
		return;//if not in ConfigTable  then not in Configdetail level too..

	//call the config matrix details to return the customized default if avilable
	bfound = getDefaultSysConfigDetail( idField, idDataGroup, pDefaultSysConfigDetail,dstrKeyField1,
									    dstrKeyField2 , dstrKeyField3, dstrKeyField4, dstrKeyField5 );
	if(bfound)
	{
	  DString dstrStatCode;
	  pDefaultSysConfigDetail->getField( ifds::StatCode, dstrStatCode, idDataGroup, false );
      pDefaultSysConfigDetail->getField( ifds::DefValue, dstrMatrixDefault, idDataGroup, bformattedReturn  );
	  bUseMatrixDefault = dstrStatCode == STATUS_CODE::ACTIVE ? true : false ;
	}

	dstrDefValue =	bUseMatrixDefault ? dstrMatrixDefault : dstrSysDefault ; 
}
//******************************************************************************
bool DefaultSysConfigDetailList::getDefaultSysConfigDetail(const BFFieldId& idField,const BFDataGroupId& idDataGroup, DefaultSysConfigDetail *&pDefaultSysConfigDetail,
														   const DString& dstrKeyField1 /*= NULL_STRING*/, const DString& dstrKeyField2 /*= NULL_STRING*/, 
														   const DString& dstrKeyField3 /*= NULL_STRING*/, const DString& dstrKeyField4 /*= NULL_STRING*/, 
														   const DString& dstrKeyField5 /*= NULL_STRING*/ )
{
	assert(	idField != ifds::NullFieldId );
	DString dstrKey,dstrFieldName;
	dstrFieldName = idField.getName(); 
	pDefaultSysConfigDetail = NULL;
	BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	buildKey (dstrFieldName, dstrKeyField1, dstrKeyField2, dstrKeyField3, 
			  dstrKeyField4, dstrKeyField5, dstrKey );
	if (iter.positionByKey (dstrKey))
		pDefaultSysConfigDetail = dynamic_cast<DefaultSysConfigDetail *>(iter.getObject());
	return ( pDefaultSysConfigDetail ? true : false );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigDetailList.cpp-arc  $	  

*/