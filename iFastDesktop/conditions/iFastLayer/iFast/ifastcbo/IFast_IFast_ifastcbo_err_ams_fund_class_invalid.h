#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_fund_class_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_fund_class_invalid() { }
		~CIFast_IFast_ifastcbo_err_ams_fund_class_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_FUND_CLASS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUNDNAME% Class %CLASSNAME% is not eligible for this type of allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUNDNAME% Class %CLASSNAME% is not eligible for this type of allocation.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund %FUNDNAME% Class %CLASSNAME% is not eligible for this type of allocation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUNDNAME% et la classe %CLASSNAME% ne sont pas admissibles à ce type de répartition.")); }

        // Actions
	};
}



