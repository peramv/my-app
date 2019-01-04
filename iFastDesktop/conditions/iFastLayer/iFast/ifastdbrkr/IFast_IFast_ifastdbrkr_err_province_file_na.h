#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_province_file_na : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_province_file_na() { }
		~CIFast_IFast_ifastdbrkr_err_province_file_na() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROVINCE_FILE_NA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Province file records not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Province file records not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provinz-Dateieinträge nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los registros de archivo de provincia no están disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les enregistrements du fichier de la province ne sont pas disponibles.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen records voor het provinciebestand beschikbaar")); }

        // Actions
	};
}



