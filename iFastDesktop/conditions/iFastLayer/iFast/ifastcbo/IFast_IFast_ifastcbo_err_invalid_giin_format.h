#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_giin_format : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_giin_format() { }
		~CIFast_IFast_ifastcbo_err_invalid_giin_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GIIN_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIIN format is incorrect.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de GIIN  incorrect.")); }

        // Actions
	};
}



