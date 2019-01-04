#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_broker_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker Code does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune succursale exist avec les co-ordonnées que vous avez spécifié.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker-Code existiert nicht. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de corredor no existe. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de courtier inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaarscode bestaat niet. Vul opnieuw in")); }

        // Actions
	};
}



