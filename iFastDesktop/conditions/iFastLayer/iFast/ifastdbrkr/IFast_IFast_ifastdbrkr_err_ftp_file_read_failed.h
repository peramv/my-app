#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ftp_file_read_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ftp_file_read_failed() { }
		~CIFast_IFast_ifastdbrkr_err_ftp_file_read_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FTP_FILE_READ_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FTP file read failed - %ERROR%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FTP konnte Datei nicht lesen - %ERROR%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló Abrir archivo FTP - %ERROR%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de lecture de fichier FTP – %ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("FTP-bestand lezen is mislukt - %ERROR%")); }

        // Actions
	};
}



