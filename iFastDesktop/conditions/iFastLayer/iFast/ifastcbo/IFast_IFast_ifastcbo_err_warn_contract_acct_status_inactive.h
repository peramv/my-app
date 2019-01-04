﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_contract_acct_status_inactive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_contract_acct_status_inactive() { }
		~CIFast_IFast_ifastcbo_err_warn_contract_acct_status_inactive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_CONTRACT_ACCT_STATUS_INACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Account Status is not Active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertrags-Kontostatus ist nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado de la cuenta del contrato es No activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte du contrat est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Status van accountovereenkomst is niet actief")); }

        // Actions
	};
}



