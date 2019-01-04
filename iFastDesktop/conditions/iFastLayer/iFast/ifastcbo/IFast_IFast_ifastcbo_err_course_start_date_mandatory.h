#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_course_start_date_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_course_start_date_mandatory() { }
		~CIFast_IFast_ifastcbo_err_course_start_date_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COURSE_START_DATE_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Academic year start date is mandatory")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début de l'année universitaire est requise.")); }

        // Actions
	};
}



