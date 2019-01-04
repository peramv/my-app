#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_commission_is_not_negotiable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_commission_is_not_negotiable() { }
		~CIFast_IFast_ifastcbo_err_commission_is_not_negotiable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMISSION_IS_NOT_NEGOTIABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission is not negotiable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Commission is not negotiable.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Commission is not negotiable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La commission n'est pas négociable.")); }

        // Actions
	};
}



