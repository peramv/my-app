#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_toclasscode_toaccount_for_indicatie_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_toclasscode_toaccount_for_indicatie_allocation() { }
		~CIFast_IFast_ifastcbo_err_toclasscode_toaccount_for_indicatie_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOCLASSCODE_TOACCOUNT_FOR_INDICATIE_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To class code and to account are for indicating allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zu-Klassen-Code und Zu-Konto sind zum Anzeigen der Zuweisung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de clase de destino y la cuenta de destino son para indicar la asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de classe cible et le compte cible servent à indiquer la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Naar categoriecode en naar account zijn er om de allocatie aan te geven")); }

        // Actions
	};
}



