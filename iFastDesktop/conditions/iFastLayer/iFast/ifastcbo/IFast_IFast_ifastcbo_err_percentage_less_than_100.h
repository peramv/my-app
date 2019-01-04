#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_less_than_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_less_than_100() { }
		~CIFast_IFast_ifastcbo_err_percentage_less_than_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_LESS_THAN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage of the Account must be 100% since shareholder level allocation is not allowed for AMS Rebalancing.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Percentage of the Account must be 100% since shareholder level allocation is not allowed for AMS Rebalancing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz des Kontos muss 100% sein, da die Aktionärs-Level-Zuweisung nicht für „RB“(Rebalancin=Wiederausgleich)-Arten (AMS Rebalancing) zugelassen ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje de la cuenta debe ser 100% since shareholder level allocation is not allowed for \"RB\" type (AMS Rebalancing).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage du compte doit être 100 % puisque la répartition au niveau de l'actionnaire n'est pas autorisée pour le rebalancement du service de gestion de portefeuille.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage van het account moet 100 % zijn omdat allocatie op aandeelhoudersniveau niet toegestaan is voor 'RB'-type (Nieuwe saldering BBD)")); }

        // Actions
	};
}



