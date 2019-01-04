#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_date_range : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_date_range() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_date_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_DATE_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid date range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Datumsbereich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Rango de fechas no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plage de dates invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig datumbereik")); }

        // Actions
	};
}



