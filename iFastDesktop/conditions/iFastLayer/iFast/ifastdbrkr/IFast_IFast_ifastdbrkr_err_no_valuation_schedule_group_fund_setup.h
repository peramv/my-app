#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_group_fund_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_group_fund_setup() { }
		~CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_group_fund_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VALUATION_SCHEDULE_GROUP_FUND_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Valuation schedule fund group is not setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bewertungslisten-Fonds-Gruppe ist nicht erstellt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el grupo de fondos con plan de valuación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le groupe de fonds du tableau d'évaluation n'est pas réglé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsgroep voor waarderingsschema is niet ingesteld")); }

        // Actions
	};
}



