#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundclass_settle_currency_different : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundclass_settle_currency_different() { }
		~CIFast_IFast_ifastcbo_err_fundclass_settle_currency_different() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDCLASS_SETTLE_CURRENCY_DIFFERENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund currency should be the same as settle currency for unit purchases.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds-Währung sollte die gleiche sein wie die Abrechnungs-Währung für Anteilkäufe.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa del fondo debe ser igual a la divisa de liquidación para compras de unidades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie du fonds devrait être identique à la monnais de règlement pour les achats en unités.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsvaluta moet dezelfde zijn als de betalingsvaluta voor eenheidsaankoop")); }

        // Actions
	};
}



