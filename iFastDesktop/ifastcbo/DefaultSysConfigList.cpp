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
// ^FILE   : DefaultSysConfigList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfigList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for a  field from DefaultConfig table
//
//******************************************************************************
#include "stdafx.h"
#include "DefaultSysConfigList.hpp"
#include "DefaultSysConfig.hpp"
#include <ifastdataimpl\dse_dstc0454_req.hpp>
#include <ifastdataimpl\dse_dstc0454_vw.hpp>
#include <ifastdataimpl\dse_dstc0454_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEFAULT_SYSTEM_CONFIG; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("DefaultSysConfigList");
   const I_CHAR * const FIELD_NAME             = I_("FldName");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FldName;
   extern CLASS_IMPORT const BFTextFieldId DefValue;
}

//******************************************************************************
DefaultSysConfigList::DefaultSysConfigList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0454_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
DefaultSysConfigList::~DefaultSysConfigList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY DefaultSysConfigList::init (const DString& dstrFldName,
									 const DString& dstrTrack,
									 const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData *receivedData = new BFData (ifds::DSTC0454_VW);
   DString mgmtCoIdOut;
   m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   m_requestData.setElementValue (ifds::Track, dstrTrack);
   m_requestData.setElementValue (ifds::Activity, dstrPageName);
   m_requestData.setElementValue( ifds::FldName,  dstrFldName );
   ReceiveData ( DSTC_REQUEST::DEFAULT_SYSTEM_CONFIG, 
                 m_requestData, 
                 *receivedData, 
                 DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DefaultSysConfigList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DefaultSysConfig * pDefaultSysConfig = new DefaultSysConfig( *this );
   pDefaultSysConfig->init( data );
   pObjOut = pDefaultSysConfig;       
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void DefaultSysConfigList::buildKey (const BFFieldId& idField, DString &strKeyOut)
{
	strKeyOut = idField.getName();
}
//******************************************************************************
void DefaultSysConfigList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      strKey  = data->getElementValue( FIELD_NAME );
      strKey.strip() ;
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}
//******************************************************************************
void DefaultSysConfigList::getFieldDefaultValue( const BFFieldId& idField , const BFDataGroupId& idDataGroup, DString& dstrDefValue, 
												 bool& bfound, bool bformattedReturn )
{
	dstrDefValue = NULL_STRING;
	assert(	idField != ifds::NullFieldId ); 	
	DString dstrKey;
	DefaultSysConfig* pDefaultSysConfig = NULL;
	//call the default config matrix to return the default
	bfound = getDefaultSysConfig( idField, idDataGroup, pDefaultSysConfig );
	if(bfound)
		pDefaultSysConfig->getField( ifds::DefValue, dstrDefValue, idDataGroup, bformattedReturn  );
}
//******************************************************************************
bool DefaultSysConfigList::getDefaultSysConfig(const BFFieldId& idField, const BFDataGroupId& idDataGroup, DefaultSysConfig *&pDefaultSysConfig )
{
	assert(	idField != ifds::NullFieldId );
	DString dstrKey;
	pDefaultSysConfig = NULL;
	BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	buildKey (idField, dstrKey );
	if (iter.positionByKey (dstrKey))
		pDefaultSysConfig = dynamic_cast<DefaultSysConfig *>(iter.getObject());
	return ( pDefaultSysConfig ? true : false );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigList.cpp-arc  $		 

*/