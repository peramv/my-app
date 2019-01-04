#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_of_registration : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_of_registration() { }
		~CIFast_IFast_ifastcbo_err_date_of_registration() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_OF_REGISTRATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registration date can not be modified to a date earlier than current registration date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierungsdatum darf nicht auf ein Datum vor dem aktuellen Registrierungsdatum geändert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de registro no puede modificarse a una fecha anterior a la fecha de registro actual.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'enregistrement ne peut être changée pour une date antérieure à la date d'enregistrement actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Registratiedatum kan niet worden gewijzigd in een eerdere datum dan de huidige registratiedatum")); }

        // Actions
	};
}



