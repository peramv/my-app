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
// ^FILE   : DefaultSysConfigList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfigList
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

class DefaultSysConfig;

class IFASTCBO_LINKAGE DefaultSysConfigList : public MFCanBFCbo, private boost::noncopyable
{
public:

	DefaultSysConfigList( BFAbstractCBO &parent );
	virtual ~DefaultSysConfigList( void );
	SEVERITY init ( const DString& dstrFldName =	NULL_STRING,
					const DString& dstrTrack = I_("N"), 
					const DString& dstrPageName = NULL_STRING );
	void getFieldDefaultValue( const BFFieldId& idField , const BFDataGroupId& idDataGroup, DString& dstrDefValue, 
							   bool& bfound, bool bformattedReturn = false );
protected:	
	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	static void buildKey(const BFFieldId& idField, DString &strKeyOut);
	void getStrKey ( DString& strKey, const BFData* data );
	bool getDefaultSysConfig(const BFFieldId& idField, const BFDataGroupId& idDataGroup, DefaultSysConfig *&pDefaultSysConfig );
private:
   BFData   m_requestData; 
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigList.hpp-arc  $		  

*/