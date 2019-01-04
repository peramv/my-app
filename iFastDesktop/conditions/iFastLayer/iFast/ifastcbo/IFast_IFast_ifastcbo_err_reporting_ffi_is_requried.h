#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reporting_ffi_is_requried : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reporting_ffi_is_requried() { }
		~CIFast_IFast_ifastcbo_err_reporting_ffi_is_requried() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REPORTING_FFI_IS_REQURIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reporting FFI is requried.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rapport FFI  requis.")); }

        // Actions
	};
}



