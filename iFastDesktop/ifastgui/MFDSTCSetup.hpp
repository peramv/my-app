
#ifndef MFDSTCSETUP_HPP
#define MFDSTCSETUP_HPP

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

/**
 * Utility class with single static method to start initial singletons.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/01/2000</dd></dl>
 * @version 0.1
 */
#ifndef DSTCSETUPTHREAD_HPP
#include <ifastdbrkr\DSTCSetupThread.hpp>
#endif
#include <ifastdbrkr\ifastdbrkr.hpp>

class ProcessManager;

class MFDSTCSetup
{
 public:
  static void exit();
  static bool init(bool bDirectConnect, const bool& performTesting, DString& errorMessage);

 private:
  static bool tryMessageService(const ifastdbrkr::MessageServiceConfig& smqConfig,
                                const ifastdbrkr::MessageServiceConfig& amqConfig,
                                DString& errorMessage);
  static DSTCSetupThread dstcSetupThread;
  static ProcessManager* s_rpProcessMgr;
};

#endif  // MFDSTCSETUP_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/MFDSTCSetup.hpp-arc  $
 *
 *    Rev 1.5   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.4   19 Mar 2002 13:44:50   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 *
 *    Rev 1.3   11 Oct 2001 18:22:18   SMITHDAV
 * Changed ProcessManager form singleton to static.
 *
 *    Rev 1.2   06 Jul 2001 14:07:14   HSUCHIN
 * call DSTCSetupThread to preload data properties
 *
 *    Rev 1.1   Feb 12 2001 15:55:20   HSUCHIN
 * changed init method to use direct RTS connection or Vm based on command line input.  Direct RTS
 * connection is the default
 *
 *    Rev 1.0   Mar 01 2000 12:15:40   MCNABBGL
 * Initial revision.
 *
 */
