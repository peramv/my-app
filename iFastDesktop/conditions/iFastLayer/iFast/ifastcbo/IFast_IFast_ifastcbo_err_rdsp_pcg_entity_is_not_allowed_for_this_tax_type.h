#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_pcg_entity_is_not_allowed_for_this_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_pcg_entity_is_not_allowed_for_this_tax_type() { }
		~CIFast_IFast_ifastcbo_err_rdsp_pcg_entity_is_not_allowed_for_this_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_PCG_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Primary Care Giver Entity is not allowed for this tax type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Primary Care Giver Entity is not allowed for this tax type.")); }

        // Actions
	};
}



