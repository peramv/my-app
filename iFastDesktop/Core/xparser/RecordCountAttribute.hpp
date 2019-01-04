#pragma once

#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class RecordCountAttribute : public ElementAttribute
   {
   public:

      enum RecordCountType
      {
         RCT_NONE = 0,
         RCT_ALL_RECORDS,
         RCT_NUMERIC
      };

      RecordCountAttribute( xercesc::AttributeList &attributes );
      RecordCountAttribute( int recordCount );
      RecordCountAttribute( RecordCountType type = RCT_NONE );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator RecordCountType() const
      {
         return(_type);
      }

      //   operator int() const
      //   {
      //      return _recordCount;
      //   }

   private:
      RecordCountType _type;
      DString _strRecordCount;
      int _recordCount;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/RecordCountAttribute.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 11:01:18   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.3   Oct 09 2002 17:43:20   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 19 2002 09:28:56   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.1   14 May 2002 16:44:14   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:46   SMITHDAV
//Initial revision.
 * 
 */

