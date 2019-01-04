#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_no_longer_supported_after_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_no_longer_supported_after_date() { }
		~CIFast_IFast_ifastcbo_err_tax_type_no_longer_supported_after_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_NO_LONGER_SUPPORTED_AFTER_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New account set up for %VAR1% is not allowed where the effective date is after %GRANDFATHEREDDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La création d'un nouveau compte RERI pour la %VAR1% n'est pas autorisée lorsque la date d'effet est ultérieure au %GRANDFATHEREDDATE%.")); }

        // Actions
	};
}



