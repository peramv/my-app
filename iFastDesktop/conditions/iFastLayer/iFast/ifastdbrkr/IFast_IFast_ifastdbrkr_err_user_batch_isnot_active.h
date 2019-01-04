#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_batch_isnot_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_batch_isnot_active() { }
		~CIFast_IFast_ifastdbrkr_err_user_batch_isnot_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_BATCH_ISNOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Users batch is not active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot des utilisateurs est inactif.")); }

        // Actions
	};
}



