#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_batch_belongs_to_otheruser : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_batch_belongs_to_otheruser() { }
		~CIFast_IFast_ifastcbo_err_batch_belongs_to_otheruser() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCH_BELONGS_TO_OTHERUSER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch belongs to another user.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot appartient à un autre utilisateur.")); }

        // Actions
	};
}



