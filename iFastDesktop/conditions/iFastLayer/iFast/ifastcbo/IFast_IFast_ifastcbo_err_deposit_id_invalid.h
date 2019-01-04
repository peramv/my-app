#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_id_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_id_invalid() { }
		~CIFast_IFast_ifastcbo_err_deposit_id_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_ID_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit ID is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-ID ist ungültig. Bitte geben Sie es neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La identificación de depósito no es válida. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deposito-ID is ongeldig. Vul opnieuw in")); }

        // Actions
	};
}



