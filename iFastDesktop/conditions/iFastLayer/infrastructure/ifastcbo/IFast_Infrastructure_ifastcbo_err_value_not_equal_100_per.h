#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_value_not_equal_100_per : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_value_not_equal_100_per() { }
		~CIFast_Infrastructure_ifastcbo_err_value_not_equal_100_per() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_NOT_EQUAL_100_PER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The search found no matching data.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The search found no matching data.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei der Suche wurden keine passenden Daten gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La búsqueda no encontró datos coincidentes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune donnée correspondante n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen overeenkomende gegevens gevonden")); }

        // Actions
	};
}



