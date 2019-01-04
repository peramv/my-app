#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_early_end_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_early_end_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_early_end_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_EARLY_END_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End date can not be earlier than Start date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Enddatum darf nicht vor dem Startdatum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de terminación no puede ser anterior a la fecha de inicio")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de fin ne peut être antérieure à la date de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum kan niet vroeger zijn dan begindatum")); }

        // Actions
	};
}



