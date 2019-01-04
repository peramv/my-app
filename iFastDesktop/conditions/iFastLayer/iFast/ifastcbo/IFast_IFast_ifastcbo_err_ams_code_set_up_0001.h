#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_set_up_0001 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_set_up_0001() { }
		~CIFast_IFast_ifastcbo_err_ams_code_set_up_0001() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_SET_UP_0001")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code 0001 can not be set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Code 0001 darf nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código 0001AMS no puede configurarse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille 0001 ne peut être réglé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("BBD-code 0001 kan niet worden ingesteld")); }

        // Actions
	};
}



