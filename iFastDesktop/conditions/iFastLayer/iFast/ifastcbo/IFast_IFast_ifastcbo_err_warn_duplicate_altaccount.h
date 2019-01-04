#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_duplicate_altaccount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_duplicate_altaccount() { }
		~CIFast_IFast_ifastcbo_err_warn_duplicate_altaccount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_DUPLICATE_ALTACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Alternate account for this broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppeltes Verfügungsberechtigten-Konto für diesen Broker")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuenta alternativa repetida para este corredor")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie de l'autre compte pour ce courtier")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbel alternatief account voor deze makelaar")); }

        // Actions
	};
}



