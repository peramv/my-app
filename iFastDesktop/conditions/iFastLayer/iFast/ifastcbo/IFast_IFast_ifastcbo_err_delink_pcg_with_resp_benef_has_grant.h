#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delink_pcg_with_resp_benef_has_grant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delink_pcg_with_resp_benef_has_grant() { }
		~CIFast_IFast_ifastcbo_err_delink_pcg_with_resp_benef_has_grant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELINK_PCG_WITH_RESP_BENEF_HAS_GRANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delink PCG due to current RESP benef has existing grant request.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de séparer le responsable principal parce que le bénéficiaire REEE actuel a une demande de subvention existante.")); }

        // Actions
	};
}



