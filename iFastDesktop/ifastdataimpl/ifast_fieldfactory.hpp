// Field Factory .hpp file
#include <bfdata/bfdatafieldfactory.hpp>
#include <bfdata/bfdatafield.hpp>
#include <clientlocale.hpp>
#undef IFAST_DATAIMPL_LINKAGE
#ifdef IFAST_DATAIMPL_DLL
   #define IFAST_DATAIMPL_LINKAGE CLASS_EXPORT
#else
   #define IFAST_DATAIMPL_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   class IFAST_DATAIMPL_LINKAGE ifast_FieldFactory : public BFDataFieldFactory
   {
   public:
      // Constructors
      ifast_FieldFactory();
      virtual ~ifast_FieldFactory();
      virtual BFDataField* createField( const BFFieldId id ) const;
   };
} // ifds namespace 
