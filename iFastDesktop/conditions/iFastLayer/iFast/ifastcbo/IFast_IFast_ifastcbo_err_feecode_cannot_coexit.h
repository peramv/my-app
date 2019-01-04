#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_feecode_cannot_coexit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_feecode_cannot_coexit() { }
		~CIFast_IFast_ifastcbo_err_feecode_cannot_coexit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEECODE_CANNOT_COEXIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FeeCode %FEECODE1% and %FEECODE2% can not be set up  at the same time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FeeCode %FEECODE1% and %FEECODE2% can not be set up  at the same time.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("FeeCode %FEECODE1% and %FEECODE2% can not be set up  at the same time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les codes de frais %FEECODE1% et %FEECODE2% ne peuvent être réglés à la même heure.")); }

        // Actions
	};
}



