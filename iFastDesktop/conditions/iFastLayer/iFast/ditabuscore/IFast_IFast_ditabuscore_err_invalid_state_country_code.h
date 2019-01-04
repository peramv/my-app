#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_state_country_code : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_state_country_code() { }
		~CIFast_IFast_ditabuscore_err_invalid_state_country_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_STATE_COUNTRY_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage must be greater than zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le pourcentage doit être superieur a zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz muss größer als Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje debe ser mayor que cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage doit être supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage moet groter dan nul zijn")); }

        // Actions
	};
}



