#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_distrib_to_cash_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_distrib_to_cash_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_distrib_to_cash_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DISTRIB_TO_CASH_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution to Cash not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verteilung auf Bargeld nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten distribuciones a efectivo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Distribution en argent non autorisée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributie naar Contant is niet toegestaan")); }

        // Actions
	};
}



