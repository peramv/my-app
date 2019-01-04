#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_disessn_diodbc_connect_error : public CConditionObject
	{
	public:
		CIFast_Infrastructure_disessn_diodbc_connect_error() { }
		~CIFast_Infrastructure_disessn_diodbc_connect_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIODBC_CONNECT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error connecting to data source %SOURCE%: %SQL_ERROR%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error connecting to data source %SOURCE%: %SQL_ERROR%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler bei Verbindung mit folgender Datenquelle:%SOURCE%: %SQL_ERROR%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al conectarse con la fuente de datos %SOURCE%: %SQL_ERROR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de la connexion à la source de données%SOURCE% : %SQL_ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij verbinden met gegevensbron %SOURCE%: %SQL_ERROR%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



