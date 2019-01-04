#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_deposit_date_affect_min_max_amt : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_deposit_date_affect_min_max_amt() { }
		~CIFast_Infrastructure_ifastcbo_err_deposit_date_affect_min_max_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_DATE_AFFECT_MIN_MAX_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Failed to connect with the Logon Manager")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Failed to connect with the Logon Manager")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verbindung mit dem Anmelde-Manager fehlgeschlagen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no se pudo conectar con el Logon Manager")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de connexion au gestionnaire d'ouverture de session")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbinding met aanmeldingsmanager is mislukt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich zwecks Überprüfung der Installation von TaLogon an einen Supervisor")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour vérifier l'installation de ?")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor om de installatie van TaLogon te controleren")); }
	};
}



