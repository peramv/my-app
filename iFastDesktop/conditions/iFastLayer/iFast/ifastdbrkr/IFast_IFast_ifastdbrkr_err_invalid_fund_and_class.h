#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_fund_and_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_fund_and_class() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_fund_and_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_AND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Fund and Class entered for this Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Fund and Class entered for this Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige/r Fonds und Klasse für dieses Konto eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo un fondo y clase no válidos para esta cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds et classe saisis invalides pour ce compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig fonds en ongeldige categorie opgegeven voor dit account")); }

        // Actions
	};
}



