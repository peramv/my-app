#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_cont_settl_status_cannot_be_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_cont_settl_status_cannot_be_selected() { }
		~CIFast_IFast_ifastcbo_err_acct_cont_settl_status_cannot_be_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CONT_SETTL_STATUS_CANNOT_BE_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement status cannot be selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut Règlement ne peut être sélectionné.")); }

        // Actions
	};
}



