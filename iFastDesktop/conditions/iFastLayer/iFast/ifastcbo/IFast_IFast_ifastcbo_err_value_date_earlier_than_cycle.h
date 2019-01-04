#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_value_date_earlier_than_cycle : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_value_date_earlier_than_cycle() { }
		~CIFast_IFast_ifastcbo_err_value_date_earlier_than_cycle() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_DATE_EARLIER_THAN_CYCLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value Date should be equal to or later than next cycle date of fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Valutatag sollte das gleiche oder ein späteres sein als/wie das nächste Zyklusdatum des Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de valuación debe ser igual o posterior a la fecha del siguiente ciclo del fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de la valeur devrait être identique ou postérieure à la prochaine date de cycle du fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waardedatum moet gelijk zijn aan of later dan de volgende cyclusdatum van het fonds")); }

        // Actions
	};
}



