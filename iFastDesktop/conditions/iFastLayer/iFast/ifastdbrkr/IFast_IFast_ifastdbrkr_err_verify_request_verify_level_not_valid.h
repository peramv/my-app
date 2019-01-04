#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_verify_request_verify_level_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_verify_request_verify_level_not_valid() { }
		~CIFast_IFast_ifastdbrkr_err_verify_request_verify_level_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERIFY_REQUEST_VERIFY_LEVEL_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VerifyRequest - Verify Level is not valid")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Demande de vérification – niveau de vérification invalide")); }

        // Actions
	};
}



