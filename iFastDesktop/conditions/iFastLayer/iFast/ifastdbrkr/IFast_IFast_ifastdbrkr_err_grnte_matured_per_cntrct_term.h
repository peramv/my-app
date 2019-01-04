#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_grnte_matured_per_cntrct_term : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_grnte_matured_per_cntrct_term() { }
		~CIFast_IFast_ifastdbrkr_err_grnte_matured_per_cntrct_term() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GRNTE_MATURED_PER_CNTRCT_TERM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee has matured per Contract Term or Reset.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Guarantee has matured per Contract Term or Reset.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La garantie est échue selon les termes du contrat ou la revalorisation.")); }

        // Actions
	};
}



