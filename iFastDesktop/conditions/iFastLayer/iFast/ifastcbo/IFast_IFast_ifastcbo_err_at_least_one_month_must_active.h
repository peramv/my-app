#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_least_one_month_must_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_least_one_month_must_active() { }
		~CIFast_IFast_ifastcbo_err_at_least_one_month_must_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_LEAST_ONE_MONTH_MUST_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one or more months must be active for a %FREQUENCY% frequency.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Un mois au moins doit être actif pour une frequence %FREQUENCY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein oder mehrere Monate müssen für eine %FREQUENCY% -Häufigkeit aktiv sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe estar activo al menos uno o más meses para una frecuencia de %FREQUENCY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un ou plusieurs mois doivent être actifs pour une fréquence %FREQUENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moeten ten minste een of meer maanden actief zijn voor een %FREQUENCY% frequentie")); }

        // Actions
	};
}



