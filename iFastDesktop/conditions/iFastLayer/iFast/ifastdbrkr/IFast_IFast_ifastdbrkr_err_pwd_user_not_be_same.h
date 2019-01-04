#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pwd_user_not_be_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pwd_user_not_be_same() { }
		~CIFast_IFast_ifastdbrkr_err_pwd_user_not_be_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PWD_USER_NOT_BE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password cannot be the same as UserId.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe ne peut être identique au code d'utilisateur.")); }

        // Actions
	};
}



