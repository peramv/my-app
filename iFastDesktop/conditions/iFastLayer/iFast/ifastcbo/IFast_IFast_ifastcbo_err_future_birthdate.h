#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_birthdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_birthdate() { }
		~CIFast_IFast_ifastcbo_err_future_birthdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_BIRTHDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date of birth may not be future dated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date de naissance invalide. La date de naissance ne peut pas être une date future.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Geburtsdatum. Das Geburtsdatum darf nicht in der Zukunft liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de nacimiento no válida. La fecha de nacimiento no puede ser en el futuro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance ne peut être postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige geboortedatum. Geboortedatum mag niet in de toekomst liggen")); }

        // Actions
	};
}



