#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_end_birth_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_end_birth_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_end_birth_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_END_BIRTH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End date must be 60 years from birth date or later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Enddatum muss 60 Jahre nach dem Geburtsdatum oder später liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de terminación debe ser 60 años después de la fecha de nacimiento o posterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de fin doit être postérieure de 60 ans ou plus à la date de naissance.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum moet 60 jaar na de geboortedatum of later zijn")); }

        // Actions
	};
}



