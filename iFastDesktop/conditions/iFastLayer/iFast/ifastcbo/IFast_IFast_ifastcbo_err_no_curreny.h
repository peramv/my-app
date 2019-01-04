#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_curreny : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_curreny() { }
		~CIFast_IFast_ifastcbo_err_no_curreny() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_CURRENY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The currency selected is not supported.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die ausgewählte Währung wird nicht unterstützt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no soporta la divisa seleccionada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie sélectionnée n'est pas supportée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De geselecteerde valuta wordt niet ondersteund")); }

        // Actions
	};
}



