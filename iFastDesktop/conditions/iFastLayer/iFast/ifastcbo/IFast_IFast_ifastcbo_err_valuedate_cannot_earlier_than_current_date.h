#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_valuedate_cannot_earlier_than_current_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_valuedate_cannot_earlier_than_current_date() { }
		~CIFast_IFast_ifastcbo_err_valuedate_cannot_earlier_than_current_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUEDATE_CANNOT_EARLIER_THAN_CURRENT_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value date can not be earlier than current business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Valutatag darf nicht vor dem aktuellen Geschäftsdatum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de valuación no puede ser anterior a la fecha de negocios actual.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de valeur ne peut être antérieure à la date opérationnelle actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waardedatum kan niet eerder zijn dan de huidige werkdag")); }

        // Actions
	};
}



