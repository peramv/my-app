#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_status_death_or_death_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_status_death_or_death_transfer() { }
		~CIFast_IFast_ifastcbo_err_acct_status_death_or_death_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_STATUS_DEATH_OR_DEATH_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Status must be changed to Death or Death Transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte doit être changé pour Décès ou Transfert au décès.")); }

        // Actions
	};
}



