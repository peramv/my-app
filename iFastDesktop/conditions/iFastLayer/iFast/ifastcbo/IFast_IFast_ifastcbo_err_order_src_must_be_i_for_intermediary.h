#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_order_src_must_be_i_for_intermediary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_order_src_must_be_i_for_intermediary() { }
		~CIFast_IFast_ifastcbo_err_order_src_must_be_i_for_intermediary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORDER_SRC_MUST_BE_I_FOR_INTERMEDIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order Source must be Intermediary.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Order Source must be Intermediary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestellquelle muss \"I\" für Intermediary (Mittler) sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El origen de la orden debe ser \"I\" para Intermediario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source de l'ordre doit être l'intermédiaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Orderbron moet 'I' voor tussenpersoon zijn")); }

        // Actions
	};
}



