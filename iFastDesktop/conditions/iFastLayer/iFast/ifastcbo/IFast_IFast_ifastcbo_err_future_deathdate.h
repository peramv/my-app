#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_deathdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_deathdate() { }
		~CIFast_IFast_ifastcbo_err_future_deathdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DEATHDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date of death may not be future dated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date de deces invalide. La date de deces ne peut pas être une date future.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Todesdatum. Das Todesdatum darf nicht in der Zukunft liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de fallecimiento no válida. La fecha de fallecimiento no puede ser en el futuro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de décès ne doit pas être postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige overlijdensdatum. Overlijdensdatum mag niet in de toekomst liggen")); }

        // Actions
	};
}



