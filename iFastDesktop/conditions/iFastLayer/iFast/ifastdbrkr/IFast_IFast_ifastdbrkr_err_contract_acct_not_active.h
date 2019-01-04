#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_acct_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_acct_not_active() { }
		~CIFast_IFast_ifastdbrkr_err_contract_acct_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_ACCT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Account Status is not Active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertrags-Kontostatus ist nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado de la cuenta del contrato es No activa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Status van accountovereenkomst is niet actief")); }

        // Actions
	};
}



