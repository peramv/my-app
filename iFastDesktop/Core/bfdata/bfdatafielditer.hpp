#pragma once

#include <commonport.h>

#include <bfdata\bfdata.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif


/*
   Usage:
  
   BFData data;
   BFDataFieldIter iter( data );
   DString value;
  
   for( ; iter; ++iter )
   {
      const BFDataField& df = iter();
      // do something with df   
   }

*/

class BFDATA_LINKAGE BFDataFieldIter
{
public:

   BFDataFieldIter( BFData& in, bool bIncludeAppended = true );
   ~BFDataFieldIter();

   void operator++();
   BFDataField& operator()();
   operator int () const;

   void reset();
private:

   BFData&        data_;
   unsigned int   iFixed_;
   bool           bIncludeAppended_;
   BFData::ExtraFieldsMap_Iter         itExtraFields_;

   enum
   {
      Fixed, Extra, AtEnd
   } eFieldArea_;

};

class BFDATA_LINKAGE BFConstDataFieldIter
{
public:
   BFConstDataFieldIter( const BFData& in, bool bIncludeAppended = true );
   ~BFConstDataFieldIter();

   void operator++();
   const BFDataField& operator()() const;
   operator int () const;

   void reset();
private:
   const BFData&  data_;
   unsigned int   iFixed_;
   bool           bIncludeAppended_;
   BFData::ExtraFieldsMap_Iter         itExtraFields_;

   enum
   {
      Fixed, Extra, AtEnd
   } eFieldArea_;

};

