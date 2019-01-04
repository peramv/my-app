#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_new_password_too_long : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_new_password_too_long() { }
		~CIFast_IFast_ifastdbrkr_err_new_password_too_long() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEW_PASSWORD_TOO_LONG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New password exceeds allowed length")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("New password exceeds allowed length")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nouveau passeport excède le nombre de caractères autorisé.")); }

        // Actions
	};
}



