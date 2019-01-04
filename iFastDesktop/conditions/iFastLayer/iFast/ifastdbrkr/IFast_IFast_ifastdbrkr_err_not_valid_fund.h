#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_valid_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_valid_fund() { }
		~CIFast_IFast_ifastdbrkr_err_not_valid_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_VALID_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash' is not a valid fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cash' is not a valid fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("\"Bargeld\" ist kein gültiger Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("\"Efectivo\" no es un fondo válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Comptant n'est pas un fonds valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Contant' is geen geldig fonds")); }

        // Actions
	};
}



