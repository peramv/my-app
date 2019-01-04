#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_persistence_start_request_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_persistence_start_request_failed() { }
		~CIFast_IFast_ifastdbrkr_err_persistence_start_request_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERSISTENCE_START_REQUEST_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An error occurred attempting to establish a persistent connection to the host.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Fehler trat auf beim Versuch, eine beständige Verbindung mit dem Host herzustellen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se produjo un error al intentar establecer una conexión persistente con el host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la tentative d'établir une connexion automatique à l'hôte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout opgetreden bij het maken van een vaste verbinding met de host")); }

        // Actions
	};
}



