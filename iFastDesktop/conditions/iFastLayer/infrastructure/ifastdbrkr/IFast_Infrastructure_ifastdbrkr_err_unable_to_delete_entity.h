#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_entity : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_entity() { }
		~CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Communications with the host system timed out before a response was received.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Communications with the host system timed out before a response was received.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zeitüberschreitung bei Kommunikation mit dem Hostsystem, bevor eine Antwort erhalten wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Finalizó el intervalo de espera de comunicación con el sistema host antes de recibir respuesta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La communication avec le système de l'hôte a expiré avant qu'une réponse ne soit reçue.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Communicatie met het hostsysteem is verlopen voordat er een respons is ontvangen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again at a later time, or contact an administrator to increase the timeout period.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try again at a later time, or contact an administrator to increase the timeout period.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es zu einem späteren Zeitpunkt noch einmal, oder wenden Sie sich an einen Administrator, um den Zeitraum für die Zeitüberschreitung zu erhöhen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try again at a later time, or contact an administrator to increase the timeout period.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez plus tard ou communiquez avec un administrateur pour augmenter le délai d'inactivité.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer opnieuw op een later tijdstip of neem contact op met een beheerder om de tijdslimiet te verleggen")); }
	};
}



