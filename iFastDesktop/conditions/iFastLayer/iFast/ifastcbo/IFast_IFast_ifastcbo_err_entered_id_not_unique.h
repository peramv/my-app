#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entered_id_not_unique : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entered_id_not_unique() { }
		~CIFast_IFast_ifastcbo_err_entered_id_not_unique() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTERED_ID_NOT_UNIQUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ID is not unique.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code non unique")); }

        // Actions
	};
}



