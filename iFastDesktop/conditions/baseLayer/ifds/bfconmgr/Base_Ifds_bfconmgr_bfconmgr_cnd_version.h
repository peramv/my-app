#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfconmgr_bfconmgr_cnd_version : public CConditionObject
	{
	public:
		CBase_Ifds_bfconmgr_bfconmgr_cnd_version() { }
		~CBase_Ifds_bfconmgr_bfconmgr_cnd_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BFCONMGR_CND_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dev")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dev")); }

        // Actions
	};
}



