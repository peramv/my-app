#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unknown_ftp_read_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unknown_ftp_read_error() { }
		~CIFast_IFast_ifastdbrkr_err_unknown_ftp_read_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_FTP_READ_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown FTP file read error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekannter FTP-Fehler beim Lesen der Datei.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de lectura de archivo FTP desconocido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de lecture de fichier FTP inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende fout FTP-bestand lezen")); }

        // Actions
	};
}



