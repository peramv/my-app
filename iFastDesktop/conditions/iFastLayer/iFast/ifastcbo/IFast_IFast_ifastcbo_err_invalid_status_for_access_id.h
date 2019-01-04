#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_status_for_access_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_status_for_access_id() { }
		~CIFast_IFast_ifastcbo_err_invalid_status_for_access_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_STATUS_FOR_ACCESS_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot change Access Id status to %VAR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de changer le statut du code d'accès pour %VAR%.")); }

        // Actions
	};
}



