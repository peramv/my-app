#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_effective_date_must_late : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_effective_date_must_late() { }
		~CIFast_IFast_ifastcbo_err_effective_date_must_late() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFFECTIVE_DATE_MUST_LATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The new record's Effective Date must be later than previous.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Effektivdatum des neuen Eintrags muss hinter dem vorigen liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia del nuevo registro debe ser posterior a la anterior.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La nouvelle date d'entrée en vigueur de l'enregistrement doit être postérieure à la précédente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De ingangsdatum van het nieuwe record moet later zijn dan die van het voorgaande record")); }

        // Actions
	};
}



