#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_trustee_update_hist_info_req : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_trustee_update_hist_info_req() { }
		~CIFast_IFast_ifastcbo_err_non_trustee_update_hist_info_req() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_TRUSTEE_UPDATE_HIST_INFO_REQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Update Tax Jurisdiction History if beneficiary was a resident of Quebec on December 31 of the applicable historical year(s). Create the QESI grant request for the applicable historical year(s).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mettez à jour l'historique de juridiction fiscale si le bénéficiaire était un résident du Québec le 31 décembre de/des année(s) historique(s) applicable(s). Créez une demande de subvention IQEE pour la/les année(s) historique(s) applicable(s).")); }

        // Actions
	};
}



