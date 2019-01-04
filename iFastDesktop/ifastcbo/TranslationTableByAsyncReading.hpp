#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//
//******************************************************************************
//
// ^FILE   : TranslationTableByAsyncReading.hpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : MiscInfoExternalInstitutionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\TranslationTable.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MiscInfoExternalInstitutionList : public TranslationTable
{
public:

   MiscInfoExternalInstitutionList( BFAbstractCBO &parent );
   virtual ~MiscInfoExternalInstitutionList();

   virtual void getSubstitutionList(DString& dstrSubstitutionList, bool bRequireViewDesc = false );
   virtual void getStrKey( DString &strKey, const BFData *data  = NULL);
   bool getDescription(const DString& miscCode, DString& miscDescription, bool& isOther);
   bool codeExists(const DString& miscCode);
   
   SEVERITY init();

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TranslationTableByAsyncReading.hpp-arc  $
// 