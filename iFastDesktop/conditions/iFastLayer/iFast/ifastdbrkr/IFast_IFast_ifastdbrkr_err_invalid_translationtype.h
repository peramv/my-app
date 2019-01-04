#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_translationtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_translationtype() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_translationtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRANSLATIONTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Translation Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Umrechnungsart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de traducción no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de transaction invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig vertaaltype")); }

        // Actions
	};
}



