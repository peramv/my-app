#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_must_be_business_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_must_be_business_date() { }
		~CIFast_IFast_ifastcbo_err_date_must_be_business_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_MUST_BE_BUSINESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% must fall on a business day.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% doit correspondre a un jour ouvrable")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% muss auf einen Geschäftstag fallen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% debe caer en un día hábil")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% doit tomber un jour ouvrable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% moet op een werkdag vallen")); }

        // Actions
	};
}



