#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_pwd_recently_used : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_pwd_recently_used() { }
		~CIFast_IFast_ifastdbrkr_pwd_recently_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("PWD_RECENTLY_USED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password has been recently used.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe a été utilisé récemment.")); }

        // Actions
	};
}



