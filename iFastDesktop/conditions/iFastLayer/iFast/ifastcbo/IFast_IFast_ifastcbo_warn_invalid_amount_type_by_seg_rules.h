#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_amount_type_by_seg_rules : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_amount_type_by_seg_rules() { }
		~CIFast_IFast_ifastcbo_warn_invalid_amount_type_by_seg_rules() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Amount Type for %TRANS_TYPE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour le %TRANS_TYPE%")); }


        // Actions
	};
}



