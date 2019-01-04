#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_end_date_less_than_stop_date_of_pacswp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_end_date_less_than_stop_date_of_pacswp() { }
		~CIFast_IFast_ifastcbo_err_end_date_less_than_stop_date_of_pacswp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_END_DATE_LESS_THAN_STOP_DATE_OF_PACSWP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End Date must be earlier or equal to the Stop Date of the PAC/Savings Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Enddatum muss kleiner oder gleich dem Stoppdatum des PAC/Spar-Plans sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de terminación debe ser anterior o igual a la fecha de baja del PAC/plan de ahorro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt doit être antérieure ou identique à la date d'arrêt du PAC/régime d'épargne.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum moet eerder zijn dan of gelijk zijn aan de einddatum van het VGC/Savings Plan")); }

        // Actions
	};
}



