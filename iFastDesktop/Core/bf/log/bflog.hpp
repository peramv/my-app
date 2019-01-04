#pragma once

namespace bf {
namespace log {

enum Category
{
//   trace         = 0x00000001,
   notification  = 0x00000002,
   field         = 0x00000004,
   cbo           = 0x00000008,
   process       = 0x00000010,
   service       = 0x00000020,
   xml           = 0x00000040,
   databroker    = 0x00000080,
   conmgr        = 0x00000100,
   view          = 0x00000200,
   server        = 0x00000400,
   gui           = 0x00000800,
   config        = 0x00001000,
   awd           = 0x00002000,

   // values from 0x0800 to 0x8000 are reserved
   all           = 0xffffffff
};


}  // namespace log
}  // namespace bf



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/bflog.hpp-arc  $
//
//   Rev 1.2   Feb 20 2009 14:33:26   purdyech
//ZTS Revision 6
//
//   Rev 1.1   May 09 2007 10:25:30   purdyech
//Introduce EXECHIST Logging for AWD
//
//   Rev 1.0   Aug 12 2003 10:14:08   PURDYECH
//Initial revision.
//
