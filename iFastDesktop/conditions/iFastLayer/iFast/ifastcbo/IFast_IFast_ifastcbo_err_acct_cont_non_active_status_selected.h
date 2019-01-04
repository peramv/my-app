#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_cont_non_active_status_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_cont_non_active_status_selected() { }
		~CIFast_IFast_ifastcbo_err_acct_cont_non_active_status_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CONT_NON_ACTIVE_STATUS_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Active status can be selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le statut Actif peut être sélectionné.")); }

        // Actions
	};
}



