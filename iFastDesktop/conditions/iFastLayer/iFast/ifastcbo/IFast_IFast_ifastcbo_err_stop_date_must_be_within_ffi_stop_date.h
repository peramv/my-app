#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_date_must_be_within_ffi_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_date_must_be_within_ffi_stop_date() { }
		~CIFast_IFast_ifastcbo_err_stop_date_must_be_within_ffi_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_MUST_BE_WITHIN_FFI_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date must be within Reporting FFI' Stop Date.")); }

        // Actions
	};
}



