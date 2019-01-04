#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_expiry_date_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_expiry_date_required() { }
		~CIFast_IFast_ifastcbo_err_expiry_date_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXPIRY_DATE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Expiry date required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date d’expiration requise.")); }

        // Actions
	};
}



