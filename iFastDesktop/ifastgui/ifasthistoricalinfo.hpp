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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : IFastBaseMainDlg.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2003
//
// ^CLASS    : IFastHistoricalInfo
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


class BaseMainDlg;
class BFContainerId;

class IFastHistoricalInfo
{
public:
   bool operator()( BaseMainDlg* pDlg, const BFContainerId& idContainer, DString dstrType = I_("SINGLE") );
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ifasthistoricalinfo.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 14:29:20   popescu
//PET965 FN11, removed some commented out old code
//
//   Rev 1.3   Feb 28 2004 16:03:02   HERNANDO
//PET965 FN11 - Additional historical enhancement.  Support for single or multiple view calls.
//
//   Rev 1.2   Mar 21 2003 18:38:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Mar 05 2003 10:56:50   PURDYECH
//Make this a function object for cleaner design.
//
//   Rev 1.2   Feb 03 2003 11:57:00   popescu
//Displaying the history button only when the item is not new, and adding some txt message for the status bar
//
//   Rev 1.1   Jan 28 2003 13:16:42   popescu
//Historical Info feature implementation
//
//   Rev 1.0   Jan 26 2003 13:46:44   popescu
//Initial Revision
 * 
 */
