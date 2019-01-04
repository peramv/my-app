#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_invalid_ordersrc_for_acct_designation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_invalid_ordersrc_for_acct_designation() { }
		~CIFast_IFast_ifastcbo_err_warn_invalid_ordersrc_for_acct_designation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_INVALID_ORDERSRC_FOR_ACCT_DESIGNATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid order source for account designation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Bestellquelle für Kontozuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Origen de orden no válido para la designación de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source de l'ordre est invalide pour la désignation du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige orderbron voor accountnaam")); }

        // Actions
	};
}



