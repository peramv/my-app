#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifysem_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifysem_error() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifysem_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMNOTIFYSEM_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem due to a View Manager notification semaphore error.  Semaphore Name: %sem%  Return Code: %rc%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem due to a View Manager notification semaphore error.  Semaphore Name: %sem%  Return Code: %rc%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem wegen eines View Manager-Benachrichtigungs-Semaphorfehlers.  Semaphorname: Rückgabecode: %rc%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno debido a un error de semáforo de notificación de View Manager.  Nombre del semáforo: %sem%  Código de retorno: %rc%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne dû à une erreur de sémaphore de notification du gestionnaire de l'affichage. Nom du sémaphore : %sem%, code de renvoi : %rc%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat er een fout is opgetreden bij de berichtgevingssemafoor van View Manager.  Naam semafoor: %sem%  Retourcode: %rc%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



