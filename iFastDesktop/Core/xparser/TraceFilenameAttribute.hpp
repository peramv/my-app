#pragma once
#include <bfutil\elementattribute.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{
   class XPARSER_LINKAGE TraceFilenameAttribute : public ElementAttribute
   {
   public:

      TraceFilenameAttribute();
      TraceFilenameAttribute( xercesc::AttributeList &attributes );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;

      void setValue( const DString& traceFilename );

      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

   private:
      DString _traceFilename;

   };

}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/xparser/TraceFilenameAttribute.hpp-arc  $
//
//   Rev 1.2   Mar 09 2004 11:01:38   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.1   Oct 09 2002 17:43:24   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Sep 19 2002 15:22:10   IVESPAUL
//Initial revision.
//
