#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ordersrc_must_be_intermediary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ordersrc_must_be_intermediary() { }
		~CIFast_IFast_ifastcbo_err_ordersrc_must_be_intermediary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORDERSRC_MUST_BE_INTERMEDIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order source must be intermediary account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestellquelle muss \"I\" für Intermediary (Mittler)-Konto sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El origen de la orden debe ser \"I\" para la cuenta de intermediario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source de l'ordre doit être le compte intermédiaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Orderbron bron moet 'I' voor account tussenpersoon zijn")); }

        // Actions
	};
}



