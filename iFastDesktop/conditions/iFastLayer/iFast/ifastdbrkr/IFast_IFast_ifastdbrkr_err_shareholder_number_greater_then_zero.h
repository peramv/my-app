#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shareholder_number_greater_then_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shareholder_number_greater_then_zero() { }
		~CIFast_IFast_ifastdbrkr_err_shareholder_number_greater_then_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_NUMBER_GREATER_THEN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder Number must be greater than zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Shareholder Number must be greater than zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionärsnummer muss größer als Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número del accionista debe ser mayor que cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'actionnaire doit être supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer aandeelhouder moet groter dan nul zijn")); }

        // Actions
	};
}



