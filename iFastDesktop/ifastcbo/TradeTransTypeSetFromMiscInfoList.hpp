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
// ^FILE   : TradeTransTypeSetFromMiscInfoList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 04 April 2013
//
// ^CLASS    : TradeTransTypeSetFromMiscInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the Network Config Details
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

class NetworkConfigDetail;

class IFASTCBO_LINKAGE TradeTransTypeSetFromMiscInfoList : public MFCanBFCbo, private boost::noncopyable
{

public:

   TradeTransTypeSetFromMiscInfoList( BFAbstractCBO &parent );
   virtual ~TradeTransTypeSetFromMiscInfoList( );
   SEVERITY init ( const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING );
   void getSysLevelTransTypeList( DString& dstrTransList ); 
   void setFilteredString( const DString& dstrFilteredList);
   void getFilteredString( DString& dstrFilteredList);

protected:

	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	void getStrKey ( DString& strKey, const BFData* data );
    void buildKey( DString& dstrKeyOut, const DString& dstrNetworkID, 
                   const DString& dstrNetworkConfigType );

private:
   
    void  buildTransTypeList( ) ;

private:
   BFData   m_requestData; 
   DString  m_dstrTransTypeList;
   DString  m_filteredList;

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeTransTypeSetFromMiscInfoList.hpp-arc  $  

*/