#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transitno_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transitno_not_exist() { }
		~CIFast_IFast_ifastcbo_err_transitno_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSITNO_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The transit number does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The transit number does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Bankleitzahl existiert nicht. Bitte geben Sie neu ein oder drücken Sie F4, um eine Liste mit gültigen Banken einzusehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de tránsito no existe. Por favor vuelva a introducir los datos o presione F4 para ver una lista de bancos válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de succursale inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het transitnummer bestaat niet. Vul opnieuw in of druk op F4 voor een lijst met geldige banken")); }

        // Actions
	};
}



