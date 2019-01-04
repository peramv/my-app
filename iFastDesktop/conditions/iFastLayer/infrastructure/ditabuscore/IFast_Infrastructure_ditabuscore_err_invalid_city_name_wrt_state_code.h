#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_invalid_city_name_wrt_state_code : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_invalid_city_name_wrt_state_code() { }
		~CIFast_Infrastructure_ditabuscore_err_invalid_city_name_wrt_state_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CITY_NAME_WRT_STATE_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("State Code of %VALUE% Requires City Name to be Either APO or FPO")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("State Code of %VALUE% Requires City Name to be Either APO or FPO")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für den Staatscode von %VALUE% muss der Stadtname entweder APO oder FPO sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de estado de %VALUE% requiere que el nombre de la ciudad sea APO o FPO")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour un code d'état/de province de %VALUE%, le nom de la ville doit être APO ou FPO.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Staatcode %VALUE% vereist stadsnaam om APO of FPO te zijn")); }

        // Actions
	};
}



