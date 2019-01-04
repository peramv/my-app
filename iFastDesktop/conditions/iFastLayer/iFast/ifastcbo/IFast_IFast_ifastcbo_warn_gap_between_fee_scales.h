#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_gap_between_fee_scales : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_gap_between_fee_scales() { }
		~CIFast_IFast_ifastcbo_warn_gap_between_fee_scales() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GAP_BETWEEN_FEE_SCALES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gaps not allowed in fee scales %SCALE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gaps not allowed in fee scales %SCALE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Gaps not allowed in fee scales %SCALE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Lacunes ne sont pas autorisés dans les barèmes d'honoraires %SCALE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gaps not allowed in fee scales %SCALE%.")); }

        // Actions
	};
}



