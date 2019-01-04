#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_verify_request_record_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_verify_request_record_locked() { }
		~CIFast_IFast_ifastdbrkr_err_verify_request_record_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERIFY_REQUEST_RECORD_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VerifyRequest record is locked, try later")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de demande de vérification est verrouillé, réessayez plus tard.")); }

        // Actions
	};
}



