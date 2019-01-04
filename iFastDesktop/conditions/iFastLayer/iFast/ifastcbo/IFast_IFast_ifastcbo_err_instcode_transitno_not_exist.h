#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_instcode_transitno_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_instcode_transitno_not_exist() { }
		~CIFast_IFast_ifastcbo_err_instcode_transitno_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSTCODE_TRANSITNO_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Institution code, transit number do not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Institutscode, Bankleitzahl existieren nicht. Führen Sie eine Neueingabe aus oder drücken Sie F4, um nach einer gültigen Bank zu suchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de institución, número de tránsito no existe. Por favor vuelva a introducir los datos o presione F4 para ver un banco válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'institution et numéro de succursale inexistants")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Instellingscode, transitnummer bestaat niet. Vul opnieuw in of druk op F4 voor een lijst met geldige banken")); }

        // Actions
	};
}



