#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_div_type_is_not_avail_for_fundclass : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_div_type_is_not_avail_for_fundclass() { }
		~CIFast_IFast_ifastcbo_err_div_type_is_not_avail_for_fundclass() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIV_TYPE_IS_NOT_AVAIL_FOR_FUNDCLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%DIVTYPE% distribution is not available for fund %FUNDFROM% class %CLASSFROM%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%DIVTYPE% distribution is not available for fund %FUNDFROM% class %CLASSFROM%.")); }

        // Actions
	};
}



