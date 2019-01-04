#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_less_than_xii_month : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_less_than_xii_month() { }
		~CIFast_IFast_ifastcbo_err_less_than_xii_month() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LESS_THAN_XII_MONTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are less than 12 months.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There are less than 12 months.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es bleiben weniger als 12 Monate.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay menos de 12 meses.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a moins de 12 mois.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn minder dan 12 maanden")); }

        // Actions
	};
}



