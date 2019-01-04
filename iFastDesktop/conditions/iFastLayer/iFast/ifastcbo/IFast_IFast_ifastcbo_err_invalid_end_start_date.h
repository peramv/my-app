#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_end_start_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_end_start_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_end_start_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_END_START_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End date must be 18 years from Start date or later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Enddatum muss 18 Jahre nach dem Startdatum oder später liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de terminación debe ser 18 años después de la fecha de inicio o posterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de fin doit être postérieure de 18 ans ou plus à la date de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum moet 18 jaar na de begindatum of later zijn")); }

        // Actions
	};
}



