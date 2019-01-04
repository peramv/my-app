#pragma once

#include <commonport.h>

#include <bfdata\bfdataid.hpp>
#include <bfdata\bfdatafield.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

BF_DECL_BASE_EXCEPTION( BFDataNotImplementedException );
BF_DECL_BASE_EXCEPTION( BFDataFieldNotFoundException );
BF_DECL_BASE_EXCEPTION( BFDataRepeatNotFoundException );

class BFData;
class BFDataImplDefaults;
class ClientLocale;

class BFDATA_LINKAGE BFDataImpl
{
public:
   BFDataImpl( const BFDataId& id, const BFDataId& idRepeat )
   : id_( id )
   , idRepeat_( idRepeat )
   , cFields_( 0 )
   {}
   BFDataImpl( const BFDataId& id )
   : id_( id )
   , idRepeat_( ifds::NullDataId )
   , cFields_( 0 )
   {}
   virtual ~BFDataImpl() {}

   friend class BFData;

   // these have been moved to the public interface so that BFData::BufferStream
   // can access them.  I'll figure out the syntax to allow this when then methods
   // are protected later ... CP 20020321
   virtual unsigned long fromBuffer( const I_CHAR* pBuffer, const I_CHAR* const pEnd, long cbBuffer ) { return(0);}
   virtual unsigned long toBuffer( I_CHAR* pBuffer, long cbBuffer, const ClientLocale& rLocale ) const { return(0);}
   virtual unsigned long getDefinedByteLength() const = 0;

   static unsigned long getDefaultMarket();
   static unsigned long getDefaultClient();
   static const DString& getDefaultLocale();     // in enUS form

   static BFDataImplDefaults* setDefaults( BFDataImplDefaults* pDefaults );
   static const BFDataImplDefaults* getDefaults();


protected:
   virtual BFDataImpl* clone() = 0;

   inline unsigned int getFieldCount() { return(cFields_);}
   virtual BFDataField* getElementByIndex( unsigned int idx ) = 0;
   virtual const BFDataField* getElementByIndex( unsigned int idx ) const = 0;

   virtual unsigned long getLargestDefinedField() const = 0;

   virtual BFDataField* getElement( const BFFieldId& id ) = 0;
   virtual const BFDataField* getElement( const BFFieldId& id ) const = 0;

   const BFDataId& getId() const { return(id_);}
   const BFDataId& getRepeatId() const { return(idRepeat_);}
   inline bool isRepeatable() const { return(idRepeat_ != ifds::NullDataId);}

   virtual bool exists( const BFFieldId& idField ) const = 0;

protected:
   BFDataId    id_;
   BFDataId    idRepeat_;

   unsigned int cFields_;

private:
   static BFDataImplDefaults* s_pDefaults_;
};

