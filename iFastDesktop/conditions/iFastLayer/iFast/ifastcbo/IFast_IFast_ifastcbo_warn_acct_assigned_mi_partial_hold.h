#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_assigned_mi_partial_hold : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_assigned_mi_partial_hold() { }
		~CIFast_IFast_ifastcbo_warn_acct_assigned_mi_partial_hold() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_ASSIGNED_MI_PARTIAL_HOLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account assigned for reason of CDICHoldFile-Partial Hold.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte assigné en raison d'un fichier de retenue de la SADC – retenue partielle")); }

        // Actions
	};
}



