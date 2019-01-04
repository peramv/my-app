#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unable_to_change_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unable_to_change_group() { }
		~CIFast_IFast_ifastcbo_err_unable_to_change_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_CHANGE_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to change Shareholder group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unable to change Shareholder group.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Unable to change Shareholder group.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de changer le groupe d'actionnaire.")); }

        // Actions
	};
}



