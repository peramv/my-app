#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_invalid_mrs_account : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_invalid_mrs_account() { }
		~CIFast_Infrastructure_ifastdbrkr_err_invalid_mrs_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_MRS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Configuration setting is invalid. Session cannot process AWD event. Business area, work type, or status is undefined.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Configuration setting is invalid. Session cannot process AWD event. Business area, work type, or status is undefined.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konfigurationseinstellung ist ungültig. Die Sitzung kann das AWD-Ereignis nicht bearbeiten. Geschäftsbereich, Arbeitstyp oder Status sind nicht definiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El parámetro de configuración no es válido. La sesión no puede procesar el evento de AWD. El área de negocios, tipo de tarea o estado no están definidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Réglage de configuration invalide. La session ne peut traiter l'événement AWD. Le secteur de marché, le type de travail ou le statut n'ont pas été définis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Configuratie-instelling is ongeldig. Sessie kan AWD-gebeurtenis niet verwerken. Zakelijk gebied, werktype of status is ongedefinieerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



