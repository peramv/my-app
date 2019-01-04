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
//    Copyright 2002 by International financial data service.
//
//
//******************************************************************************
//
// ^FILE   : TranslationTable.hpp
// ^AUTHOR : 
// ^DATE   :
//
// ^CLASS    : TranslationTable
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE TranslationTable : public MFCanBFCbo, private boost::noncopyable
{
public:

   TranslationTable( BFAbstractCBO &parent );
   virtual ~TranslationTable();
 
   SEVERITY init(const DString& dstrGroupCode, const DString& dstrTrack = I_("N"),
                                  const DString& dstrPageName = NULL_STRING  );

   SEVERITY getMore();

   virtual void getSubstitutionList(DString& dstrSubstitutionList, bool bRequireViewDesc = false );
   void getSubstitutionListByDescription(DString& dstrSubstitutionList);
   void getSubstitutionListByCodeAndDescription (DString& dstrSubstitutionList);
   void getCategory(const DString &dstrCode, DString &dstrCategory );
   void getAdminFeeRedCodeSubList(const DString & strRedCodesByTaxTypeList, DString& dstrAdminFeeRedCodeSubList);
   void getRedCodeSubList(const DString & strRedCodesByTaxTypeList, DString& dstrRedCodeSubList);
   void getPurchaseSrcOfFundCodeList( DString &dstrPurchaseSrcOfFundCodeList );
   void getRedemptionSrcOfFundCodeList( DString &dstrPurchaseSrcOfFundCodeList );
   void getTransferSrcOfFundCodeList( DString &dstrPurchaseSrcOfFundCodeList );
   void getDescByCode( const DString &dstrCode, DString &dstrDesc );
   void getCodeList( DString &dstrCodeList );
   bool isCodeInCategory( const DString &dstrCode, const DString &dstrCategory )	;//P0186486_FN15_The Source of Funds

protected:
   BFData* _pRequestData;

private:

   void linkSubstituteSet();
   DString m_dstrGroupCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//