#ifndef SOMINC_H
#define SOMINC_H

#pragma message( "including "__FILE__ )

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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : sominc.h
//
// ^DESCRIPTION: This file includes the AWD Som headers and any regular
//               header that includes an AWD SOM header.
//
//               The file <somcorba.h> has been modified so that if the
//               Rogue Wave standard library is being used, that it
//               NOT typedef string as char *.  We are #defining it here
//               and at the end of this list we will #undef string.
//
//               These files are listed here so that scandeps will generate a
//               dependancy for them
//
                 #if 0
                    #include "somcorba.h"
                    #include "awdsom.h"
                    #include "awdassrt.h"
                 #endif
//
//  Inlcude this header before ANYTHING that uses the standard C++ library
//
//******************************************************************************

#define string char *

#ifndef _AWDON_H
   #include "awdon.h"
#endif

#ifndef AWDOFF_H
   #include "awdoff.h"
#endif

#ifndef SOM_ACBL0030_xh
   #include "ACBL0030.xh"
#endif

#ifndef SOM_ACBL0043_xh
   #include "ACBL0043.xh"
#endif

#ifndef SOM_ACBL0044_xh
   #include "ACBL0044.xh"
#endif

#ifndef SOM_ACBL0045_xh
   #include "ACBL0045.xh"
#endif

#ifndef SOM_ACBL0046_xh
   #include "ACBL0046.xh"
#endif

#ifndef SOM_ACBL0048_xh
   #include "ACBL0048.xh"
#endif

#ifndef SOM_ACBL0342_xh
   #include "ACBL0342.xh"
#endif

#ifndef SOM_AWDApplication_xh
   #include "awdapp.xh"
#endif

#ifndef SOM_LookupCriteria_xh
   #include "lkupaid.xh"
#endif

#ifndef SOM_AWDWork_xh
   #include "wrkobj.xh"
#endif

#ifndef SOM_AWDBase_xh
   #include "awdobj.xh"
#endif

#ifndef SOM_AWDUser_xh
   #include "awduser.xh"
#endif

#ifndef SOM_AWDWorkStation_xh
   #include "awdwksta.xh"
#endif

#ifndef SOM_AWDEntityDefaults_xh
   #include "entity.xh"
#endif

#ifndef SOM_AWDEvent_xh
   #include "awdevent.xh"
#endif

#ifndef SOM_AWDListener_xh
   #include "awdlsten.xh"
#endif

#ifndef SOM_AWDObjectFactory_xh
   #include "objfact.xh"
#endif

#ifndef SOM_AWDSource_xh
   #include "srcobj.xh"
#endif

#ifndef SOM_AWDSuspaid_xh
   #include "suspaid.xh"
#endif

// Undefine this puppie!
#undef string

#endif // SOMINC_H
