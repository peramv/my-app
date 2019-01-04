#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_sum_too_big2_rate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_sum_too_big2_rate() { }
		~CIFast_IFast_ifastcbo_err_rif_sum_too_big2_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_SUM_TOO_BIG2_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Federal Rate plus Provincial Rate must be smaller or equal to 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Federal Rate plus Provincial Rate must be smaller or equal to 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bundessatz + Provinzsatz müssen kleiner oder gleich 100 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa federal + la tasa provincial debe ser inferior o igual a 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux fédéral additionné au taux provincial doit être inférieur ou égal à 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Federaal tarief + Provincietarief moet kleiner zijn dan of gelijk zijn aan 100")); }

        // Actions
	};
}



