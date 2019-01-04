#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_acct_status_death : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_acct_status_death() { }
		~CIFast_IFast_ifastdbrkr_err_contract_acct_status_death() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_ACCT_STATUS_DEATH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Account Status is Death Status.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertrags-Kontostatus ist Todes-Status.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado de la cuenta del contrato es Muerta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte est Décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Status van accountovereenkomst is overleden")); }

        // Actions
	};
}



