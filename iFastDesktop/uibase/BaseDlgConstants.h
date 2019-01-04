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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// List flags
const int LISTFLAG_NOT_UPDATABLE  = 0x0001;    // List not updateable
const int LISTFLAG_NOT_AUTO_ADD   = 0x0002;    // Don't automatically add a row when empty
const int LISTFLAG_TIMER          = 0x0004;    // Timer list control (there is a timming before a selection is handled)

// Control flags
const int CTRLFLAG_DEFAULT                      = 0x0000;
const int CTRLFLAG_NOT_UPDATABLE                = 0x0001;   // Read only
const int CTRLFLAG_FIELDS_FROM_SUB_LIST         = 0x0002;   // Substitutes = multiple fields
const int CTRLFLAG_MANUAL_LOAD                  = 0x0004;   // No auto load/clear
const int CTRLFLAG_MANUAL_INIT                  = 0x0008;   // Depend on dialog for init
const int CTRLFLAG_INITCOMBO_BY_SUB_LIST        = 0x0010;   // Use substitution for entries
const int CTRLFLAG_INITCOMBO_WITH_BLANK         = 0x0020;   // Use substitution for entries
const int CTRLFLAG_NO_STRIP_LEADING_SPACE       = 0x0040;   // Allow leading spaces
const int CTRLFLAG_AUTO_UPDATE_ON_CHANGE        = 0x0080;   // Store data whenever data 
                                                            //  changes instead of waiting 
                                                            //  for kill focus - this may
                                                            //  or may not be implemented
                                                            //  by the derived control.
const int CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE   = 0x0100;   // Use substitution code for entries 
const int CTRLFLAG_GUI_FIELD                    = 0x0200;   // Field not associated with CBO
const int CTRLFLAG_MASKED                       = 0x0400;   // Field uses a mask
const int CTRLFLAG_WORD_WRAP                    = 0x0800;   // for multiline edit controls, performs a word wrap and automatically adds a new line if the max. number of chars is reached for the current line
const int CTRLFLAG_LINE_PACK                    = 0x1000;   // for multiline edit controls, 
                                                            // empty line will be removed between 1st and last line if the flag turned on.
const int CTRLFLAG_COMBO_EDIT                   = 0x2000;   // for combo boxes that have the CBS_DROPDOWN style (editable) 

// Other flags
//const int IDOK_NOT_CHECK = -1; //Do not perform permission check for OK button

enum E_CONTROLTYPE
{
   CTRL_EDIT,
   CTRL_COMBO,
   CTRL_DATE, 
   CTRL_CHECKBOX,
   CTRL_STATIC,
   CTRL_FUNDCLASS_EDIT,
   CTRL_BUTTON,
   CTRL_TIME
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/BaseDlgConstants.h-arc  $
 * 
 *    Rev 1.15   05 May 2009 10:08:14   popescu
 * Added support for drop down comboxes. The value typed in is appended to the subst set.
 * 
 *    Rev 1.14   Jul 06 2005 13:54:20   hernando
 * PET1250 FN01 - Added CTRL_DATE.
 * 
 *    Rev 1.13   Apr 14 2005 11:48:40   yingbaol
 * Incident283230: add new flag  CTRLFLAG_LINE_PACK                
 * 
 *    Rev 1.12   Nov 30 2004 16:29:50   Fengyong
 * Add CTRL_BUTTON
 * 
 *    Rev 1.11   May 24 2003 15:04:04   PURDYECH
 * Made the values hex.  
 * Prettied up the file and comments.
 * 
 *    Rev 1.10   Oct 09 2002 17:42:36   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.9   26 Apr 2002 10:36:46   KOVACSRO
 * Added CTRLFLAG_WORD_WRAP.
 * 
 *    Rev 1.8   01 Apr 2002 16:20:54   HSUCHIN
 * added CTRLFLAG_INITCOMBO_WITH_BLANK
 * 
 *    Rev 1.7   19 Mar 2002 13:36:02   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.6   04 Feb 2002 15:17:52   KOVACSRO
 * Added LISTFLAG_TIMER for timer list controls.
 * 
 *    Rev 1.5   06 Jun 2001 17:02:48   YINGZ
 * add control flag CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE
 * 
 *    Rev 1.4   Dec 05 2000 17:08:38   KOVACSRO
 * Added a flag for permission check.
 * 
 *    Rev 1.3   May 31 2000 14:43:58   BUZILA
 * added Masked flag
 * 
 *    Rev 1.2   May 08 2000 12:57:18   BUZILA
 * added CTRL_FUNDCLASS_EDIT value in  enum E_CONTROLTYPE
 * 
 *    Rev 1.1   Feb 15 2000 18:58:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Dec 08 1999 16:29:04   DT24433
// added list flags
// 
//    Rev 1.0   Dec 07 1999 17:58:52   VASILEAD
// Initial revision.
 * 
 */
