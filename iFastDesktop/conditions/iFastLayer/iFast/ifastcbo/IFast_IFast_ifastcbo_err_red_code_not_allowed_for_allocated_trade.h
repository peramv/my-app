#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_red_code_not_allowed_for_allocated_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_red_code_not_allowed_for_allocated_trade() { }
		~CIFast_IFast_ifastcbo_err_red_code_not_allowed_for_allocated_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RED_CODE_NOT_ALLOWED_FOR_ALLOCATED_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code %RED_CODE% cannot be used with Allocated Exchanges or Transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungscode %RED_CODE% darf nicht mit Zugewiesenen Devisen oder Transfers verwendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de rescate %RED_CODE% no se puede utilizar con traspasos o transferencias asignadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat %RED_CODE% ne peut être utilisé avec les échanges ou les transferts répartis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode %RED_CODE% kan niet worden gebruikt met gealloceerde ruiltransacties of overdrachten")); }

        // Actions
	};
}



