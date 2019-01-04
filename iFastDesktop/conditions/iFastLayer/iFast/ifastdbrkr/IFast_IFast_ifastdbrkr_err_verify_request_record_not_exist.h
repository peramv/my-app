#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_verify_request_record_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_verify_request_record_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_verify_request_record_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERIFY_REQUEST_RECORD_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VerifyRequest record does not exist")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement de demande de vérification inexistant")); }

        // Actions
	};
}



