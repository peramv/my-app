#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pwd_not_contain_user : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pwd_not_contain_user() { }
		~CIFast_IFast_ifastdbrkr_err_pwd_not_contain_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PWD_NOT_CONTAIN_USER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password can not contain UserId.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe ne peut contenir le code d'utilisateur.")); }

        // Actions
	};
}



