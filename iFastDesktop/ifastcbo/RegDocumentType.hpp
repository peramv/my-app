#ifndef REG_DOCUMENT_TYPE_HPP
#define REG_DOCUMENT_TYPE_HPP

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegDocumentType : 
      public MFCanBFCbo, 
      private boost::noncopyable
{
public:
   RegDocumentType(BFAbstractCBO &parent);
   virtual ~RegDocumentType(void);

   SEVERITY init (const BFData& data);
};

#endif