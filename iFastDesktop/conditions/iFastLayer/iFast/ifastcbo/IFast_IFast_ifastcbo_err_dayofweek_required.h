#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dayofweek_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dayofweek_required() { }
		~CIFast_IFast_ifastcbo_err_dayofweek_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DAYOFWEEK_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Day Of Week information is required for the Weekly or BiWeekly frequency.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The Day Of Week information is required for the Weekly or BiWeekly frequency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Wochentaginformation ist für die Wöchentliche oder Vierzehntägliche Häufigkeit erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información de día de la semana es obligatoria para la frecuencia semanal o bisemanal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le jour de semaine est requise pour les fréquence hebdomadaire et bihebdomadaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De gegevens over de dag van de week zijn vereist voor de wekelijkse of veertiendaagse frequentie")); }

        // Actions
	};
}



