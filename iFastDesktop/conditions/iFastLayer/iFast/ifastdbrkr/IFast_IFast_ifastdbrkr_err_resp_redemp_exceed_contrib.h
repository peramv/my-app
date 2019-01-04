#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_redemp_exceed_contrib : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_redemp_exceed_contrib() { }
		~CIFast_IFast_ifastdbrkr_err_resp_redemp_exceed_contrib() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_REDEMP_EXCEED_CONTRIB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Redemption exceed Contribution.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Tilgung überschreitet Einlage.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El rescate RESP excedió las aportaciones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat REEE excèede la cotisation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RESP-aflossing overschrijdt de bijdrage")); }

        // Actions
	};
}



