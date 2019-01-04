#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_invalid_profile : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_invalid_profile() { }
		~CIFast_Infrastructure_ifastdbrkr_err_invalid_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid front end.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid front end.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Front End.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Front end no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Achat invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige front-end")); }

        // Actions
	};
}



