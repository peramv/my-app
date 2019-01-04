#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_from_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_from_currency() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_from_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FROM_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid From Currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Von-Währung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Divisa de origen no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Monnaie source invalid")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige van-valuta")); }

        // Actions
	};
}



