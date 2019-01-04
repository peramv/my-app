﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_minimum_fund_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_minimum_fund_balance() { }
		~CIFast_IFast_ifastcbo_err_minimum_fund_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MINIMUM_FUND_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum fund and class balance for %FUND% and %CLASS% is %MINIMUM_BAL%.  Balance goes beyond minimum amount after this trade.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le solde de catégorie et de fond minimum pour %FUND%, %CLASS% est %MINIMUM_BAL%. Le solde depasse le montant minimum apres cette operation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimaler Fonds- und Klassensaldo für %FUND% und %CLASS% beträgt %MINIMUM_BAL%. Saldo unterhalb des Minimums nach diesem Handel.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo mínimo para el fondo %FUND% y la clase %CLASS% es de %MINIMUM_BAL%.  El saldo excede el monto mínimo después de esta operación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde minimal du fonds %FUND% et de la classe %CLASS% est %MINIMUM_BAL%. Le solde sera inférieur au montant minimal après cette transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Minimale fonds- en categoriesaldo voor %FUND% en %CLASS% is %MINIMUM_BAL%. Saldo komt onder het minimumbedrag na deze transactie")); }

        // Actions
	};
}



