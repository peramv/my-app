#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reset_date_later_cur_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reset_date_later_cur_date() { }
		~CIFast_IFast_ifastcbo_err_reset_date_later_cur_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESET_DATE_LATER_CUR_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reset Date cannot be later than current business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Reset Date cannot be later than current business date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Reset Date cannot be later than current business date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de revalorisation ne peut être postérieure à la date opérationnelle actuelle.")); }

        // Actions
	};
}



