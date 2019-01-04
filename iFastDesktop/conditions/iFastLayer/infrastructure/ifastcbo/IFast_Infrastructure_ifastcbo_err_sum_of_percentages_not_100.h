#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_sum_of_percentages_not_100 : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_sum_of_percentages_not_100() { }
		~CIFast_Infrastructure_ifastcbo_err_sum_of_percentages_not_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUM_OF_PERCENTAGES_NOT_100")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be empty. Zip code is not allowed. Remove zip code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^ must be empty. Zip code is not allowed. Remove zip code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss leer sein. Postleitzahl ist nicht erlaubt. Bitte entfernen Sie die Postleitzahl.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe estar vacío. No se permite el código postal. Elimine el código postal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% doit être vide. Code postal non autorisé. Enlevez le code postal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet leeg zijn. Postcode is niet toegestaan. Verwijder de postcode")); }

        // Actions
	};
}



