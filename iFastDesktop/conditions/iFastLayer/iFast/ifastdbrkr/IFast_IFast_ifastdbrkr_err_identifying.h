#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_identifying : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_identifying() { }
		~CIFast_IFast_ifastdbrkr_err_identifying() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTIFYING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("We could not identify you in the system.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wir konnten Sie im System nicht identifizieren")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pudimos identificarlo en el sistema")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Nous n'avons pu vous identifier dans le système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wij konden u niet identificeren in het systeem")); }

        // Actions
	};
}



