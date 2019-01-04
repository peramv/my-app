#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_reporting_ffi_is_requried : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_reporting_ffi_is_requried() { }
		~CIFast_IFast_ifastcbo_warn_reporting_ffi_is_requried() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REPORTING_FFI_IS_REQURIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reporting FFI is requried.")); }

        // Actions
	};
}



