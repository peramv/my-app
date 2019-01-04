#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deptype_redcode_can_not_be_used_with_curr_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deptype_redcode_can_not_be_used_with_curr_year() { }
		~CIFast_IFast_ifastcbo_err_deptype_redcode_can_not_be_used_with_curr_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPTYPE_REDCODE_CAN_NOT_BE_USED_WITH_CURR_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%CODE% are not applicable when contribute tax year is same with current year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code %CODE% n'est pas applicable lorsque l'année d'imposition de cotisation est la même que l'année actuelle.")); }

        // Actions
	};
}



