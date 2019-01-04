#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_stop_date_must_be_within_regporting_ffi : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_stop_date_must_be_within_regporting_ffi() { }
		~CIFast_IFast_ifastcbo_err_start_stop_date_must_be_within_regporting_ffi() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reporting FFI is not valid as of %STARTDATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La FFI avec obligation de rapport n’est pas valide en date du %STARTDATE%.")); }

        // Actions
	};
}



