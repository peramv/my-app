#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_identical_fund_allocs : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_identical_fund_allocs() { }
		~CIFast_Infrastructure_ifastcbo_err_identical_fund_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_FUND_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid line number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid line number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Zeilenzahl.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de línea no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de ligne invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig regelnummer")); }

        // Actions
	};
}



