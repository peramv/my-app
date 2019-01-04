#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_register_address_not_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_register_address_not_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_register_address_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REGISTER_ADDRESS_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Financial institution information not available (A90).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Financial institution information not available (A90).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Finanzinstitut-Information nicht verfügbar (A90).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información sobre la institución financiera no está disponible (A90).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur l'institution financière n'est pas disponible (A90).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens financiële instelling zijn niet beschikbaar (A90)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again later or contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try again later or contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später nochmals oder wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try again later or contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez plus tard ou communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later nog eens of neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



