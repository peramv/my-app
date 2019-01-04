#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_brk_epa_status_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_brk_epa_status_not_active() { }
		~CIFast_IFast_ifastdbrkr_err_brk_epa_status_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BRK_EPA_STATUS_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker EPA Status is not active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut APE du courtier est inactif.")); }

        // Actions
	};
}



