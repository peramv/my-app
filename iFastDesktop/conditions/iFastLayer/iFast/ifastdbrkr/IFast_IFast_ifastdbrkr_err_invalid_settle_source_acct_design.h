#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_settle_source_acct_design : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_settle_source_acct_design() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_settle_source_acct_design() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLE_SOURCE_ACCT_DESIGN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Settlement Source for Account Designation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Abrechnungsquelle für Konto-Zuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Origen de liquidación no válido para la designación de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Source de règlement invalide pour la désignation du compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige betalingsbron voor accountnaam")); }

        // Actions
	};
}



