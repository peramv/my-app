#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_user : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_user() { }
		~CIFast_IFast_ifastdbrkr_err_no_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_USER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Utilisateur introuvable")); }

        // Actions
	};
}



