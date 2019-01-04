#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warning_all_fund_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warning_all_fund_transfer() { }
		~CIFast_IFast_ifastcbo_err_warning_all_fund_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARNING_ALL_FUND_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is an All Fund Transfer which will transfer all the fund units from the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dies ist ein Gesamtfonds-Transfer, der alle Fonds-Anteile aus dem Konto transferieren wird.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ésta es una transferencia de todo el fondo que transferirá todas las unidades del fondo de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci est un transfert de tous les fonds qui transférera toutes les unités du fonds du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is een overdracht van alle fondsen die alle fondseenheden uit het account overdraagt")); }

        // Actions
	};
}



