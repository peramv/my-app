#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pwd_not_change : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pwd_not_change() { }
		~CIFast_IFast_ifastdbrkr_err_pwd_not_change() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PWD_NOT_CHANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password change failed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de changement de mot de passe")); }

        // Actions
	};
}



