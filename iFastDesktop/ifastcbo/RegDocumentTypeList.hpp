#pragma once
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegDocumentTypeList : 
      public MFCanBFCbo, 
      private boost::noncopyable
{
public:
   RegDocumentTypeList(BFAbstractCBO &parent);
   virtual ~RegDocumentTypeList(void);

   SEVERITY init( const DString& dstrComplyRule, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const DString& dstrComplyRule,
                  const DString& dstrAcctType,
                  const DString& dstrTaxType, 
                  const DString& dstrTaxJuris, 
				  const DString& dstrAcctDesignation, 
				  const DString& dstrBrokerCode, 
				  const DString& dstrInterCode,
				  const DString& dstrEffectiveDate, 
                  const DString& dstrTrack ,
                  const DString& dstrPageName);
   
   DString buildSubsitutionSet(const DString& dstrExcludeComplyRule = NULL_STRING );
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   void buildStrKey(DString &strKey, DString dstrRegDocId);

protected:   
   SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);

};
