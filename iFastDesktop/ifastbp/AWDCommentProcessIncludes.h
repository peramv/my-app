#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AWDCommentProcessIncludes.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : AWDCommentProcessIncludes
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{     
	extern CLASS_IMPORT const BFTextFieldId Remark1;	
	extern CLASS_IMPORT const BFTextFieldId Remark2;	
	extern CLASS_IMPORT const BFTextFieldId Remark3;	
	extern CLASS_IMPORT const BFTextFieldId Remark4;	
	extern CLASS_IMPORT const BFTextFieldId Remark5;		
	
	extern CLASS_IMPORT const BFTextFieldId BusinessArea;
	extern CLASS_IMPORT const BFTextFieldId WorkType;
	extern CLASS_IMPORT const BFTextFieldId StatusDesc;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AWDCommentProcessIncludes.h-arc  $
//
//   Rev 1.1   May 10 2004 12:18:02   VADEANUM
//PET1017 - AWD Comments - Limit Comment to 250 characters.
//
//   Rev 1.0   May 06 2004 16:31:06   VADEANUM
//Initial revision.
 */

