#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_qesi_grant_request_not_available_for_beneficiary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_qesi_grant_request_not_available_for_beneficiary() { }
		~CIFast_IFast_ifastcbo_warn_qesi_grant_request_not_available_for_beneficiary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_QESI_GRANT_REQUEST_NOT_AVAILABLE_FOR_BENEFICIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Grant Request not available for the Beneficiary in the Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de subvention IQEE n'est pas disponible pour le bénéficiaire en cette année d'imposition.")); }

        // Actions
	};
}



