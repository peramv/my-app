#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eff_date_late_than_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eff_date_late_than_stop_date() { }
		~CIFast_IFast_ifastcbo_err_eff_date_late_than_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFF_DATE_LATE_THAN_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date must precede Stop Date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective Date must precede Stop Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum muss vor dem Stopdatum liegen, bitte geben Sie das Effektivdatum neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia debe ser anterior a la fecha de baja. Por favor vuelva a introducir la fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être antérieure à la date d'arrêt.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum moet voor de einddatum liggen, voer de ingangsdatum opnieuw in")); }

        // Actions
	};
}



