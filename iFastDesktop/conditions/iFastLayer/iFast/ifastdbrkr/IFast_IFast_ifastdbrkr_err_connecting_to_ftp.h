#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_connecting_to_ftp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_connecting_to_ftp() { }
		~CIFast_IFast_ifastdbrkr_err_connecting_to_ftp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONNECTING_TO_FTP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error Connecting to FTP HOST - %ERROR%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler bei der Verbindung mit FTP-Host -%ERROR%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al conectarse con FTP HOST -  %ERROR%:")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de la connexion à l'hôte FTP – %ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij verbinden met FTP-host - %ERROR%")); }

        // Actions
	};
}



