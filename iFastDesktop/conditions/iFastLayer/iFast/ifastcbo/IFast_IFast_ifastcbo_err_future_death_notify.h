#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_death_notify : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_death_notify() { }
		~CIFast_IFast_ifastcbo_err_future_death_notify() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DEATH_NOTIFY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death notification date can not be future dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungsdatum darf nicht in der Zukunft liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de notificación de fallecimiento no puede ser en el futuro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de notification du décès ne peut être postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datum overlijdensbericht mag niet in de toekomst liggen")); }

        // Actions
	};
}



