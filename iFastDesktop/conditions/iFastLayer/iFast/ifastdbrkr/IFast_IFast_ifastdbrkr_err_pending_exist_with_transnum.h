#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pending_exist_with_transnum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pending_exist_with_transnum() { }
		~CIFast_IFast_ifastdbrkr_err_pending_exist_with_transnum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENDING_EXIST_WITH_TRANSNUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EO/TO leg is processed. Cancel it to make EI/TI pending trade bad.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("EO/TO leg is processed. Cancel it to make EI/TI pending trade bad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("EO/TO leg is processed. Cancel it to make EI/TI pending trade bad.")); }

        // Actions
	};
}



