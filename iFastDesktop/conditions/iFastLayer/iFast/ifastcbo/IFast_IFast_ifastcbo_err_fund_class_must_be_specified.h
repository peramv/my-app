#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_be_specified : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_be_specified() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_be_specified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BE_SPECIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Class must be specified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondsklasse muss spezifiziert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe especificarse la clase de fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La classe de fonds doit être spécifiée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscategorie moet worden opgegeven")); }

        // Actions
	};
}



