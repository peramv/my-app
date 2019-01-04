#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_currency_not_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_currency_not_for_fund() { }
		~CIFast_IFast_ifastcbo_err_currency_not_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CURRENCY_NOT_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle currency is not valid for the fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Währung abrechnen ist nicht gültig für den Fonds")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa de liquidación no es válida para el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie de règlement est invalide pour le fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsvaluta is niet geldig voor het fonds")); }

        // Actions
	};
}



