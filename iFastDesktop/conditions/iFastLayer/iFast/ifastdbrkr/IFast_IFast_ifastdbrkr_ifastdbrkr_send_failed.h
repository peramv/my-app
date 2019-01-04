#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_send_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_send_failed() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_send_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_SEND_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not send data to host.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Could not send data to host.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Daten konnten nicht an Host gesendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudieron enviar los datos al host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'envoyer des données à l'hôte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens konden niet worden verzonden naar host")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



