#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_valuation_schedule_group_fund_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_valuation_schedule_group_fund_setup() { }
		~CIFast_IFast_ifastdbrkr_err_valuation_schedule_group_fund_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUATION_SCHEDULE_GROUP_FUND_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not setup in valuation schedule group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds ist in Bewertungslisten-Gruppe nicht erstellt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo no está configurado en un grupo con plan de valuación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas réglé dans le groupe du tableau d'évaluation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds is niet ingesteld in waarderingsschemagroep")); }

        // Actions
	};
}



