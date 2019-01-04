#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_acct_value_rec_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_acct_value_rec_exists() { }
		~CIFast_IFast_ifastdbrkr_err_no_acct_value_rec_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACCT_VALUE_REC_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Account Value Record Exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es existiert kein Konto-Wert-Eintrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No existe un registro de valor de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune valeur marchande n’existe pour ce fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat geen record voor de accountwaarde")); }

        // Actions
	};
}



