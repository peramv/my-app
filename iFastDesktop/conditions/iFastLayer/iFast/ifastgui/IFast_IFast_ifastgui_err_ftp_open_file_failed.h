#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_err_ftp_open_file_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_err_ftp_open_file_failed() { }
		~CIFast_IFast_ifastgui_err_ftp_open_file_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FTP_OPEN_FILE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FTP open file failed - %ERROR%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FTP konnte Datei nicht öffnen - %ERROR%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló Abrir archivo FTP - %ERROR%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de fichier ouvert FTP – %ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("FTP-bestand openen is mislukt - %ERROR%")); }

        // Actions
	};
}



