#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nontrustee_grant_req_not_avail_in_taxyear : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nontrustee_grant_req_not_avail_in_taxyear() { }
		~CIFast_IFast_ifastcbo_err_nontrustee_grant_req_not_avail_in_taxyear() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NONTRUSTEE_GRANT_REQ_NOT_AVAIL_IN_TAXYEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Grant Request of Non Trustee is not available for the Beneficiary in the Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de subvention IQEE du non fiduciaire n'est pas disponible pour le bénéficiaire pour l'année d'imposition.")); }

        // Actions
	};
}



