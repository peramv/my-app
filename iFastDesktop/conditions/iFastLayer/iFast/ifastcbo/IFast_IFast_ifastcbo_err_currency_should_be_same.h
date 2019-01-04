#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_currency_should_be_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_currency_should_be_same() { }
		~CIFast_IFast_ifastcbo_err_currency_should_be_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CURRENCY_SHOULD_BE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The System Currency (%SYS_CURRENCY%) should be the same as the current Currency (%CURRENCY%).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The System Currency (%SYS_CURRENCY%) should be the same as the current Currency (%CURRENCY%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Systemwährung  (%SYS_CURRENCY%) sollte mit der aktuellen Währung (%CURRENCY%) übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa del sistema (%SYS_CURRENCY%) debe ser igual a la divisa actual (%CURRENCY%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie du système (%SYS_CURRENCY%) devrait être la même que la monnaie actuelle (%CURRENCY%).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De systeemvaluta (%SYS_CURRENCY%) moet hetzelfde zijn als de huidige valuta (%CURRENCY%)")); }

        // Actions
	};
}



