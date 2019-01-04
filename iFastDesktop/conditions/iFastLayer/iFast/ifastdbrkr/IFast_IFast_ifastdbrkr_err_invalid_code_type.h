#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_code_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_code_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_code_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CODE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Code Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Codeart")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de código no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de code introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig codetype")); }

        // Actions
	};
}



