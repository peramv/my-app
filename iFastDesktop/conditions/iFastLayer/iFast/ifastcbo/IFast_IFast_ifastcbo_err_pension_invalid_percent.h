#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pension_invalid_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pension_invalid_percent() { }
		~CIFast_IFast_ifastcbo_err_pension_invalid_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_INVALID_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Percentage.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Prozentsatz.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Porcentaje no válido:")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pourcentage invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig percentage")); }

        // Actions
	};
}



