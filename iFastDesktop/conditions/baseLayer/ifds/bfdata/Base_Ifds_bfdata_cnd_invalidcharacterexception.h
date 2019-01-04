#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdata_cnd_invalidcharacterexception : public CConditionObject
	{
	public:
		CBase_Ifds_bfdata_cnd_invalidcharacterexception() { }
		~CBase_Ifds_bfdata_cnd_invalidcharacterexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_InvalidCharacterException")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid character was found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte erneut senden, da der letzte Eintrag gelöscht wurde")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("An invalid character was found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un caractère invalide a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("An invalid character was found.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Corrigez le champ et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Correct the field and try again.")); }
	};
}



