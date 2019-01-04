#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_status_not_allowed_for_acct_death_or_death_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_status_not_allowed_for_acct_death_or_death_transfer() { }
		~CIFast_IFast_ifastcbo_err_status_not_allowed_for_acct_death_or_death_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STATUS_NOT_ALLOWED_FOR_ACCT_DEATH_OR_DEATH_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Status not allowed for account status Death or Death Transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Statut non autorisé pour les statuts de compte Décès ou Transfert au décès")); }

        // Actions
	};
}



