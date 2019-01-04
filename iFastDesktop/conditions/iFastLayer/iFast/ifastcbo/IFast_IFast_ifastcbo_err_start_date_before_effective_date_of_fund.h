#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_before_effective_date_of_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_before_effective_date_of_fund() { }
		~CIFast_IFast_ifastcbo_err_start_date_before_effective_date_of_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_BEFORE_EFFECTIVE_DATE_OF_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start Date cannot be before effective date of fund %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Startdatum kann nicht vor dem Effektivdatum von Fonds %DATE% liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de inicio no puede ser anterior a fecha de entrada en vigencia del fondo %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début ne peut être antérieure à la date d'entrée en vigueur du fonds %DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begindatum kan niet voor ingangsdatum van fonds %DATE% liggen")); }

        // Actions
	};
}



