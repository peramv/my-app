#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_iwt_tax_juris : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_iwt_tax_juris() { }
		~CIFast_IFast_ifastcbo_err_not_iwt_tax_juris() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_IWT_TAX_JURIS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is not the Irish Withholding Tax Jurisdiction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("N’est pas assujetti à la retenue d’impôt irlandais.")); }

        // Actions
	};
}



