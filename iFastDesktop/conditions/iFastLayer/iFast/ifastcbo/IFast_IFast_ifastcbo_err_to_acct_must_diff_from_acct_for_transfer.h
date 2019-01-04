#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_transfer() { }
		~CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account To number must be different from Account From number for the Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("KontoZu-Nummer und KontoVon-Nummer müssen für den Händler verschieden sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta de destino debe ser diferente del número de cuenta de origen para la transferencia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de cible du compte cible doit être différent du numéro d'origine du compte pour le transfert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer Account naar moet anders zijn dan nummer Account van voor de overdracht")); }

        // Actions
	};
}



