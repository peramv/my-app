#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_crs100series_for_acctowner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_crs100series_for_acctowner() { }
		~CIFast_IFast_ifastcbo_err_crs100series_for_acctowner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CRS100SERIES_FOR_ACCTOWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CRS classification codes should be linked only to the Account owner entity type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("CRS classification codes should be linked only to the Account owner entity type.")); }
        // Actions
	};
}



