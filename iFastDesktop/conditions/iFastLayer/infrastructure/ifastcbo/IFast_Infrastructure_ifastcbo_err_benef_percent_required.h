#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_benef_percent_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_benef_percent_required() { }
		~CIFast_Infrastructure_ifastcbo_err_benef_percent_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEF_PERCENT_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid state country code was entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("An invalid state country code was entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein ungültiger Staat-/Ländercode wurde eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de estado/país no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un code de pays d'état/de province invalide a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldige staat/landcode opgegeven")); }

        // Actions
	};
}



