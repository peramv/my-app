﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_acct_contract_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_acct_contract_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_acct_contract_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACCT_CONTRACT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No account level contract information is available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No account level contract information is available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Konto-Level-Vertragsinformationen verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información del contrato a nivel de la cuenta disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur le contrat au niveau du compte n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen overeenkomstgegevens op accountniveau beschikbaar")); }

        // Actions
	};
}



