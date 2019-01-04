#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warning_fund_foreign_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warning_fund_foreign_currency() { }
		~CIFast_IFast_ifastcbo_err_warning_fund_foreign_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARNING_FUND_FOREIGN_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund class currency is different from system currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Fondsklassen-Währung unterscheidet sich von der Systemwährung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa de la clase de fondo es diferente de la divisa del sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie de la classe de fonds est différente de la monnaie du système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De valuta voor de fondscategorie verschilt van de systeemvaluta")); }

        // Actions
	};
}



