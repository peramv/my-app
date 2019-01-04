#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_err_unknown_ftp_open_file_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_err_unknown_ftp_open_file_error() { }
		~CIFast_IFast_ifastgui_err_unknown_ftp_open_file_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_FTP_OPEN_FILE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Uknown FTP Open File error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekannter FTP-Fehler beim Öffnen der Datei.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de Abrir archivo FTP desconocido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de fichier ouvert FTP inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende fout FTP-bestand openen")); }

        // Actions
	};
}



