#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_order_source_acct_desgin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_order_source_acct_desgin() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_order_source_acct_desgin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ORDER_SOURCE_ACCT_DESGIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Order Source for Account Designation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Bestellquelle für Konto-Zuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Origen de orden no válido para la designación de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source de l'ordre est invalide pour la désignation du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige orderbron voor accountnaam")); }

        // Actions
	};
}



