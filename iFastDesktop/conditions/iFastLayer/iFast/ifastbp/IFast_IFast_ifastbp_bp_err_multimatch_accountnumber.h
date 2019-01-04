#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_multimatch_accountnumber : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_multimatch_accountnumber() { }
		~CIFast_IFast_ifastbp_bp_err_multimatch_accountnumber() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_MULTIMATCH_ACCOUNTNUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple matches for account number found against broker/alternate account combinations.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Übereinstimmungen für Kontonummer mit Broker/Verfügungsberechtigten-Konto-Kombinationen gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se encontraron varias coincidencias para el número de cuenta en combinaciones de corredor/cuentas alternativas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs correspondances trouvées pour le numéro de compte avec la combinaison courtier/autre compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere overeenstemmingen voor accountnummer gevonden met combinaties van makelaar/alternatief account")); }

        // Actions
	};
}



