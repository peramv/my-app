#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_do_not_have_access_to_desktop : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_do_not_have_access_to_desktop() { }
		~CIFast_IFast_ifastdbrkr_err_user_do_not_have_access_to_desktop() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DO_NOT_HAVE_ACCESS_TO_DESKTOP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have access to Desktop.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'a pas accès au bureau.")); }

        // Actions
	};
}



