#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_effective_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid effective date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Effektivdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de entrada en vigencia no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date d'entrée en vigueur invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige ingangsdatum")); }

        // Actions
	};
}



