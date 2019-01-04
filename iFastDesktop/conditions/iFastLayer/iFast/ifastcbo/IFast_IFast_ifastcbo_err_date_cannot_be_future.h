#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_cannot_be_future : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_cannot_be_future() { }
		~CIFast_IFast_ifastcbo_err_date_cannot_be_future() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_CANNOT_BE_FUTURE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The field cannot be future date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ ne peut pas comporter une date à venir.")); }

        // Actions
	};
}



