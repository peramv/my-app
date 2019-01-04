#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_next_key_did_not_match_expected_format : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_next_key_did_not_match_expected_format() { }
		~CIFast_IFast_ifastdbrkr_err_next_key_did_not_match_expected_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Key did not match expected format.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Next Key did not match expected format.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nächster Schlüssel passte nicht zum erwarteten Format")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La clave siguiente no coincidió con el formato esperado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine clé de correspondait pas au format escompté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volgende sleutel komt niet overeen met de verwachte indeling")); }

        // Actions
	};
}



