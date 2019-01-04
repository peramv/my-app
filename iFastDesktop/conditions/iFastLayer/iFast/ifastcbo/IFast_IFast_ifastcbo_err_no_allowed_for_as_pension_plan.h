#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_allowed_for_as_pension_plan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_allowed_for_as_pension_plan() { }
		~CIFast_IFast_ifastcbo_err_no_allowed_for_as_pension_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax type 'As Pension Plan' applicable only to European clients.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax type 'As Pension Plan' applicable only to European clients.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tax type 'As Pension Plan' applicable only to European clients.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition x n'est applicable que pour les clients européens.")); }

        // Actions
	};
}



