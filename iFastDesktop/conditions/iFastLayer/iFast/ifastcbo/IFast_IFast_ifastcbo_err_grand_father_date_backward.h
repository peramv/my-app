#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_grand_father_date_backward : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_grand_father_date_backward() { }
		~CIFast_IFast_ifastcbo_err_grand_father_date_backward() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GRAND_FATHER_DATE_BACKWARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GrandFather Date can not be backdated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GrandFather Date can not be backdated.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("GrandFather Date can not be backdated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date bénéficiant d'une clause de droits acquis ne peut être antidatée.")); }

        // Actions
	};
}



