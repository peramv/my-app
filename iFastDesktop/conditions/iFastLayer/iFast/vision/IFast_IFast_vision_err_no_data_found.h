#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_data_found : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_data_found() { }
		~CIFast_IFast_vision_err_no_data_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DATA_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Data Found")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Données introuvables")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Daten gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune donnée n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen gegevens gevonden")); }

        // Actions
	};
}



