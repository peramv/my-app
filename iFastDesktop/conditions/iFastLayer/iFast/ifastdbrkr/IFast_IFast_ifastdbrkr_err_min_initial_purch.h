#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_min_initial_purch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_min_initial_purch() { }
		~CIFast_IFast_ifastdbrkr_err_min_initial_purch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIN_INITIAL_PURCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum Initial Purchase.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimaler Erstkauf")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Compra inicial mínima")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Achat initial minimal")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Minimum eerste aankoop")); }

        // Actions
	};
}



