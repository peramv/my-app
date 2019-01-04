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
// ^CLASS DESCRIPTION :	Used to get the defualt values for multiple keys
//
//******************************************************************************
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
                              
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

typedef enum  
{
	MODE_INIT		   = 0x0001,
	MODE_MODIFY        = 0x0002,
	MODE_REBOOK        = 0x0004,
}MODE;

class FIELD_DEFAULT_RULE
{
   public: const BFFieldId		_FieldID;
		   const BFFieldId		_KeyFld1;
		   const BFFieldId		_KeyFld2;
		   const BFFieldId		_KeyFld3;
		   const BFFieldId		_KeyFld4;
		   const BFFieldId		_KeyFld5;
		   const long		    _Mode; //Type of applicable mode,can Be Init,Modify,Rebook
		   bool  getModAppl(long lCurrMode) const { return ( _Mode & lCurrMode ? true : false ); }
 };

class DefaultSysConfigDetail;

class IFASTCBO_LINKAGE DefaultSysConfigDetailList : public MFCanBFCbo, private boost::noncopyable
{
public:

   DefaultSysConfigDetailList( BFAbstractCBO &parent );
   virtual ~DefaultSysConfigDetailList( void );
   void getFieldDefaultValue  ( const BFFieldId& idField , const BFDataGroupId& idDataGroup, DString& dstrDefValue, 
								bool bformattedReturn = false, const DString& dstrKeyField1 = NULL_STRING, 
								const DString& dstrKeyField2 = NULL_STRING, const DString& dstrKeyField3 = NULL_STRING, 
								const DString& dstrKeyField4 = NULL_STRING, const DString& dstrKeyField5 = NULL_STRING ); 
	bool getDefaultSysConfigDetail(const BFFieldId& idField,const BFDataGroupId& idDataGroup, DefaultSysConfigDetail *&pDefaultSysConfigDetail,
									 const DString& dstrKeyField1 = NULL_STRING, const DString& dstrKeyField2 = NULL_STRING, 
									 const DString& dstrKeyField3 = NULL_STRING, const DString& dstrKeyField4 = NULL_STRING, 
									 const DString& dstrKeyField5 = NULL_STRING ); 	
   SEVERITY init ( const DString& dstrFldName =	NULL_STRING,
				   const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING );

protected:

	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	static void buildKey (const DString& dstrFieldName, const DString& dstrKeyField1, const DString& dstrKeyField2,
						  const DString& dstrKeyField3, const DString& dstrKeyField4, const DString& dstrKeyField5,
						  DString &dstrKeyOut);
	void getStrKey ( DString& strKey, const BFData* data );
	 
private:
   BFData   m_requestData; 
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigDetailList.hpp-arc  $  

*/