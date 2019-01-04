#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_split_commission_only_discounts_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_split_commission_only_discounts_allowed() { }
		~CIFast_IFast_ifastcbo_err_split_commission_only_discounts_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLIT_COMMISSION_ONLY_DISCOUNTS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only discounts are allowed for commission.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only discounts are allowed for this split commission rates list.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Only discounts are allowed for this split commission rates list.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les escomptes sont autorisés pour la commission.")); }

        // Actions
	};
}



