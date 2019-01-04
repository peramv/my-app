#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_benef_reason_cannot_be_modified : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_benef_reason_cannot_be_modified() { }
		~CIFast_IFast_ifastcbo_err_resp_benef_reason_cannot_be_modified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_REASON_CANNOT_BE_MODIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reason cannot be modified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Reason cannot be modified.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Reason cannot be modified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La raison ne peut être modifiée.")); }

        // Actions
	};
}



