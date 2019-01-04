#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_pd_has_been_used_recently_choose_another : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_pd_has_been_used_recently_choose_another() { }
		~CIFast_Infrastructure_ifastdbrkr_err_pd_has_been_used_recently_choose_another() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_HAS_BEEN_USED_RECENTLY_CHOOSE_ANOTHER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid function type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid function type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Funktionstyp.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de función no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de fonction invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig functietype")); }

        // Actions
	};
}



