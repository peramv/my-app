#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_early_termination : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_early_termination() { }
		~CIFast_IFast_ifastcbo_err_early_termination() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EARLY_TERMINATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reason code for early termination is needed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Begründungscode für vorzeitige Beendigung wird benötigt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el código de motivo para terminación prematura")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de raison de la résiliation anticipée est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Redencode voor vroegtijdige beëindiging is nodig")); }

        // Actions
	};
}



