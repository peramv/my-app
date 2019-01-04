#pragma once

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
//
//******************************************************************************
//
// ^FILE   : GROUPLIST_HPP.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Octoble 19, 1999
//
// ^CLASS    : GROUPLIST
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

class IFASTCBO_LINKAGE GroupList : public MFCanBFCbo, private boost::noncopyable
{
public:
   GroupList( BFAbstractCBO &parent );

   virtual ~GroupList(void);

   SEVERITY init( const DString& dstrGropCode = NULL_STRING,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   virtual void getStrKey( DString &strKey, const BFData *data );
   void getGroupSubstList( DString &strList, bool bMakeUppercase);

   SEVERITY getField( const DString& strGroupCode, 
                      const BFFieldId& idField, 
                      DString& strValue, 
                      const BFDataGroupId& idDataGroup, 
                      bool formattedReturn=false );

   void buildKey(const DString& strGroup, DString &strKey);

private:
};

